// FtexedView.cpp : implementation of the CFtexedView class
//

#include "stdafx.h"
#include "Ftexed.h"
#include "FtexedDoc.h"
#include "FtexedView.h"
#include "GotoDlg.h"
#include "Search.h"
#include "Replace.h"
#include "Tokenizer.h"
#include <process.h>
#include <winreg.h>

//#include <wchar.h>

// The mapping array defined in the "Ftexed.cpp".
extern UCHAR map[256];

extern COLORREF background;
extern COLORREF normal_farsi_text;
extern COLORREF english_background;
extern COLORREF normal_english_text;
extern COLORREF selected_text;
extern COLORREF selection_background;
extern COLORREF commented_text;
extern COLORREF command_text;
extern COLORREF eraab_text;
extern COLORREF english_line_marker;

extern BOOL syntax_highlighting;
extern BOOL save_backups;
extern UINT clipboard_wrap_size;
extern BOOL pair_brackets_and_braces;
extern BOOL dash_is_number_separator;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFtexedView

IMPLEMENT_DYNCREATE(CFtexedView, CScrollView)

BEGIN_MESSAGE_MAP(CFtexedView, CScrollView)
	//{{AFX_MSG_MAP(CFtexedView)
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_GO, OnEditGo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_FARSI, OnUpdateFarsi)
	ON_UPDATE_COMMAND_UI(ID_ENGLISH, OnUpdateEnglish)
	ON_COMMAND(ID_FARSI, OnFarsi)
	ON_COMMAND(ID_ENGLISH, OnEnglish)
	ON_UPDATE_COMMAND_UI(ID_TEXT5, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_LnCol, OnUpdateLnCol)
	ON_COMMAND(ID_EDIT_SEARCH, OnEditSearch)
	ON_COMMAND(ID_EDIT_SEARCHAGAIN, OnEditSearchAgain)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_RUN_RUN, OnRunRun)
	ON_COMMAND(ID_RUN_CNVRT, OnRunCnvrt)
	ON_COMMAND(ID_RUN_PS, OnRunPs)
	ON_COMMAND(ID_RUN_VIEW, OnRunView)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GS, OnGhostView)
	ON_COMMAND(ID_RUN, OnRunFTeX)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SEARCHAGAIN, OnUpdateEDITSearchAgain)
	ON_COMMAND(ID_RUN_GS, OnRunGs)
	ON_COMMAND(ID_SYNTAXOFF, OnSyntaxoff)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_UPDATE_COMMAND_UI(ID_SYNTAXOFF, OnUpdateSyntaxoff)
	ON_COMMAND(ID_VIEW_DEF_MODE, OnViewDefMode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEF_MODE, OnUpdateViewDefMode)
	ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
	ON_COMMAND(ID_DVI, OnDvi)
	ON_COMMAND(ID_DVIPS, OnDvips)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_OPTIONS_CARETCASE, OnViewOptionsCaretcase)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPTIONS_CARETCASE, OnUpdateViewOptionsCaretcase)
	ON_COMMAND(ID_VIEW_OPTIONS_DEF_CARET_NEXT, OnDefCaretNext)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPTIONS_DEF_CARET_NEXT, OnUpdateDefCaretNext)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_EDIT_IMPORT, OnEditImport)
	ON_COMMAND(ID_RUN_MKIND, OnRunMkind)
	ON_COMMAND(ID_RUN_FTXTOUNI, OnRunFtxtouni)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtexedView construction/destruction

CFtexedView::CFtexedView()
{
	m_bHighlight = syntax_highlighting;
	m_bCaretChangeCase = true;
	m_bDefCaretNext = true;

	// TODO: add construction code here
	mode = FARSI;
	defaultMode = FARSI_IS_DEFAULT;

	numchar1 = numchar2 = 0;

	// Loading font.
	logFont.lfHeight = 16;
	logFont.lfWidth = 8;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfItalic = 0;
	logFont.lfUnderline = 0;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = ANSI_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
	strcpy(logFont.lfFaceName, "FarsiTeX");
	font = new CFont();
	font->CreateFontIndirect(&logFont);
	shift = 0;
	ctrl = 0;
	special_mode = 0;
	inserted_farsi_num = 0;
	m_bNewView = TRUE;
	search_is_done = false;


	/**************************************Reading addresses from Registry********************/
	/*******************Current directory of ftexed*************************/
	HKEY ftxHandle;
	long lftxSize = 100;

	if (RegOpenKey(HKEY_LOCAL_MACHINE,
		"Software\\CLASSES\\FarsiTeX.Document\\shell\\open\\command", &ftxHandle) == ERROR_SUCCESS) {
	    RegQueryValue(ftxHandle, NULL, m_szftxPath, &lftxSize);
		RegCloseKey(ftxHandle);
	}

	/*****************GhostView directory**********************/
	HKEY psHandle;
	long lpsSize = 100;

	if (RegOpenKey(HKEY_LOCAL_MACHINE,
		"Software\\CLASSES\\psfile\\shell\\open\\command", &psHandle) == ERROR_SUCCESS) {
	    RegQueryValue(psHandle, NULL, m_szpsPath, &lpsSize);
		RegCloseKey(psHandle);
	}

	for (int i = 0; i < lpsSize - 1; i++)
		m_szpsPath[i] = m_szpsPath[i+1];
	m_szpsPath[lpsSize - 8] = '\0';


	m_pEnCaret = new CBitmap;
	m_pFaCaret = new CBitmap;

	m_pEnCaret->LoadBitmap(IDB_EN_CARET);
	m_pFaCaret->LoadBitmap(IDB_FA_CARET);

}

CFtexedView::~CFtexedView()
{
	delete font;

	delete m_pEnCaret;

	delete m_pFaCaret;

}

BOOL CFtexedView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFtexedView drawing

void CFtexedView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here

	// Create a new font and select it into the DC.
	CFont* oldFont = pDC->SelectObject(font);

	// Number of lines to be redrawn.
	int yLen;

	// Position of the first line to be redrawn in pixels.
	UINT yPos;

	// A pointer to the first line to be redrawn.
	CFtexedDoc::LINETYPE *UpdateHead;

	topleft = GetDeviceScrollPosition();
	yLen = window.bottom / logFont.lfHeight + 2;
	yPos = topleft.y - (topleft.y % logFont.lfHeight);
	FindLine(topleft.y / logFont.lfHeight, &UpdateHead);

	for (int i = 0; i < yLen; i++) {
		int temp = ISL2R(UpdateHead)?m_pmargin:0;

		PrintLine(pDC, temp, yPos, UpdateHead->data, UpdateHead->len);

		yPos += logFont.lfHeight;
		UpdateHead = UpdateHead->next;
		if (UpdateHead == NULL)
			break;
	}

	// Restore the old font to the DC
	pDC->SelectObject(oldFont);
}

void CFtexedView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	GetClientRect(window);
	AdjustScrollers();
	OnScroll((128 << 8) + SB_THUMBTRACK, m_pmargin, TRUE);

	m_Curs.x = ISL2R(pDoc->m_head) ? m_cmargin + 1: MAX_TLEN / 2 - 1;
	m_Curs.y = 0;
	
	BeginSelPoint.x = -1;
}

/////////////////////////////////////////////////////////////////////////////
// CFtexedView printing

BOOL CFtexedView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFtexedView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFtexedView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFtexedView diagnostics

#ifdef _DEBUG
void CFtexedView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFtexedView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFtexedDoc* CFtexedView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFtexedDoc)));
	return (CFtexedDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFtexedView message handlers

void CFtexedView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (bActivate) {
		((CFtexedApp *)AfxGetApp())->ActiveView = this;
		SetMode(mode);
		HideCaret();
		topleft = GetDeviceScrollPosition();
		m_Curs.y -= FindLine(m_Curs.y, &CURLINE);
		ValidateCursorPos();
		UpdateCaretPos();
		ShowCaret();
	}

	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CFtexedView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint BeginP, EndP;
	BOOL DeletedLine = 0; // Will become one if Delete, has omitted a line;
	int save_num = pDoc->numLines;
	CFtexedView *(Views[2]);

	Handle$(nChar);
	if (!ISL2R(CURLINE) && (mode == ENGLISH) && (special_mode == 1))
		if (!isalpha(nChar)) {
			if (nChar != BACKSPACE)
				special_mode = 0;
			
			if ((nChar >= 32) && (nChar <= 128)) {
				SetMode(FARSI);
				while ((CURLINE->data[m_Curs.x] < 128) &&
					(CURLINE->data[m_Curs.x] >= 32))
					m_Curs.x--;
			}
		}

	if (!ISL2R(CURLINE) && (mode == FARSI) && (special_mode == 1))
		if ((!isdigit(nChar)) && (nChar != '#' /* Farsi Momayez */)
			&& (!dash_is_number_separator || nChar != '-' /* Farsi Khatte Teereh */)) {
			special_mode = 0;
			if ((nChar >= 32) && (nChar <= 128))
				while (((CURLINE->data[m_Curs.x] < 138) && (CURLINE->data[m_Curs.x] >= 128)) ||
					   (CURLINE->data[m_Curs.x] == 11) ||
					   (dash_is_number_separator && CURLINE->data[m_Curs.x] == 197)
					  )
					m_Curs.x--;
		}

	if (ISL2R(CURLINE) && (mode == FARSI) && (inserted_farsi_num == 1))
		if ((!isdigit(nChar)) && (nChar != '#' /* Farsi Momayez */)
			&& (!dash_is_number_separator || nChar != '-' /* Farsi Khatte Teereh */)) {
			inserted_farsi_num = 0;
			if ((nChar >= 32) && (nChar <= 128))
			{
				while (((CURLINE->data[m_Curs.x - m_cmargin] < 138) && (CURLINE->data[m_Curs.x - m_cmargin] >= 128)) ||
					   (CURLINE->data[m_Curs.x - m_cmargin] == 11) ||
					   (dash_is_number_separator && CURLINE->data[m_Curs.x - m_cmargin] == 197)
					  )
					m_Curs.x--;
				m_Curs.x++;
			}
		}


	if (CURLINE->len == 0) 
		if (nChar == '>') {
			m_Curs.x = m_cmargin;
			CURLINE->data[0] = '>';
			SetMode(ENGLISH);
		}
		else 
			strcpy((char *)CURLINE->data, pDoc->blanks);
		
	// Scroll the window such that cursor is in it.
	SetProperWindow(0);
/*
	if (((nChar == CTRLE) && (mode == FARSI)) || ((nChar == CTRLF) && (mode == ENGLISH)))
		nChar = CTRLG;
*/
	int tmp;
	int current;
	char tmpLine[MAX_TLEN / 2 + 1];	

	switch (nChar) {
	case '>':
		if ISL2R(CURLINE)
			break;

		if ((CURLINE->len != 0) && (mode == FARSI))
			break;

		if (m_Curs.x != MAX_TLEN / 2 - CURLINE->len - 1)
			break;

		if (CURLINE->len > MAX_TLEN / 2 - 2)
		{
			AfxMessageBox("This line is one character long for line mode conversion.");
			return;
		}
		strcpy(tmpLine, pDoc->blanks);
		tmpLine[0] = '>';

		strcpy(tmpLine + 1, (char *)CURLINE->data + (MAX_TLEN / 2 - CURLINE->len));
		strcpy((char *)CURLINE->data, tmpLine);
		m_Curs.x = m_cmargin + 1;
		CURLINE->len++;


		Unselect();
		UpdateCaretPos();
		Invalidate();

		return;

	case CTRLF:
		if (mode == ENGLISH) {
			BeginP.y = EndP.y = m_Curs.y;

			if ISL2R(CURLINE) { 
				UCHAR c;
				if (m_bCaretChangeCase)
				{
					c = CURLINE->data[m_Curs.x - m_cmargin];
					UINT prevChar = CURLINE->data[m_Curs.x - m_cmargin + SkipEraab(m_Curs.x - m_cmargin) + 1];
	
					if (c == 254) //ie kochik
					{
						if (!join_to_prev(prevChar))
							c = 253;
						else
							c = 252;
					}
					else
						c = farsi_upper_case(c);
				}
				else
					c = CURLINE->data[m_Curs.x - m_cmargin];

				if (c == CURLINE->data[m_Curs.x - m_cmargin]) {
					if (mode == FARSI)			
						SetMode(ENGLISH);
					else
						SetMode(FARSI);
					Unselect();
					UpdateCaretPos();
					return;
				}

				CURLINE->data[m_Curs.x - m_cmargin] = c;
				CURLINE->data[m_Curs.x - m_cmargin - 1] = ShiftSpaceMap(CURLINE->data[m_Curs.x - m_cmargin - 1]);

				BeginP.x = m_Curs.x;
				EndP.x = m_Curs.x + 1;
			}
			else {
				UCHAR c;
				if (m_bCaretChangeCase)
				{
					c = CURLINE->data[m_Curs.x + 1];
					UINT prevChar = CURLINE->data[m_Curs.x + 1 + SkipEraab(m_Curs.x + 1) + 1];
					if (c == 254) //ie kochik
					{
						if (!join_to_prev(prevChar))
							c = 253;
						else
							c = 252;
					}
					else
						c = farsi_upper_case(c);
				}
				else
					c = CURLINE->data[m_Curs.x + 1];
			
				
				if (c == CURLINE->data[m_Curs.x + 1]) {
					if (mode == FARSI)			
						SetMode(ENGLISH);
					else
						SetMode(FARSI);
					Unselect();
					UpdateCaretPos();
					return;
				}

				CURLINE->data[m_Curs.x + 1] = c;
				CURLINE->data[m_Curs.x] = ShiftSpaceMap(CURLINE->data[m_Curs.x]);

				BeginP.x = m_Curs.x + 1;
				EndP.x = m_Curs.x;

		}

		if (mode == FARSI)			
			SetMode(ENGLISH);
		else
			SetMode(FARSI);

		}
		break;

	case CTRLE:
		if (mode == FARSI){
			BeginP.y = EndP.y = m_Curs.y;

			if ISL2R(CURLINE) { 
				UCHAR c;
				if (m_bCaretChangeCase)
				{
					c = CURLINE->data[m_Curs.x - m_cmargin];
					UINT prevChar = CURLINE->data[m_Curs.x - m_cmargin + SkipEraab(m_Curs.x - m_cmargin) + 1];

					if (c == 254) //ie kochik
					{
						if (!join_to_prev(prevChar))
							c = 253;
						else
							c = 252;
					}
					else
						c = farsi_upper_case(c);
				}
				else
					c = CURLINE->data[m_Curs.x - m_cmargin];
			
				if (c == CURLINE->data[m_Curs.x - m_cmargin]) {
					if (mode == FARSI)			
						SetMode(ENGLISH);
					else
						SetMode(FARSI);
					Unselect();
					UpdateCaretPos();
					return;
				}

				CURLINE->data[m_Curs.x - m_cmargin] = c;
				CURLINE->data[m_Curs.x - m_cmargin - 1] = ShiftSpaceMap(CURLINE->data[m_Curs.x - m_cmargin - 1]);

				BeginP.x = m_Curs.x;
				EndP.x = m_Curs.x + 1;
			}
			else {
				UCHAR c;
				if (m_bCaretChangeCase)
				{
					c = CURLINE->data[m_Curs.x + 1];
					UINT prevChar = CURLINE->data[m_Curs.x + 1 + SkipEraab(m_Curs.x + 1) + 1];
					if (c == 254) //ie kochik
					{
						if (!join_to_prev(prevChar))
							c = 253;
						else
							c = 252;
					}
					else
						c = farsi_upper_case(c);
				}
				else
					c = CURLINE->data[m_Curs.x + 1];
			
								
				if (c == CURLINE->data[m_Curs.x + 1]) {
					if (mode == FARSI)			
						SetMode(ENGLISH);
					else
						SetMode(FARSI);
					Unselect();
					UpdateCaretPos();
					return;
				}

				CURLINE->data[m_Curs.x + 1] = c;
				CURLINE->data[m_Curs.x] = ShiftSpaceMap(CURLINE->data[m_Curs.x]);

				BeginP.x = m_Curs.x + 1;
				EndP.x = m_Curs.x;

			}

			if (mode == FARSI)			
				SetMode(ENGLISH);
			else
				SetMode(FARSI);

		}
		break;
	case CTRLG:
		// Last char before CTRLG must be updated 

		BeginP.y = EndP.y = m_Curs.y;

		if ISL2R(CURLINE) { 
			UCHAR c;
			if (m_bCaretChangeCase)
			{
				c = CURLINE->data[m_Curs.x - m_cmargin];
				UINT prevChar = CURLINE->data[m_Curs.x - m_cmargin + SkipEraab(m_Curs.x - m_cmargin) + 1];

				if (c == 254) //ie kochik
				{
					if (!join_to_prev(prevChar))
						c = 253;
					else
						c = 252;
				}
				else
					c = farsi_upper_case(c);
			}
			else
				c = CURLINE->data[m_Curs.x - m_cmargin];

			CPoint New_Curs;
		
			New_Curs = m_Curs;

			if (mode == FARSI)
			{
				while ((New_Curs.x - m_cmargin) < CURLINE->len && (CURLINE->data[New_Curs.x - m_cmargin] <= 32 || CURLINE->data[New_Curs.x - m_cmargin] >= 128))
					New_Curs.x++;
			}
			
			if (c == CURLINE->data[m_Curs.x - m_cmargin]) {
				if (mode == FARSI)			
					SetMode(ENGLISH);
				else
					SetMode(FARSI);
				m_Curs = New_Curs;
				Unselect();
				UpdateCaretPos();
				return;
			}

			CURLINE->data[m_Curs.x - m_cmargin] = c;
			CURLINE->data[m_Curs.x - m_cmargin - 1] = ShiftSpaceMap(CURLINE->data[m_Curs.x - m_cmargin - 1]);

			BeginP.x = m_Curs.x;
			EndP.x = m_Curs.x + 1;

			m_Curs = New_Curs;
			UpdateCaretPos();		
		}
		else {
			UCHAR c;
			if (m_bCaretChangeCase)
			{
				c = CURLINE->data[m_Curs.x + 1];
				UINT prevChar = CURLINE->data[m_Curs.x + 1 + SkipEraab(m_Curs.x + 1) + 1];
				if (c == 254) //ie kochik
				{
					if (!join_to_prev(prevChar))
						c = 253;
					else
						c = 252;
				}
				else
					c = farsi_upper_case(c);
			}

			else
				c = CURLINE->data[m_Curs.x + 1];


			CPoint New_Curs;
		
			New_Curs = m_Curs;

			if (mode == ENGLISH)
				while ( New_Curs.x >= 0 && (CURLINE->data[New_Curs.x] >= 32 && CURLINE->data[New_Curs.x] <= 128))
					New_Curs.x --;
			
			
			if (c == CURLINE->data[m_Curs.x + 1]) {
				if (mode == FARSI)			
					SetMode(ENGLISH);
				else
					SetMode(FARSI);
				m_Curs = New_Curs;
				Unselect();
				UpdateCaretPos();
				return;
			}

			CURLINE->data[m_Curs.x + 1] = c;
			CURLINE->data[m_Curs.x] = ShiftSpaceMap(CURLINE->data[m_Curs.x]);

			BeginP.x = m_Curs.x + 1;
			EndP.x = m_Curs.x;

			m_Curs = New_Curs;
			UpdateCaretPos();

		}

		if (mode == FARSI)			
			SetMode(ENGLISH);
		else
			SetMode(FARSI);

		break;
	
	case CTRLJ:
		if (!ISL2R(CURLINE))
			break;

		strcpy(tmpLine, pDoc->blanks);

		for (tmp = MAX_TLEN / 2 - 1; tmp > 0; tmp--)
		{
			current = MAX_TLEN / 2 - 1 - tmp;
			if (current >= CURLINE->len - 1)
				break;
			tmpLine[tmp]= CURLINE->data[CURLINE->len - current - 1];
		}

		strcpy((char *)CURLINE->data, tmpLine);

		m_Curs.x = MAX_TLEN / 2 - 1 - CURLINE->len + m_Curs.x - m_cmargin;
		CURLINE->len--;

		UpdateCaretPos();
		Invalidate();
		
		break;

	case BACKSPACE:
		if ((!ISL2R(CURLINE)) && (mode == ENGLISH) && (CURLINE->len == MAX_TLEN / 2 - m_Curs.x - 1) ||
			(ISL2R(CURLINE)) && (mode == FARSI) && (CURLINE->len == m_Curs.x - m_cmargin))
		{
			Unselect();
			return;
		}

		if ((!ISL2R(CURLINE)) && (mode == FARSI)) {
			if (m_Curs.x < MAX_TLEN / 2 - 1)
				m_Curs.x++;
			else if ((m_Curs.y != 0) && !ISL2R(CURLINE->last)) {
				CURLINE = CURLINE->last;
				m_Curs.x = MAX_TLEN / 2 - 1 - CURLINE->len;
				m_Curs.y--;
			}
			else
			{
				Unselect();
				return;
			}
		}
		else if ((ISL2R(CURLINE)) && (mode == ENGLISH)) {
			if (m_Curs.x > m_cmargin + 1)
				m_Curs.x--;
			else if ((m_Curs.y != 0) && ISL2R(CURLINE->last)) {
				CURLINE = CURLINE->last;
				m_Curs.x = m_cmargin + CURLINE->len;
				m_Curs.y--;
			}
			else
			{
				Unselect();
				return;
			}
		}

	case CDELETE:

		if (!ISL2R(CURLINE))
		{
			if (m_Curs.x > MAX_TLEN / 2 - 1 - CURLINE->len) {
				SetProperWindow(0);
				DelChar();
				BeginP.y = EndP.y = m_Curs.y;
				BeginP.x = m_Curs.x + 1;
				EndP.x = -1;
			}
			else if ((CURLINE->next != NULL) && (CURLINE->len + CURLINE->next->len <= MAX_TLEN / 2))
			{
				for (int i = 0; i < CURLINE->next->len; i++)
					CURLINE->data[MAX_TLEN / 2 - 1 - (CURLINE->len)++] = CURLINE->next->data[MAX_TLEN / 2 - 1 - i];

				CFtexedDoc::LINETYPE *p = CURLINE->next;
				CURLINE->next = CURLINE->next->next;

				if (CURLINE->next != NULL)
					CURLINE->next->last = CURLINE;

				delete p;

				pDoc->numLines--;
				BeginP.x = -1;
				BeginP.y = m_Curs.y;
				EndP.x = EndP.y = -1;
				DeletedLine = 1;
			}
		}
		else
		{
			if (m_Curs.x < m_cmargin + CURLINE->len) {
				SetProperWindow(0);
				DelChar();
				BeginP.y = EndP.y = m_Curs.y;
				BeginP.x = m_Curs.x;
				EndP.x = -1;
			}
			else if ((CURLINE->next != NULL) && (CURLINE->len + CURLINE->next->len <= MAX_TLEN / 2))
			{
				for (int i = 1; i < CURLINE->next->len; i++)
					CURLINE->data[(CURLINE->len)++] = CURLINE->next->data[i];

				CFtexedDoc::LINETYPE *p = CURLINE->next;
				CURLINE->next = CURLINE->next->next;

				if (CURLINE->next != NULL)
					CURLINE->next->last = CURLINE;

				delete p;

				pDoc->numLines--;
				BeginP.x = -1;
				BeginP.y = m_Curs.y;
				EndP.x = EndP.y = -1;
				DeletedLine = 1;
			}
		}
	
		break;

	case CTRLY:
		BeginP.x = -1;
		BeginP.y = m_Curs.y;
		EndP.x = EndP.y = -1;

		if (CURLINE->next != NULL) {
			if (CURLINE->last != NULL)
				CURLINE->last->next = CURLINE->next;

			CURLINE->next->last = CURLINE->last;

			CFtexedDoc::LINETYPE *p;
			p = CURLINE;
			
			if (CURLINE == pDoc->m_head)
				pDoc->m_head = CURLINE->next;
			
			CURLINE = CURLINE->next;
			
			delete p;

			pDoc->numLines--;
		}
		else {
			CURLINE->len = 0;
			strcpy((char *)CURLINE->data, pDoc->blanks);
		}

		ValidateCursorPos();
		
		break;

	case ENTER:
		CFtexedDoc::LINETYPE *temp;
		char last;

		if ((!IsRunningOnNT()) && (pDoc->numLines >= MAX_LINE_NUM_IN_WIN9X))
		{
			AfxMessageBox("Documents larger than 2048 lines are not supported in Win9x");
			shift = 0;
			ctrl = 0;
			Unselect();
			return;
		}

		pDoc->numLines++;
		m_Curs.y++;
		temp = CURLINE->next;

		CURLINE->next = new CFtexedDoc::LINETYPE;
		CURLINE->next->data = new BYTE[MAX_TLEN / 2 + 1];
		CURLINE->next->last = CURLINE;
		CURLINE->next->next = temp;
		CURLINE->next->base = 0;
		strcpy((char *)CURLINE->next->data, pDoc->blanks);
		if (temp != NULL)
			temp->last = CURLINE->next;

		if ISL2R(CURLINE) {
			if (m_Curs.x == m_cmargin + CURLINE->len)
			{
				if (defaultMode == FARSI_IS_DEFAULT)
				{
					m_Curs.x = MAX_TLEN / 2 - 1;
					CURLINE->next->len = 0;
					if (m_bDefCaretNext)
						SetMode(FARSI);
				}
				else
				{
					CURLINE->next->data[0] = '>';
					m_Curs.x = m_cmargin + 1;
					CURLINE->next->len = 1;
					if (m_bDefCaretNext)
						SetMode(ENGLISH);
				}
			}
			else {
				CURLINE->next->data[0] = '>';
				for (int i = m_Curs.x; i <= m_cmargin + CURLINE->len - 1; i++) {
					CURLINE->next->data[i - m_Curs.x + 1] = CURLINE->data[i - m_cmargin];
					CURLINE->data[i - m_cmargin] = 255;
				}
				CURLINE->next->len = m_cmargin + CURLINE->len - m_Curs.x + 1;
				CURLINE->len = m_Curs.x - m_cmargin;
				m_Curs.x = m_cmargin + 1;
			}
		}
		else {
			for (int i = MAX_TLEN / 2 - CURLINE->len; i <= m_Curs.x; i++) {
				CURLINE->next->data[i + MAX_TLEN / 2 - 1 - m_Curs.x] = CURLINE->data[i];
				CURLINE->data[i] = 255;
			}
			CURLINE->next->len = CURLINE->len - MAX_TLEN / 2 + 1 + (unsigned short)m_Curs.x;
			CURLINE->len = MAX_TLEN / 2 - 1 - (unsigned short)m_Curs.x;

			last = CURLINE->data[m_Curs.x + 1];
			UINT c = CURLINE->data[m_Curs.x + 1];
			UINT prevChar = CURLINE->data[m_Curs.x + 1 + SkipEraab(m_Curs.x + 1) + 1];
			if (c == 254) //ie kochik
			{
				if (!join_to_prev(prevChar))
					CURLINE->data[m_Curs.x + 1] = 253;
				else
					CURLINE->data[m_Curs.x + 1] = 252;
			}
			else
				CURLINE->data[m_Curs.x + 1] = farsi_upper_case(c);


			m_Curs.x = MAX_TLEN / 2 - 1;
			
			if (m_bDefCaretNext)
				SetMode(FARSI);
		}

		BeginP.y = m_Curs.y - 1;
		BeginP.x = -1;
		EndP.x = EndP.y = -1;
		CURLINE = CURLINE->next;
		if ((CURLINE->len == 0) && (last == CURLINE->data[m_Curs.x + 1]))
			BeginP.y++;
		
		break;

	case SPACE:
		if ((shift == 1) && (mode == FARSI))
			nChar = SHIFTB;
		else 
			break;
	case SHIFTB:
		// Last char before cursor must be updated 

		if (mode == FARSI) {
			BeginP.y = EndP.y = m_Curs.y;

			if (!ISL2R(CURLINE)) {

				UINT c = CURLINE->data[m_Curs.x + 1];
				UINT prevChar = CURLINE->data[m_Curs.x + 1 + SkipEraab(m_Curs.x + 1) + 1];
				if (c == 254) //ie kochik
				{
					if (!join_to_prev(prevChar))
						CURLINE->data[m_Curs.x + 1] = 253;
					else
						CURLINE->data[m_Curs.x + 1] = 252;
				}
				else
					CURLINE->data[m_Curs.x + 1] = farsi_upper_case(c);

				/**
				 * Added by Shiva 
				 * to remove the Shift+Space Problem
				**/
				CURLINE->data[m_Curs.x] = ShiftSpaceMap(CURLINE->data[m_Curs.x]);


			
				BeginP.x = m_Curs.x + 2;
				EndP.x = m_Curs.x + 1;
			}
			else {
				UINT c = CURLINE->data[m_Curs.x - m_cmargin];
				UINT prevChar = CURLINE->data[m_Curs.x - m_cmargin + SkipEraab(m_Curs.x - m_cmargin) + 1];
				if (c == 254) //ie kochik
				{
					if (!join_to_prev(prevChar))
						CURLINE->data[m_Curs.x - m_cmargin] = 253;
					else
						CURLINE->data[m_Curs.x - m_cmargin] = 252;
				}
				else
					CURLINE->data[m_Curs.x - m_cmargin] = farsi_upper_case(c);

				
				
				/**
				 * Added by Shiva 
				 * to remove the Shift+Space Problem
				**/
				CURLINE->data[m_Curs.x - m_cmargin - 1] = ShiftSpaceMap(CURLINE->data[m_Curs.x - m_cmargin - 1]);


				BeginP.x = m_Curs.x;
				EndP.x = m_Curs.x + 1;
			}
		}
		break;
	}

	if ((nChar >= 32) && ((nChar != SHIFTB) || (mode != FARSI))) { 
		UINT c = nChar;
		int mapret;

		if (mode == FARSI) {
			mapret = Map(c);
			if (isdigit(nChar) && (!ISL2R(CURLINE))) {
				if (special_mode == 0)
					mapret = 1;
				special_mode = 1;
			}

			else if (ISL2R(CURLINE) && (isdigit(nChar) || (nChar == '#' && inserted_farsi_num == 1) ||
					 (dash_is_number_separator && nChar == '-' && inserted_farsi_num == 1)))
			{
				if (inserted_farsi_num == 1)
					OnKeyDown(VK_RIGHT, 0, 0);

				inserted_farsi_num = 1;
			}
		}

		// Detecting la
		if ((ISL2R(CURLINE)) && 
			(CURLINE->data[m_Curs.x - m_cmargin] == 243) && (c == 145)) {

			CURLINE->data[m_Curs.x - m_cmargin] = 242;
			BeginP.y = EndP.y = m_Curs.y;
			BeginP.x = m_Curs.x;
			EndP.x = m_Curs.x + 1;
		}
		else if ((!ISL2R(CURLINE)) &&
			(CURLINE->data[m_Curs.x + 1] == 243) && (c == 145)) {

			CURLINE->data[m_Curs.x + 1] = 242;
			BeginP.y = EndP.y = m_Curs.y;
			BeginP.x = m_Curs.x + 2;
			EndP.x = m_Curs.x + 1;
		}
		else {
			if (CURLINE->len == MAX_TLEN / 2 - 1)
			{
				Unselect();
				return;
			}
			if ISL2R(CURLINE) {
	
				BeginP.y = EndP.y = m_Curs.y;
				if ((CURLINE->len == m_Curs.x - m_cmargin) && (mapret == 0)) {
					BeginP.x = m_Curs.x;
					EndP.x = m_Curs.x + 1;
				}
				else {
					BeginP.x = m_Curs.x;
					if (mapret != 0)
						BeginP.x--;
					EndP.x = -1;
				}
				for (int i = CURLINE->len + m_cmargin - 1; i >= m_Curs.x; i--)
					CURLINE->data[i + 1 - m_cmargin] = CURLINE->data[i - m_cmargin];
					
				(CURLINE->data)[m_Curs.x - m_cmargin] = c;
				if (mode == ENGLISH)
					m_Curs.x++;
			}
			else {
				BeginP.y = EndP.y = m_Curs.y;
				if ((m_Curs.x + CURLINE->len + 1 == MAX_TLEN / 2) && (mapret == 0)) {
					BeginP.x = m_Curs.x + 1; 
					EndP.x = m_Curs.x;
				}
				else {
					BeginP.x = m_Curs.x + 1;
					EndP.x = -1;
					if (mapret != 0)
						BeginP.x++;
				}
				for (int i = MAX_TLEN / 2 - 1 - CURLINE->len; i < m_Curs.x; i++)
					(CURLINE->data)[i] = (CURLINE->data)[i + 1];
				(CURLINE->data)[m_Curs.x] = c;
				if ((mode == FARSI) && (special_mode == 0))
					m_Curs.x--;
			}
			(CURLINE->len)++;
		}
	}

	if (save_num != pDoc->numLines) {
		FindAllViews(Views);
		for (int k = 0; k < 2; k++)
			if (Views[k] != NULL)
				Views[k]->AdjustScrollers();
			else
				break;
	}

	if (nChar == ENTER) {
		PerformScrolling(CPoint(m_pmargin, -1));
		SetProperWindow(2);
	}

	if ((nChar >= 32) || (nChar == CTRLY) || (nChar == BACKSPACE) ||
		(nChar == CDELETE) || (nChar == CTRLG) || (nChar == CTRLF) || (nChar == CTRLE) || (nChar == CTRLJ) ||
		(nChar == ENTER)) {
		Unselect();
		if (!(pDoc->IsModified())) {
			pDoc->SetModifiedFlag(TRUE);
			pDoc->SetTitle(pDoc->GetTitle() + " *");
		}
		

		//InvalidateBlock(BeginP, EndP);
/*		
		CRect rect;
		GetClientRect(&rect);
		int pagebase = GetDeviceScrollPosition().y;
		int phBegin = BeginP.y * logFont.lfHeight - pagebase;
		int phEnd = ((EndP.y != -1) ? ((EndP.y + 1) * logFont.lfHeight) - pagebase : rect.bottom);
		
		if (nChar != CTRLY && !DeletedLine)
			InvalidateRect(&CRect(0,phBegin, rect.right,phEnd), FALSE);
		else
			InvalidateRect(&CRect(0,phBegin, rect.right,rect.bottom), TRUE);
*/

		CRect rect;
		int pagebase;
		int phBegin;
		int phEnd;

		FindAllViews(Views);

		for (int k = 0; k < 2; k++)
		{
			if (Views[k] == NULL)
				continue;

			Views[k]->GetClientRect(&rect);
			pagebase = (Views[k]->GetDeviceScrollPosition()).y;
			phBegin = BeginP.y * logFont.lfHeight - pagebase;
			
			if (phBegin > rect.bottom)
				continue;

			phBegin = max(phBegin, 0);

			phEnd = ((EndP.y != -1) ? ((EndP.y + 1) * logFont.lfHeight) - pagebase : rect.bottom);


			if (nChar != CTRLY && !DeletedLine && phEnd < 0)
				continue;

		
			ASSERT(phBegin <= phEnd);

			if (nChar != CTRLY && !DeletedLine)
				Views[k]->InvalidateRect(&CRect(0,phBegin, rect.right,phEnd), FALSE);
			else
				Views[k]->InvalidateRect(&CRect(0,phBegin, rect.right,rect.bottom), TRUE);
		}
	}

	HandleSpecialKeys(nChar);

	UpdateCaretPos();
}

void CFtexedView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {

	// The shift key is released.
	case VK_SHIFT:
		shift = 0;
		break;

	// The control key is released.
	case VK_CONTROL:
		ctrl = 0;
		break;
	}
}

void CFtexedView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	CPoint save_curs(-1,-1);

	switch (nChar) {

	// The shift key is pressed.
	case VK_SHIFT:
		shift = 1;
		break;

	case VK_CONTROL:
		ctrl = 1;
		break;

	case VK_UP:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;
		GoUp(1);
		break;

	case VK_DOWN:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;
		GoDown(1);
		break;

	case VK_LEFT:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;
		if ISL2R(CURLINE)
		{
			if (m_Curs.x > m_cmargin + 1)
			{
				m_Curs.x--;
				//special_mode = 0;
			}

			if (ctrl == 1)
			{
				while ((m_Curs.x > m_cmargin + 1) && (IsSeparator(CURLINE->data[m_Curs.x - m_cmargin])))
					m_Curs.x--;

				while ((m_Curs.x > m_cmargin + 1) && (!IsSeparator(CURLINE->data[m_Curs.x - m_cmargin - 1])))
					m_Curs.x--;
			}

		}
		else if ((MAX_TLEN / 2 - 1 - CURLINE->len) < m_Curs.x)
		{
				m_Curs.x--;
				//special_mode = 0;

				if (ctrl == 1)
				{
					while (((MAX_TLEN / 2 - 1 - CURLINE->len) < m_Curs.x) && (!IsSeparator(CURLINE->data[m_Curs.x])))
						m_Curs.x--;

					while (((MAX_TLEN / 2 - 1 - CURLINE->len) < m_Curs.x) && (IsSeparator(CURLINE->data[m_Curs.x])))
						m_Curs.x--;

				}
		}
		SetProperWindow(0);
		break;

	case VK_RIGHT:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;
		if ISL2R(CURLINE)
		{
			if (m_Curs.x < m_cmargin + CURLINE->len)
			{
				m_Curs.x++;
				//special_mode = 0;
			}
			if (ctrl == 1)
			{
				while ((m_Curs.x < m_cmargin + CURLINE->len) && (!IsSeparator(CURLINE->data[m_Curs.x - m_cmargin])))
					m_Curs.x++;

				while ((m_Curs.x < m_cmargin + CURLINE->len) && (IsSeparator(CURLINE->data[m_Curs.x - m_cmargin])))
					m_Curs.x++;
			}

		}
		else if (MAX_TLEN / 2 - 1 > m_Curs.x)
		{
			m_Curs.x++;
			//special_mode = 0;

			if (ctrl == 1)
			{
				while ((MAX_TLEN / 2 - 1 > m_Curs.x) && (IsSeparator(CURLINE->data[m_Curs.x])))
					m_Curs.x++;

				while ((MAX_TLEN / 2 - 1 > m_Curs.x) && (!IsSeparator(CURLINE->data[m_Curs.x + 1])))
					m_Curs.x++;
			}

		}
		SetProperWindow(0);
		break;

	case VK_HOME:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;
		
		if (ctrl == 1)
			GoUp(m_Curs.y);
		else if ISL2R(CURLINE)
			m_Curs.x = m_cmargin + 1;
		else
			m_Curs.x = MAX_TLEN / 2 - 1;
		special_mode = 0;
		inserted_farsi_num = 0;
		SetProperWindow(0);
		break;

	case VK_END:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;

		if (ctrl == 1)
			GoDown(pDoc->numLines - m_Curs.y);
		else if ISL2R(CURLINE)
			m_Curs.x = m_cmargin + CURLINE->len;
		else
			m_Curs.x = MAX_TLEN / 2 - 1 - CURLINE->len;
		if (special_mode)
			SetMode(FARSI);
		special_mode = 0;
		inserted_farsi_num = 0;
		SetProperWindow(0);
		break;

	case VK_PRIOR:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;			
		GoUp(window.bottom / logFont.lfHeight);
		break;

	case VK_NEXT:
		if (!shift)
			Unselect();
		else
			save_curs = m_Curs;
		GoDown(window.bottom / logFont.lfHeight);
		break;

	case VK_DELETE:
		if (BeginSelPoint.x != -1)
			RemoveSelectedArea();
		else if ISL2R(CURLINE) {
			if (m_Curs.x < CURLINE->len + m_cmargin) {
				int temp_special_mode = special_mode;
				int temp_inserted_farsi_num = inserted_farsi_num;
				OnChar(CDELETE, 0, 0);
				special_mode = temp_special_mode;
				inserted_farsi_num = temp_inserted_farsi_num;
				//special_mode = 0;
			}
			else if (CURLINE->next != NULL) {
				if (ISL2R(CURLINE->next)) {
					int temp_special_mode = special_mode;
					int temp_inserted_farsi_num = inserted_farsi_num;
					OnChar(CDELETE, 0, 0);
					special_mode = temp_special_mode;
					inserted_farsi_num = temp_inserted_farsi_num;
					//special_mode = 0;
				}
			}
		}
		else {
			if (m_Curs.x > MAX_TLEN / 2 - 1 - CURLINE->len) {
				int temp_special_mode = special_mode;
				int temp_inserted_farsi_num = inserted_farsi_num;
				OnChar(CDELETE, 0, 0);
				special_mode = temp_special_mode;
				inserted_farsi_num = temp_inserted_farsi_num;
				//special_mode = 0;
			}
			else if (CURLINE->next != NULL) {
				if (!ISL2R(CURLINE->next)) {
					int temp_special_mode = special_mode;
					int temp_inserted_farsi_num = inserted_farsi_num;
					OnChar(CDELETE, 0, 0);
					special_mode = temp_special_mode;
					inserted_farsi_num = temp_inserted_farsi_num;
					//special_mode = 0;
				}
			}
		}
		break;
	}

	if ((save_curs.x != -1)  && (save_curs != m_Curs)) {
		if (BeginSelPoint.x == -1) {
			if (IsGreater(m_Curs, save_curs)) {
				BeginSelPoint = save_curs;
				EndSelPoint = m_Curs;
			}
			else {
				BeginSelPoint = m_Curs;
				EndSelPoint = save_curs;
			}
			InvalidateBlock(BeginSelPoint, EndSelPoint);
		}
		else {
			if (IsGreater(EndSelPoint, save_curs)) {
				// Cursor was previously at the beginnig of block
				if (IsGreater(BeginSelPoint, m_Curs)) {
					save_curs = BeginSelPoint;
					BeginSelPoint = m_Curs;
					InvalidateBlock(m_Curs, save_curs);
				}
				else if (IsGreater(EndSelPoint, m_Curs)) {
					save_curs = BeginSelPoint;
					BeginSelPoint = m_Curs;
					InvalidateBlock(save_curs, m_Curs);
				}
				else {
					save_curs = BeginSelPoint;
					BeginSelPoint = EndSelPoint;
					EndSelPoint = m_Curs;
					InvalidateBlock(save_curs, m_Curs);
				}
			}
			else {
				// Cursor was previously at the end of block
				if (IsGreater(BeginSelPoint, m_Curs)) {
					save_curs = EndSelPoint;
					EndSelPoint = BeginSelPoint;
					BeginSelPoint = m_Curs;
					InvalidateBlock(m_Curs, save_curs);
				}
				else if (IsGreater(EndSelPoint, m_Curs)) {
					save_curs = EndSelPoint;
					EndSelPoint = m_Curs;
					InvalidateBlock(m_Curs, save_curs);
				}
				else {
					save_curs = EndSelPoint;
					EndSelPoint = m_Curs;
					InvalidateBlock(save_curs, m_Curs);
				}
			}

			if (BeginSelPoint == EndSelPoint)
					BeginSelPoint.x = EndSelPoint.x = -1;
		}
	}

	UpdateCaretPos();
}

BOOL CFtexedView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{
	// TODO: Add your specialized code here and/or call the base class

	if (LOBYTE(nScrollCode) != 255)
		return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
	
	HideCaret();

	topleft = GetScrollPosition();
	SCROLLINFO ScrollInfo;
	GetScrollInfo(SB_VERT, &ScrollInfo);

	int nMapMode;
	SIZE sizeTotal, sizePage, sizeLine;
	GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);

	switch (HIBYTE(nScrollCode)) {
	case SB_LINEDOWN:
		ScrollToPosition(CPoint(topleft.x, min(sizeTotal.cy, topleft.y + sizeLine.cy)));
		break;
	case SB_LINEUP:
		ScrollToPosition(CPoint(topleft.x, max(0, topleft.y - sizeLine.cy)));
		break;
	case SB_PAGEDOWN:
		ScrollToPosition(CPoint(topleft.x, min(sizeTotal.cy, topleft.y + sizePage.cy)));
		break;
	case SB_PAGEUP:
		ScrollToPosition(CPoint(topleft.x, max (0, topleft.y - sizePage.cy)));
		break;
	case SB_THUMBTRACK:
		ScrollToPosition(CPoint(topleft.x, ScrollInfo.nTrackPos));
		break;
	case SB_THUMBPOSITION:
		break;
	}
	
	UpdateCaretPos();

	ShowCaret();

	return TRUE;
}

void CFtexedView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int temp = m_pmargin;

	GetClientRect(&window);

	m_pmargin = MAX_TLEN * logFont.lfWidth / 2 - window.right + (window.right % logFont.lfWidth);
	m_cmargin = m_pmargin / logFont.lfWidth;
	AdjustScrollers();
	PerformScrolling(CPoint(topleft.x + m_pmargin - temp, -1));

	if (((CFtexedApp *)AfxGetApp())->ActiveView == this)
		Invalidate();

	if ISL2R(CURLINE)
		m_Curs.x += ((m_pmargin - temp) / logFont.lfWidth);

	SetProperWindow(0);
	UpdateCaretPos();
}

void CFtexedView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	SetCapture();

	Unselect();
	m_Curs.x = (point.x + topleft.x) / logFont.lfWidth;
	int temp = (point.y + topleft.y) / logFont.lfHeight;

	if (temp > m_Curs.y)
		GoDown(temp - m_Curs.y);
	else
		GoUp(m_Curs.y - temp);

	if (!ISL2R(CURLINE)) {
		if ((CURLINE->data[m_Curs.x] < 32) || (CURLINE->data[m_Curs.x] >= 128))
			SetMode(FARSI);
		else SetMode(ENGLISH);
	}
	else {
		if ((CURLINE->data[m_Curs.x - m_cmargin - 1] < 32) ||
			(CURLINE->data[m_Curs.x - m_cmargin - 1] >= 128))
			SetMode(FARSI);
		else SetMode(ENGLISH);
	}

	UpdateCaretPos();
}

void CFtexedView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint lastp, currentp;
	int temp;

	if (m_bNewView && (nFlags & MK_LBUTTON))
		return;

	if (m_bNewView && !(nFlags & MK_LBUTTON)) {
		m_bNewView = FALSE;
	}

	if (!(nFlags & MK_LBUTTON))
		return;            

	lastp = m_Curs;
	m_Curs.x = (point.x + topleft.x) / logFont.lfWidth;
	temp = (point.y + topleft.y) / logFont.lfHeight;

	if (temp > m_Curs.y)
		GoDown(temp - m_Curs.y);
	else
		GoUp(m_Curs.y - temp);

	if (!ISL2R(CURLINE)) {
		if ((CURLINE->data[m_Curs.x] < 32) || (CURLINE->data[m_Curs.x] >= 128))
			SetMode(FARSI);
		else SetMode(ENGLISH);
	}
	else {
		if ((CURLINE->data[m_Curs.x - m_cmargin - 1] < 32) ||
			(CURLINE->data[m_Curs.x - m_cmargin - 1] >= 128))
			SetMode(FARSI);
		else SetMode(ENGLISH);
	}

	UpdateCaretPos();

	currentp = m_Curs;
	if (currentp == lastp)
		return;

	if (BeginSelPoint.x == -1) {
		if (IsGreater(currentp, lastp)) {
			BeginSelPoint = lastp;
			EndSelPoint = currentp;
		}
		else {
			BeginSelPoint = currentp;
			EndSelPoint = lastp;
		}
		InvalidateBlock(BeginSelPoint, EndSelPoint);
	}
	else {
		if (IsGreater(EndSelPoint, lastp)) {
			// Cursor was previously at the beginnig of block
			if (IsGreater(BeginSelPoint, currentp)) {
				lastp = BeginSelPoint;
				BeginSelPoint = currentp;
				InvalidateBlock(currentp, lastp);
			}
			else if (IsGreater(EndSelPoint, currentp)) {
				lastp = BeginSelPoint;
				BeginSelPoint = currentp;
				InvalidateBlock(lastp, currentp);
			}
			else {
				lastp = BeginSelPoint;
				BeginSelPoint = EndSelPoint;
				EndSelPoint = currentp;
				InvalidateBlock(lastp, currentp);
			}
		}
		else {
			// Cursor was previously at the end of block
			if (IsGreater(BeginSelPoint, currentp)) {
				lastp = EndSelPoint;
				EndSelPoint = BeginSelPoint;
				BeginSelPoint = currentp;
				InvalidateBlock(currentp, lastp);
			}
			else if (IsGreater(EndSelPoint, currentp)) {
				lastp = EndSelPoint;
				EndSelPoint = currentp;
				InvalidateBlock(currentp, lastp);
			}
			else {
				lastp = EndSelPoint;
				EndSelPoint = currentp;
				InvalidateBlock(lastp, currentp);
			}
		}

		if (BeginSelPoint == EndSelPoint)
				BeginSelPoint.x = EndSelPoint.x = -1;
	}
}

BOOL CFtexedView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	LPCTSTR lpszClass =
		AfxRegisterWndClass(NULL,
		LoadCursor(NULL, IDC_IBEAM),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL);

	return CWnd::Create(lpszClass, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	
}

void CFtexedView::OnUpdateMode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CString str;
	
	if ((mode == ENGLISH) && (ISL2R(CURLINE)))
		str.Format("English Text");
	else if ((mode == FARSI) && (ISL2R(CURLINE)))
		str.Format("Inserting Farsi in English");
	else if ((mode == ENGLISH) && (!ISL2R(CURLINE)))
		str.Format("Inserting English in Farsi");
	else
		str.Format("Farsi Text");
	pCmdUI->SetText(str);

}

void CFtexedView::OnUpdateLnCol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int xPos;

	if ISL2R(CURLINE)
		xPos = m_Curs.x - m_cmargin + 1;
	else
		xPos = MAX_TLEN / 2 - m_Curs.x;

	pCmdUI->Enable();
	CString str;
	str.Format("Ln %d, Col %d", m_Curs.y + 1, xPos);
	pCmdUI->SetText(str);
}

void CFtexedView::OnEditGo() 
{
	// TODO: Add your command handler code here

	CGotoDlg m_pGotoDialog; // goto line number dialog
				
	if(m_pGotoDialog.DoModal() != IDOK)
		return;

	if ((m_pGotoDialog.m_nLineNum < 1) || (m_pGotoDialog.m_nLineNum > pDoc->numLines + 1))
	{
		MessageBox("Invalid Line Number");
		return;
	}

	Unselect();

	int nLine = m_pGotoDialog.m_nLineNum;

	nLine--;
	if (nLine < m_Curs.y)
		GoUp(m_Curs.y - nLine);

	if (nLine > m_Curs.y)
		GoDown(nLine - m_Curs.y);
	UpdateCaretPos();
}

void CFtexedView::SetProperWindow(int mode)
{
	// mode = 0 : Consider both the 5-character-horizontal margin
	//				and consider the vertical margin (normal mode).
	// mode = 1 : Do not consider both the 5-character-horizontal 
	//				but consider the vertical margin (PageUp, 
	//				PageDown, etc).
	// mode = 2 : Do not consider any of margins. (Up or down arrow
	//				keys, etc).

	int dest, margin;

	if (mode == 0)
		margin = 1;
	else
		margin = 0;

	if ISL2R(CURLINE) {
		if ((m_Curs.x * logFont.lfWidth < topleft.x ) 
			|| ((m_Curs.x + margin) * logFont.lfWidth > topleft.x + window.right)) {

			if ((m_Curs.x + margin) * logFont.lfWidth > m_pmargin + window.right)
				dest = m_Curs.x * logFont.lfWidth - window.right / 2;
			else
				dest = m_pmargin;
			PerformScrolling(CPoint(dest, -1));
		}
	}
	else {
		if (((m_Curs.x - margin) * logFont.lfWidth < topleft.x ) 
			|| (m_Curs.x * logFont.lfWidth > topleft.x + window.right)) {
			if ((MAX_TLEN / 2 - m_Curs.x + margin) * logFont.lfWidth > window.right)
				dest = m_Curs.x * logFont.lfWidth - window.right / 2;
			else
				dest = m_pmargin;
			PerformScrolling(CPoint(dest, -1));
		}
	}

	if (mode == 2) {

		if (m_Curs.y * logFont.lfHeight < topleft.y ) {
			dest = m_Curs.y * logFont.lfHeight;
			PerformScrolling(CPoint(-1, dest));
		}
		else if ((m_Curs.y + 1) * logFont.lfHeight > topleft.y + window.bottom) {
			dest = (m_Curs.y + 1) * logFont.lfHeight - window.bottom;
			PerformScrolling(CPoint(-1, dest));
		}
	}
	else if ((m_Curs.y * logFont.lfHeight < topleft.y ) ||
		((m_Curs.y + 1) * logFont.lfHeight > topleft.y + window.bottom)) {

		dest = (m_Curs.y + 1) * logFont.lfHeight - window.bottom / 2;

		if (dest < 0) {
			dest = 0;
		}
		else if ((pDoc->numLines + 1 - m_Curs.y) * logFont.lfHeight < window.bottom / 2) 
			dest -= ((window.bottom + 1) / 2);

		PerformScrolling(CPoint(-1, dest));
	}
}

void CFtexedView::AdjustScrollers(void)
{
	// Claculate the page size.
	CSize docSize(MAX_TLEN * logFont.lfWidth - window.right, (pDoc->numLines + 1) * logFont.lfHeight);
	CSize pageSize(window.right, window.bottom);

	// Calculate the line size.
	CSize lineSize(0, logFont.lfHeight);

	// Adjust the scrollers.
	SetScrollSizes(MM_TEXT, docSize, pageSize, lineSize);
}

void CFtexedView::UpdateCaretPos(void)
{
	CPoint point;

	topleft = GetDeviceScrollPosition();

	if (((CFtexedApp *)AfxGetApp())->ActiveView != this)
		return;

	if (mode == ENGLISH)
		if ISL2R(CURLINE) {
			point.x = m_Curs.x * logFont.lfWidth - topleft.x - 1;
			point.y = m_Curs.y * logFont.lfHeight - topleft.y;
		}
		else {
			point.x = (m_Curs.x + 1) * logFont.lfWidth - topleft.x - 1;
			point.y = m_Curs.y * logFont.lfHeight - topleft.y;
		}
	else {
			point.x = m_Curs.x * logFont.lfWidth - topleft.x + 1;
			point.y = m_Curs.y * logFont.lfHeight - topleft.y + 7;
	}

	SetCaretPos(point);
}

void CFtexedView::SetMode(LANGUAGE inp)
{
	mode = inp;

	DestroyCaret();
	if (inp == FARSI)
		CreateCaret(m_pFaCaret);
	else
		CreateCaret(m_pEnCaret);
		
	ShowCaret();
}

UCHAR CFtexedView::prev_char()
{
	if (!ISL2R(CURLINE)) {
		int i = m_Curs.x + 1;
		while ((CURLINE->data[i] > 0 && CURLINE->data[i] < 8) || CURLINE->data[i] == 22) //eraab
			i++;
		return (CURLINE->data[i]);
	}else {
		int i = m_Curs.x - m_cmargin;
		while ((CURLINE->data[i] > 0 && CURLINE->data[i] < 8) || CURLINE->data[i] == 22) //eraab
			i++;
		return (CURLINE->data[i]);
	}
}


int CFtexedView::Map(UINT &ch)
{
	int retval = 0;
	
	/* return value is :
	0 : changing is done compeletly in this function.
	1 : we are in R2L direction and previous character (just right
		the cursor) is converted to uppercase and must be rewritten.
	2 : we are in L2R direction and the next character (just left 
		the cursor) is converted to uppercase and must be rewritten. */
	if (CURLINE -> len != 0 || ch != '>') {
		// 1 - mapping inserted char
		UCHAR prev = prev_char();
		if ((ch == 121 || ch == 117 || ch == 105 || ch == 104)
			&& join_to_prev(prev)
			&& !ISL2R(CURLINE)) {
			
			switch(ch) {

			case 121: //ghein!!
				ch = 231;
				break;

			case 117: //ein!!
				ch = 227; 
				break;

			case 105: //he!!
				ch = 250;
				break;

			case 104: //aa!!
				ch = 145;
				break;
			}
		}
		else if ((ch == 121 || ch == 117 || ch == 105 || 
			ch == 104) && join_to_prev(prev)
			&& ISL2R(CURLINE)) {

			switch(ch) {
			case 121: //ghein!!
				ch = 231;
				break;

			case 117: //ein!!
				ch = 227; 
				break;

			case 105: //he!!
				ch = 250;
				break;

			case 104: //aa!!
				ch = 145;
				break;
			}
		}

		else
			ch = map[UCHAR(ch)];

		// 2 - mapping next char (after inserted char if exists).
		UCHAR c;

		if (CURLINE -> len >= MAX_TLEN/2 - m_Curs.x || 	CURLINE->len >= m_Curs.x - m_cmargin) {
			if (!ISL2R(CURLINE))
				c = CURLINE -> data[m_Curs.x];
			else
				c = CURLINE -> data[m_Curs.x - m_cmargin - 1];

			if (join_to_prev(UCHAR(ch))) {

				switch(c) {
				case 229:  //ghein!!
					c = 230;
					break;

				case 232:  //ghein!!
					c = 231;
					break;

				case 228:  //ein!!
					c = 227; 
					break;

				case 225:  //ein!!
					c = 226; 
					break;

				case 251:  //he!!
					c = 250;
					break;

				case 144:  //aa!!
					c = 145;
					break;
				case 253:
					c = 252;
					break;
				}
			}
			else {
				switch(c) {
				case 230:  //ghein!!
					c = 229;
					break;

				case 231:  //ghein!!
					c = 232;
					break;

				case 227:  //ein!!
					c = 228; 
					break;

				case 226:  //ein!!
					c = 225; 
					break;

				case 250:  //he!!
					c = 251;
					break;

				case 145:  //aa!!
					c = 144;
					break;
				case 252:
					c = 253;
					break;
				}
			}

			if (!ISL2R(CURLINE))
				CURLINE -> data[m_Curs.x] = c;
			else if (CURLINE -> data[m_Curs.x - m_cmargin - 1] != c) {
				CURLINE -> data[m_Curs.x - m_cmargin - 1] = c;
				retval = 2;
			}
		}
	}

	// 3 - mapping prev char		
					
	// returns 1 if ch does not join to prev farsi char 
	if (not_join_to_prev(ch)) {
		// if ch does not join to prev farsi char a convert
		// for making prev farsi char upper case is needed
		
		int effective_prev;
		int effective_prev_prev;

		if (!ISL2R(CURLINE)) {
			effective_prev = m_Curs.x + SkipEraab(m_Curs.x) + 1;
			effective_prev_prev = effective_prev + SkipEraab(effective_prev) + 1;
			UCHAR c = farsi_upper_case(CURLINE -> data[effective_prev]);				

			if (c == 252) //ie
				if (!joins_to_next(CURLINE->data[effective_prev_prev]))
					c = 253;
			if (c != CURLINE -> data[effective_prev]){
				CURLINE -> data[effective_prev] = c;
				retval = 1;
			}
		}
		else {
			effective_prev = m_Curs.x - m_cmargin + SkipEraab(m_Curs.x - m_cmargin - 1);
			effective_prev_prev = effective_prev + SkipEraab(effective_prev) + 1;

			UCHAR c = farsi_upper_case(CURLINE -> data[effective_prev]);

			if (c == 252) //ie
				if (!joins_to_next(CURLINE->data[effective_prev_prev]))
					c = 253;

			CURLINE -> data[effective_prev] = c;
		}

/*
		if (!ISL2R(CURLINE)) {
			UCHAR c = farsi_upper_case(CURLINE -> data[m_Curs.x + 1]);				

			if (c == 252) //ie
				if (!joins_to_next(CURLINE->data[m_Curs.x + 2]))
					c = 253;
			if (c != CURLINE -> data[m_Curs.x + 1]){
				CURLINE -> data[m_Curs.x + 1] = c;
				retval = 1;
			}
		}
		else {
			UCHAR c = farsi_upper_case(CURLINE -> data[m_Curs.x - m_cmargin]);

			if (c == 252) //ie
				if (!joins_to_next(CURLINE->data[m_Curs.x - m_cmargin + 1]))
					c = 253;

			CURLINE -> data[m_Curs.x - m_cmargin] = c;
		}
*/
	}

	
		
	
	return retval;
}

int CFtexedView::joins_to_next (UCHAR c)
{
                                // çéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ
     char far *group_141_to_175 = "-1----1-1-1-1-1-1-1-1------1-1-1-11";
                                // ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛
     char far *group_224_to_254 = "1--11--11-1-1-1-1--1-1-1--11--1";

	 if (c == 0)
		 return 0;

	 if (c==19 || c==20 || c==12) return 0;

	 if (c<8 || c==22) return 1;

	 if (c>=141 && c<=175)
		return group_141_to_175[c-141]=='1';

	else if (c>=224)
        return group_224_to_254[c-224]=='1';

	//MEHR strech
	if (c==(UCHAR)'ã')
		return 1;
	//MEHR end

	return 0;
}
int CFtexedView::not_join_to_prev(UCHAR ch)
{
	
	if (ch >= ' ' && ch <= (UCHAR)'ä')  // english char or Farsi digit
		return 1;

	if (ch >= (UCHAR)'ç' && ch <= (UCHAR)'Ø')
		return 0;

	if (ch < 8 || ch == 22)             // e'raab
		return 0;

	if (ch == 19 || ch == 20 || ch == 12)   // taa and zaa tanhaa and te gerd
		return 0;

	if (ch >= (UCHAR)'‡' && ch <= (UCHAR)'˛')
		return 0;

	if (ch == (UCHAR)'ã')
		return 0;

	if (ch ==(UCHAR)210)
		return 0;
		
	return 1;
}

int CFtexedView::join_to_prev(UCHAR ch)
{
	//if prev char is one of these ,next char will join to prev
	if (ch == 142 || ch == 147 || ch == 149 || ch == 151 || 
		ch == 153 || ch == 155 || ch == 157 || ch == 159 || 
		ch == 161 || ch == 168 || ch == 170 || ch == 172 ||
		ch == 174 || ch == 175 || ch == 224 || ch == 227 ||
		ch == 228 || ch == 231 || ch == 232 || ch == 234 ||
		ch == 236 || ch == 238 || ch == 240 || ch == 243 || 
		ch == 245 || ch == 247 || ch == 250 || ch == 251 ||
		ch == 254)
		return 1;
	return 0;
}

UCHAR CFtexedView::farsi_upper_case ( UCHAR c )
{
							// çéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ	
	char *group_141_to_175 = "çèèêëííîîññòòööúúûû††¢£§•¶ßß©©´´≠≠.";
							// ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛
	char *group_224_to_254 = ".·‚‚·ÂÊÊÂÈÈÎÎÌÌÔÔÒÚÒÙÙˆˆ¯˘˘˘¸˝¸";

	if (c >= 141 && c<175)
		return (UCHAR)group_141_to_175[c - 141];

	else if (c > 224 && c <= 254)
        return (UCHAR)group_224_to_254[c - 224];

	else if (c == 175)
		return(map[88]); //taa tanhaa 

	else if (c == 224)
		return(map[90]); //zaa tanhaa

	return c;
}

/**
 * Added by Shiva 
 * to remove shif+space problem
**/

UCHAR CFtexedView::ShiftSpaceMap ( UCHAR c )
{

	switch(c) {
		case 230:  //ghein!!
			c = 229;
			break;

		case 231:  //ghein!!
			c = 232;
			break;

		case 227:  //ein!!
			c = 228; 
			break;

		case 226:  //ein!!
			c = 225; 
			break;

		case 250:  //he!!
			c = 251;
			break;

		case 145:  //aa!!
			c = 144;
			break;
		case 252: //ie
			c = 253;
			break;
		case 254: //ie 
			c = 253;
			break;
		}
	return c;
}


int CFtexedView::FindLine(int LineNo, CFtexedDoc::LINETYPE **Line)
{
	(*Line) = pDoc->m_head;
	for (int i = LineNo; i > 0; i--) {
		if ((*Line)->next == NULL)
			break;
		(*Line) = (*Line)->next;
	}

	return i;
}

BOOL CFtexedView::IsSeparator(BYTE ch)
{
	switch (ch) {

	case 0:
	case 14:
	case 21:
	case 23:
	case 25:
	case 27:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 58:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 91:
	case 92:
	case 93:
	case 94:
	case 95:
	case 96:
	case 123:
	case 124:
	case 125:
	case 126:
	case 138:
	case 139:
	case 140:
	case 181:
	case 182:
	case 183:
	case 184:
	case 189:
	case 190:
	case 196:
	case 197:
	case 198:
	case 199:
	case 202:
	case 203:
	case 204:
	case 206:
	case 207:
	case 208:
	case 209:
	case 210:
	case 211:
	case 212:
	case 213:
	case 214:
	case 215:
	case 216:
	case 221:
	case 222:
	case 255:
		return TRUE;
		
	default:
		return FALSE;
	}
	
	return FALSE;
}

#define FAR_NORMAL		0
#define ENG_NORMAL		1
#define FAR_COMMENT		2
#define ENG_COMMENT		3
#define FAR_COMMAND		4
#define ENG_COMMAND		5
#define ERAAB           6
#define ENG_LINE_MARK   7

void CFtexedView::AssignColor(BYTE *logical, BYTE *c_vec, BOOL isFarsiLine)
{
	enum {Normal, Comment, Command} state = Normal;
	enum {Far, Eng} mode;

	if (!isFarsiLine)
		 mode = Eng;
	else
		mode = Far;

	if (mode == Far && *logical == 183)
		state = Comment;
	else if (mode == Far && (*logical == 210 || *logical == 92))
		state = Command;
	else state = Normal;

	if (logical[0] < 32 || logical[0] >= 128) {
		if (state == Comment)
			c_vec[0] = FAR_COMMENT;
		else
			c_vec[0] = (IsLogicalEraab(*logical) ? ERAAB : FAR_NORMAL);
	}
	else
		c_vec[0] = (((*logical == '>') && !isFarsiLine) ? ENG_LINE_MARK : ENG_NORMAL);

	for (int i = 1; i < MAX_TLEN / 2; i++) {

		if (((logical[i] == 210 || logical[i] == 92) && state != Comment) || state == Command) {
			if (state == Command)
				state = Normal;
			else c_vec[i++] = (logical[i] == 210) ? FAR_NORMAL : ENG_NORMAL;
			
			while (!IsLogicalCommandSeparator(logical[i])) {
				if (logical[i] < 32 || logical[i] >= 128)
					c_vec[i] = FAR_COMMAND;
				else c_vec[i] = ENG_COMMAND;
				i++;
			}
		}

		if (!logical[i])
			return;
	
		if (mode == Far && logical[i] == 183 && logical[i - 1] != 210)
			state = Comment;
		else if (mode == Eng && logical[i] == 37 && logical[i - 1] != 92)
			state = Comment;

		if (logical[i] < 32 || logical[i] >= 128) {
			if (state == Comment)
				c_vec[i] = FAR_COMMENT;
			else
				c_vec[i] = (IsLogicalEraab(logical[i])) ? ERAAB : FAR_NORMAL;
		}
		else {
			if (state == Comment)
				c_vec[i] = ENG_COMMENT;
			else
				c_vec[i] = ENG_NORMAL;

		}

		/*if (state != Comment && (logical[i] == 92 || logical[i] == 210))
			state = Command;
		*/
		if (state != Comment && (logical[i] == 92 && logical[i-1] != 92 ||
			logical[i] == 210 && logical[i-1] != 210))
			state = Command;		
	}

}

#define IS_COMPLETELY_SELECTED(l) (BeginSelPoint.x != -1 && BeginSelPoint.y < (l) && EndSelPoint.y > (l))

#define IS_SELECTED(j, l, t) ((BeginSelPoint.x != -1) && \
((BeginSelPoint.y == (l) && EndSelPoint.y != (l) && \
((t) == L2R ? (BeginSelPoint.x <= j) : (BeginSelPoint.x >= j))) || \
(BeginSelPoint.y != (l) && EndSelPoint.y == (l) && \
((t) == L2R ? (EndSelPoint.x > j) : (EndSelPoint.x < j))) || \
(BeginSelPoint.y == (l) && EndSelPoint.y == (l) && \
((t) == L2R ? (EndSelPoint.x > j && BeginSelPoint.x <= j) : (EndSelPoint.x < j && BeginSelPoint.x >= j)))))

void CFtexedView::PrintLine(CDC *pDC, int x, int y, BYTE *doclineParam, int length)
{

	BOOL isFarsiLine = (doclineParam[0] != '>');

	BYTE docline[MAX_TLEN / 2 + 1];

	RemapCharacters(doclineParam, docline);

	enum {Farsi, English, Selected} pmode = Farsi;
	enum {L2R, R2L} direction = (*docline == '>') ? L2R : R2L;
	enum {NORMAL_FARSI, NORMAL_ENGLISH, SELECTED, FARSI_COMMENT, FARSI_COMMAND,
		ENGLISH_COMMENT, ENGLISH_COMMAND, FARSI_ERAAB, START_OF_ENGLISH_LINE} last_state = NORMAL_FARSI;

	pDC->SetBkMode(OPAQUE);
	pDC->SetBkColor(background);
	pDC->SetTextColor(normal_farsi_text);

	pDC->TextOut(x, y, pDoc->blanks);
		
	int i = 0;
	int j = 0;

	int line_num = y / logFont.lfHeight;

	static BYTE line_head[MAX_TLEN / 2];
	strcpy((char *)line_head, (char *)docline);
	
	BYTE *line = line_head;
	enum {Far, Eng} mode;

	if (*line_head != '>') {
		j = MAX_TLEN / 2 - length;
		line += j;

		x = j * logFont.lfWidth;
		i = j;
		mode = Far;
	}

	else {
		line[length] = 0;
		j = m_cmargin;
		i = 0;
		mode = Eng;
	}

	if (IS_COMPLETELY_SELECTED(line_num)) {
		
		if (last_state != SELECTED) {
			pDC->SetBkMode(OPAQUE);
			pDC->SetBkColor(selection_background);
			pDC->SetTextColor(selected_text);
			last_state = SELECTED;
		}

		if (line[0] == 0)
			pDC->TextOut(x - logFont.lfWidth, y, "");
		else
			pDC->TextOut(x, y, (char *)line);
		
		return;

	}

	BYTE portion[3];
	static char lgline[MAX_TLEN / 2];
	BYTE c_vec[MAX_TLEN / 2];

	strcpy(lgline, (char *)pDoc->blanks);
	pDoc->ConvertToLogical((const char *)line_head, lgline);
	AssignColor((BYTE *)lgline, c_vec, isFarsiLine);
	pDoc->ConvertToPhysical((const char *)lgline, (char *)line_head,
		(BYTE *)c_vec, isFarsiLine);

	while (*line) {
		if (IS_SELECTED(j, line_num, direction)) {
			if (last_state != SELECTED) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(selection_background);
				pDC->SetTextColor(selected_text);
				last_state = SELECTED;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);
		}
		else if (c_vec[i] == FAR_NORMAL) {
			if (last_state != NORMAL_FARSI) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(background);
				pDC->SetTextColor(normal_farsi_text);
				last_state = NORMAL_FARSI;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}
		else if (c_vec[i] == FAR_COMMENT) {
			if (last_state != FARSI_COMMENT) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(background);
				pDC->SetTextColor(m_bHighlight ? commented_text : normal_farsi_text);
				last_state = FARSI_COMMENT;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}

		else if (c_vec[i] == ERAAB) {
			if (last_state != FARSI_ERAAB) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(background);
				pDC->SetTextColor(m_bHighlight ? eraab_text : normal_farsi_text);
				last_state = FARSI_ERAAB;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}

		else if (c_vec[i] == FAR_COMMAND) {
			if (last_state != FARSI_COMMAND) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(background);
				pDC->SetTextColor(m_bHighlight ? command_text : normal_farsi_text);
				last_state = FARSI_COMMAND;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}

		else if (c_vec[i] == ENG_NORMAL) {
			if (last_state != NORMAL_ENGLISH) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(english_background);
				pDC->SetTextColor(normal_english_text);
				last_state = NORMAL_ENGLISH;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}
		else if (c_vec[i] == ENG_COMMENT) {
			if (last_state != ENGLISH_COMMENT) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(english_background);
				pDC->SetTextColor(m_bHighlight ? commented_text : normal_english_text);
				last_state = ENGLISH_COMMENT;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}

		else if (c_vec[i] == ENG_LINE_MARK) {
			if (last_state != START_OF_ENGLISH_LINE) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(english_background);
				pDC->SetTextColor(english_line_marker);
				last_state = START_OF_ENGLISH_LINE;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}

		else if (c_vec[i] == ENG_COMMAND) {
			if (last_state != ENGLISH_COMMAND) {
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(english_background);
				pDC->SetTextColor(m_bHighlight ? command_text : normal_english_text);
				last_state = ENGLISH_COMMAND;
			}
			portion[0] = *line;
			portion[1] = 0;
			pDC->TextOut(x, y, (char *) portion);

		}

		i++;
		j++;
		line++;
		x = j * logFont.lfWidth;
	}
}

void CFtexedView::ValidateCursorPos()
{
	if ISL2R(CURLINE) {
		if ((m_Curs.x - m_cmargin) > CURLINE->len)
			m_Curs.x = CURLINE->len + m_cmargin;
		else if (m_Curs.x <= m_cmargin)
			m_Curs.x = m_cmargin + 1;
	}
	else {
		if ((MAX_TLEN / 2 - 1 - CURLINE->len) > m_Curs.x)
			m_Curs.x = MAX_TLEN / 2 - 1 - CURLINE->len;
		else if (m_Curs.x >= MAX_TLEN / 2)
			m_Curs.x = MAX_TLEN / 2 - 1;
	}
}

void CFtexedView::GoUp(int howmany)
{
	if (howmany > m_Curs.y)
		howmany = m_Curs.y;

	m_Curs.y -= howmany;
	special_mode = 0;
	inserted_farsi_num = 0;
	for (int i = howmany; i > 0; i --)
		CURLINE = CURLINE->last;
	ValidateCursorPos();

	if (howmany == 0)
		return;

	if (howmany == 1)
		SetProperWindow(2);
	else
		SetProperWindow(1);
}

void CFtexedView::GoDown(int howmany)
{
	if (howmany > pDoc->numLines - m_Curs.y)
		howmany = pDoc->numLines - m_Curs.y;

	m_Curs.y += howmany;
	special_mode = 0;
	inserted_farsi_num = 0;
	for (int i = howmany; i > 0; i--)
		CURLINE = CURLINE->next;
	ValidateCursorPos();

	if (howmany == 0)
		return;

	if (howmany == 1)
		SetProperWindow(2);
	else 
		SetProperWindow(1);
}

void CFtexedView::DelChar(void)
{
	if ISL2R(CURLINE)
		for (int i = m_Curs.x - m_cmargin; i < CURLINE->len; i++)
			CURLINE->data[i] = CURLINE->data[i + 1];
	else
		for (int i = m_Curs.x; i >= MAX_TLEN / 2 - CURLINE->len; i--)
			CURLINE->data[i] = CURLINE->data[i - 1];

	(CURLINE->len)--;
}

void CFtexedView::Handle$(UINT nChar) 
{
		if ((nChar == 36) && (mode == FARSI) && (!ISL2R(CURLINE))) //$
		SetMode(ENGLISH);
}

void CFtexedView::HandleSpecialKeys(UINT nChar) 
{
	if ((nChar == 92) && (mode == FARSI)) { /*\*/
		if (!ISL2R(CURLINE))
		{
			if (CURLINE->data[m_Curs.x + 2] != 210)
			{
				SetMode(ENGLISH);
		//		OnKeyDown(VK_LEFT, 0, 0);
				special_mode = 1;
			}
		}
		else
		{
			SetMode(ENGLISH);
		}
	}
	else if ((nChar == 64) && (mode == FARSI)) { //@
		numchar1 ++;
		shift = 0;
		if (numchar1 == 1) {
			OnChar(64, 0, 0);	
			OnKeyDown(VK_RIGHT, 0, 0);
		}
		SetMode(ENGLISH);
		if (numchar1 == 2) 
			numchar1 = 0;
	}
	else if (!pair_brackets_and_braces)
		return;
	/* No more checks will be performed if we do not like to use bracket/brace pairing */
	else if ((nChar == 123) && (numchar2==0)) { //{}
		numchar1 ++;
		shift = 0;
		if (numchar1 == 1) {
			if (mode == ENGLISH) {
				OnChar(125, 0, 0);			
				OnKeyDown(VK_LEFT, 0, 0);
				numchar1 = 0;
			}
			else {
				if ISL2R(CURLINE)
					OnKeyDown(VK_DELETE, 0, 0);
				else
					OnChar(BACKSPACE, 0, 0);
				OnChar(125, 0, 0);
				OnChar(123, 0, 0);
				OnKeyDown(VK_RIGHT, 0, 0);
				if (numchar1 == 2)
					numchar1 = 0;
			}
		}
	}
	else if ((nChar == 125) && (numchar1 == 0)) { //{}
		numchar2++;
		shift = 0;
		if (numchar2 == 1) {
			if (mode == ENGLISH) {
				if ISL2R(CURLINE)
					OnChar(BACKSPACE, 0, 0);		
				else
					OnKeyDown(VK_DELETE, 0, 0);
				OnChar(123, 0, 0);
				OnChar(125, 0, 0);			
				OnKeyDown(VK_LEFT, 0, 0);
				if (numchar2 == 2)
					numchar2 = 0;
			}
			else{
				OnChar(123, 0, 0);
				OnKeyDown(VK_RIGHT, 0, 0);				
				numchar2 = 0;
			}						
		}
	}
	else if ((nChar == 91) && (numchar2 == 0) && (mode == ENGLISH)) { //[ENGLISH]
		numchar1++;
		shift = 0;
		if (numchar1 == 1) {
			OnChar(93, 0, 0);			
			OnKeyDown(VK_LEFT, 0, 0);	
			numchar1 = 0;			
		}
	}
	else if ((nChar == 93) && (numchar1 == 0) && (mode == ENGLISH)) { //[ENGLISH]
		numchar2++;
		shift = 0;
		if (numchar2 == 1) {		
			if ISL2R(CURLINE)
				OnChar(BACKSPACE, 0, 0);		
			else
				OnKeyDown(VK_DELETE, 0, 0);
			OnChar(91, 0, 0);
			OnChar(93, 0, 0);			
			OnKeyDown(VK_LEFT, 0, 0);
			if (numchar2 == 2)
				numchar2 = 0;
		}		
	} else if ((nChar == 79) && (numchar2 == 0) && (mode == FARSI)) { //[FARSI]
		numchar1++;
		shift = 0;
		if (numchar1 == 1) {			
			if ISL2R(CURLINE)
				OnKeyDown(VK_DELETE, 0, 0);
			else
				OnChar(BACKSPACE, 0, 0);
			OnChar(80, 0, 0);
			OnChar(79, 0, 0);
			OnKeyDown(VK_RIGHT, 0, 0);
			if (numchar1 == 2)
				numchar1 = 0;			
		}
	} else if ((nChar == 80) && (numchar1 == 0) && (mode == FARSI)) { //[FARSI]
		numchar2++;
		shift = 0;
		if (numchar2 == 1) {			
			OnChar(79, 0, 0);
			OnKeyDown(VK_RIGHT, 0, 0);				
			numchar2 = 0;
		}
	}
}

void CFtexedView::ShrinkRect(CRect &Rect)
{
	if (Rect.left < 0)
		Rect.left = 0;
	else if (Rect.left > window.right)
		Rect.left = window.right;

	if (Rect.right < 0)
		Rect.right = 0;
	else if (Rect.right > window.right)
		Rect.right = window.right;

	if (Rect.top < 0)
		Rect.top = 0;
	else if (Rect.top > window.bottom)
		Rect.top = window.bottom;

	if (Rect.bottom < 0)
		Rect.bottom = 0;
	else if (Rect.bottom > window.bottom)
		Rect.bottom = window.bottom;
}

BOOL CFtexedView::IsGreater(CPoint p1, CPoint p2)
{
	CFtexedDoc::LINETYPE *Line;

	if (p1.y > p2.y)
		return TRUE;
	if (p1.y < p2.y)
		return FALSE;
	FindLine(p1.y, &Line);
	if (ISL2R(Line))
		return (p1.x > p2.x);
	else
		return (p1.x < p2.x);
}

void CFtexedView::InvalidateBlock(CPoint p1, CPoint p2)
{
	CFtexedView *(Views[2]);
	CFtexedDoc::LINETYPE *BeginLine;
	CPoint BeginP, EndP;

	FindAllViews(Views);

	if (p2.y == -1) {
		CRect rect;

		rect.top = p1.y * logFont.lfHeight - topleft.y;
		rect.bottom = window.bottom;
		rect.left = 0;
		rect.right = window.right;
		for (int l = 0; l < 2; l++)
			if (Views[l] != NULL) {
				Views[l]->InvalidateRect(&rect);
				Views[l]->UpdateWindow();
			}
			else 
				break;
		return;
	}

	FindLine(p1.y, &BeginLine);
	if (p1.x == -1)
		if (ISL2R(BeginLine))
			p1.x = m_cmargin;
		else
			p1.x = MAX_TLEN / 2;
	if (p1.y != p2.y) {
		if (ISL2R(BeginLine)) {
			BeginP.x = p1.x;
			EndP.x = m_cmargin + BeginLine->len;
		}
		else {
			BeginP.x = MAX_TLEN / 2 - BeginLine->len;
			if (BeginLine->len == 0)
				BeginP.x--;
			EndP.x = p1.x + 1;
		}
		BeginP.y = p1.y;
		EndP.y = p1.y + 1;
		for (int l = 0; l < 2; l++)
			if (Views[l] != NULL)
				Views[l]->LogicalInvalidate(BeginP, EndP);
			else 
				break;
	}
	else {
		if (p2.x == -1)
			if (ISL2R(BeginLine))
				p2.x = m_cmargin + BeginLine->len;
			else
				p2.x = MAX_TLEN / 2 - BeginLine->len - 1;

		if (ISL2R(BeginLine)) {
			BeginP.x = p1.x;
			EndP.x = p2.x + 1;
		}
		else {
			BeginP.x = p2.x;
			EndP.x = p1.x + 1;
		}
		BeginP.y = p2.y;
		EndP.y = p2.y + 1;
		for (int l = 0; l < 2; l++)
			if (Views[l] != NULL)
				Views[l]->LogicalInvalidate(BeginP, EndP);
			else 
				break;
	}

	for (int i = p1.y + 1; i < p2.y; i++) {
		BeginLine = BeginLine->next;
		if (ISL2R(BeginLine)) {
			BeginP.x = m_cmargin;
			EndP.x = m_cmargin + BeginLine->len;
		}
		else {
			BeginP.x = MAX_TLEN / 2 - BeginLine->len;
			if (BeginLine->len == 0)
				BeginP.x--;
			EndP.x = MAX_TLEN / 2;
		}
		BeginP.y = i;
		EndP.y = i + 1;
		for (int l = 0; l < 2; l++)
			if (Views[l] != NULL)
				Views[l]->LogicalInvalidate(BeginP, EndP);
			else 
				break;
	}

	if (p2.x == -1)
		if (ISL2R(BeginLine->next))
			p2.x = m_cmargin + BeginLine->next->len;
		else
			p2.x = MAX_TLEN / 2 - BeginLine->next->len;
	if (p1.y != p2.y) {
		if (ISL2R(BeginLine->next)) {
			BeginP.x = m_cmargin;
			EndP.x = p2.x + 1;
		}
		else {
			BeginP.x = p2.x;
			if (BeginLine->next->len == 0)
				BeginP.x--;
			EndP.x = MAX_TLEN / 2;
		}
		BeginP.y = p2.y;
		EndP.y = p2.y + 1;
		for (int l = 0; l < 2; l++)
			if (Views[l] != NULL)
				Views[l]->LogicalInvalidate(BeginP, EndP);
			else 
				break;
	}

	for (int l = 0; l < 2; l++)
		if (Views[l] != NULL)
			Views[l]->UpdateWindow();
		else 
			break;
}

void CFtexedView::Unselect(void)
{
	if (BeginSelPoint.x != -1) {
		CPoint temp = BeginSelPoint;
		BeginSelPoint.x = -1;
		InvalidateBlock(temp, EndSelPoint);
	}
}

void CFtexedView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(BeginSelPoint.x != -1);
}

void CFtexedView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(BeginSelPoint.x != -1);
}


void CFtexedView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(((CFtexedApp *)AfxGetApp())->CBLen != 0);
}

void CFtexedView::OnEditCut()
{
	// TODO: Add your command handler code here

	OnEditCopy();
	RemoveSelectedArea();
}

void CFtexedView::OnEditCopy() 
{
	// TODO: Add your command handler code here

	char *buff;
	CFtexedDoc::LINETYPE *FirstLine;
	int ptr = 0;

	FindLine(BeginSelPoint.y, &FirstLine);
	buff = new(char[NumberOfBytes(FirstLine)]);

	if (BeginSelPoint.y == EndSelPoint.y) {
		if (ISL2R(FirstLine)) {
			buff[ptr++] = '>';
			for (int i = BeginSelPoint.x; i < EndSelPoint.x; i++)
				buff[ptr++] = FirstLine->data[i - m_cmargin];
		}
		else {
			for (int i = EndSelPoint.x + 1; i <= BeginSelPoint.x; i++)
				buff[ptr++] = FirstLine->data[i];
		}
		buff[ptr] = 0;
	}
	else {
		if (ISL2R(FirstLine)) {
			buff[ptr++] = '>';
			for (int i = BeginSelPoint.x; i < m_cmargin + FirstLine->len; i++)
				buff[ptr++] = FirstLine->data[i - m_cmargin];
		}
		else {
			for (int i = MAX_TLEN / 2 - FirstLine->len; i <= BeginSelPoint.x; i++)
				buff[ptr++] = FirstLine->data[i];
		}
		buff[ptr++] = 0;

		for (int i = BeginSelPoint.y + 1; i < EndSelPoint.y; i ++) {
			int base;

			FirstLine = FirstLine->next;
			if (ISL2R(FirstLine))
				base = 0;
			else
				base = MAX_TLEN / 2 - FirstLine->len;
			for (int j = 0; j < FirstLine->len; j++)
				buff[ptr++] = FirstLine->data[base + j];
			buff[ptr++] = 0;
		}

		FirstLine = FirstLine->next;
		if (ISL2R(FirstLine)) {
			for (int i = m_cmargin; i < EndSelPoint.x; i++)
				buff[ptr++] = FirstLine->data[i - m_cmargin];
		}
		else {
			for (int i = EndSelPoint.x + 1; i < MAX_TLEN / 2 ; i++)
				buff[ptr++] = FirstLine->data[i];
		}
		buff[ptr] = 0;
	}

	// Set proper clipboard length
	((CFtexedApp *)AfxGetApp())->CBLen = ptr;

	// Release previously allocated memory for clipboard
	if ((CFtexedApp *)AfxGetApp() != NULL)
		delete []((CFtexedApp *)AfxGetApp())->ClipBoard;

	// New contents of clipboard
	((CFtexedApp *)AfxGetApp())->ClipBoard = buff;
}

void CFtexedView::OnEditPaste() 
{
	if (BeginSelPoint.x != -1)
		RemoveSelectedArea();
	OnEditOnlyPaste();
}

void CFtexedView::OnEditOnlyPaste() 
{
	// TODO: Add your command handler code here
	Unselect();

	CFtexedView *(Views[2]);
	CFtexedDoc::LINETYPE *line = CURLINE, *temp;
	char firstline[MAX_TLEN / 2 + 1];
	char *buff = ((CFtexedApp *)AfxGetApp())->ClipBoard;
	int bufflen = ((CFtexedApp *)AfxGetApp())->CBLen, savelen;
	int mode;   // = 0 if first line of text is L2R
				// = 1 if first line of text is R2L

	int lengthOfFirstBufferLine = strlen(buff); /* Mehrdad: Taking the fact that
												   clipboard buffer lines are null terminated,
												   strlen(buff) would be the length of the first
												   line in the clipboard.
	                                             */
	if (CURLINE->len + lengthOfFirstBufferLine > MAX_TLEN / 2 - 1)
	{
		AfxMessageBox("Copying the clipboard data would make the current line longer than the maximum line size in the editor.\
Try pasting the clipboard data in a shorter or an empty line.");
		shift = 0;
		ctrl = 0;
		return;
	}

	if (ISL2R(CURLINE)) {
		if (buff[0] == '>')
			buff++;

		CURLINE->data[CURLINE->len] = 0;
		strcpy(firstline, (char *)CURLINE->data + (m_Curs.x - m_cmargin));
		CURLINE->data[m_Curs.x - m_cmargin] = 0;
		strcat((char *)CURLINE->data, buff);
		CURLINE->len += strlen(buff) - strlen(firstline);
		mode = 0;
	}
	else {
		if (buff[0] == '>')
			buff++;

		int savelen = strlen(buff);

		for (int i = MAX_TLEN / 2 - CURLINE->len, j = 0; i <= m_Curs.x ; i++, j++) {
			firstline[j] = CURLINE->data[i];
			CURLINE->data[i] = 255;
		}
		firstline[j] = 0;
		for (i = m_Curs.x - savelen, j = 0; i < m_Curs.x; i++, j++)
			CURLINE->data[i + 1] = buff[j];
		CURLINE->len += savelen - strlen(firstline);
		mode = 1;
	}

	savelen = strlen(buff);
	bufflen -= (savelen + 1);
	while (bufflen > 1) {
		buff += (savelen + 1);
		savelen = strlen(buff);

		if ((!IsRunningOnNT()) && (pDoc->numLines >= MAX_LINE_NUM_IN_WIN9X))
		{
			AfxMessageBox("FarsiTeX Editor failed to paste the entire content of clipboard because documents larger than 2048 lines are not supported in Win9x.");
			shift = 0;
			ctrl = 0;
			return;
		}

		temp = new CFtexedDoc::LINETYPE;
		temp->data = new BYTE[MAX_TLEN / 2 + 1];
		temp->last = line;
		temp->next = line->next;
		if (line->next != NULL)
			line->next->last = temp;
		line->next = temp;
		temp->base = 0;
		temp->len = savelen;
		strcpy((char *)temp->data, pDoc->blanks);
		if (buff[0] == '>')
			strcpy((char *)temp->data, buff);
		else
			strcpy((char *)temp->data + MAX_TLEN / 2 - savelen, buff);
		bufflen -= (savelen + 1);
		pDoc->numLines++;
		line = temp;
	}

	if (strlen(firstline) != 0) {
		if (line == CURLINE) {
			if ISL2R(CURLINE) {
				CURLINE->data[CURLINE->len] = 0;
				strcat((char *)CURLINE->data, firstline);
			}
			else {
				for (int i = MAX_TLEN / 2 - CURLINE->len - strlen(firstline), j = 0; (WORD) j < strlen(firstline); i++, j++)
					CURLINE->data[i] = firstline[j];
			}
			CURLINE->len += strlen(firstline);
		}
		else {
			savelen = strlen(firstline);
			
			if ((!IsRunningOnNT()) && (pDoc->numLines >= MAX_LINE_NUM_IN_WIN9X))
			{
				AfxMessageBox("FarsiTeX Editor failed to paste the entire content of clipboard because documents larger than 2048 lines are not supported in Win9x.");
				shift = 0;
				ctrl = 0;
				return;
			}

			temp = new CFtexedDoc::LINETYPE;
			temp->data = new BYTE[MAX_TLEN / 2 + 1];
			temp->last = line;
			temp->next = line->next;
			if (line->next != NULL)
				line->next->last = temp;
			line->next = temp;
			temp->base = 0;
			temp->len = savelen;
			strcpy((char *)temp->data, pDoc->blanks);
			if (mode == 0) {
				temp->len++;
				temp->data[0] = '>';
				temp->data[1] = 0;
				strcat((char *)temp->data, firstline);
			}
			else
				strcpy((char *)temp->data + MAX_TLEN / 2 - savelen, firstline);
			pDoc->numLines++;
		}
	}

	FindAllViews(Views);
	for (int k = 0; k < 2; k++)
		if (Views[k] != NULL)
			Views[k]->AdjustScrollers();
		else
			break;

	if (!(pDoc->IsModified())) {
		pDoc->SetModifiedFlag(TRUE);
		pDoc->SetTitle(pDoc->GetTitle() + " *");
	}

	InvalidateBlock(CPoint(-1, m_Curs.y), CPoint(-1,-1));
}

void CFtexedView::OnUpdateFarsi(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck(mode == FARSI);
}

void CFtexedView::OnUpdateEnglish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck(mode == ENGLISH);
}

void CFtexedView::OnFarsi() 
{
	// TODO: Add your command handler code here
	OnChar(CTRLF, 0, 0);
}

void CFtexedView::OnEnglish() 
{
	// TODO: Add your command handler code here
	OnChar(CTRLE, 0, 0);
}

void CFtexedView::FindAllViews(CFtexedView **Views)
{
	CSplitterWnd *temp = (CSplitterWnd *)GetParent();
	int k = 0;

	for (int i = temp->GetRowCount() - 1; i >= 0; i--)
		for (int j = temp->GetColumnCount() - 1; j >= 0; j--)
			Views[k++] = (CFtexedView *)(temp->GetPane(i, j));

	for (; k < 2; k++)
		Views[k] = NULL;
}

int CFtexedView::NumberOfBytes(CFtexedDoc::LINETYPE *FirstLine)
{
	int sum, i;

	if (BeginSelPoint.y == EndSelPoint.y) {
		if (ISL2R(FirstLine))
			sum = EndSelPoint.x - BeginSelPoint.x + 2;
		else
			sum = BeginSelPoint.x - EndSelPoint.x + 1;
	}
	else {
		if (ISL2R(FirstLine))
			sum = m_cmargin + FirstLine->len - BeginSelPoint.x + 2;
		else
			sum = FirstLine->len + BeginSelPoint.x + 2 - MAX_TLEN / 2;

		for (i = BeginSelPoint.y + 1; i < EndSelPoint.y; i ++) {
			FirstLine = FirstLine->next;
			sum += FirstLine->len + 1;
		}

		FirstLine = FirstLine->next;
		if (ISL2R(FirstLine))
			sum += EndSelPoint.x - m_cmargin + 1;
		else
			sum += MAX_TLEN / 2 - EndSelPoint.x;
	}

	return sum;
}

void CFtexedView::LogicalInvalidate(CPoint BeginP, CPoint EndP)
{
	CRect InvRect;

	InvRect.top = BeginP.y * logFont.lfHeight - topleft.y;
	InvRect.left = BeginP.x * logFont.lfWidth - topleft.x;
	InvRect.bottom = EndP.y * logFont.lfHeight - topleft.y;
	InvRect.right = EndP.x * logFont.lfWidth - topleft.x;
	ShrinkRect(InvRect);
	InvalidateRect(&InvRect);
}

void CFtexedView::OnEditSearch() 
{
	// TODO: Add your command handler code here
	CSearch m_SearchDlg;

	if (!SearchStr.IsEmpty())
		m_SearchDlg.str = SearchStr;
	
	if(m_SearchDlg.DoModal() != IDOK)
		return;


	if (m_SearchDlg.str.IsEmpty())
		return;

	SearchStr = m_SearchDlg.str;

	//Search in Text
	search_is_done = false;
	Search();
}

void CFtexedView::OnEditSearchAgain() 
{
	// TODO: Add your command handler code here
	search_is_done = false;
	Search();
}

BOOL CFtexedView::Search() 
{
	int length = SearchStr.GetLength();
	
	CFtexedDoc::LINETYPE *head = pDoc->m_current;
	CFtexedDoc::LINETYPE *tmp = pDoc->m_head;

	UINT begin_Line = 0;
	while(tmp != head){
		tmp = tmp->next;
		begin_Line++;
	}

	BOOL find = false;
	LANGUAGE find_mode;
	UINT X = 0,Y = 0;
	UINT searchpoint;
	UINT begin_X = 0;

	if (head->data[0] != '>') {
		searchpoint = MAX_TLEN/2 - 1;
		begin_X = searchpoint - m_Curs.x ;
	}else {
		searchpoint = 0;
		begin_X = m_Curs.x -m_cmargin;
	}
	
	
	while(head != NULL) {
		if(head->data[0] != '>') {
			searchpoint = MAX_TLEN/2 - 1;
			for(int i = begin_X; i < head->len; i++) {
				UCHAR c1 = head->data[searchpoint - i];
				UCHAR c2 = SearchStr[length - 1];
				int t = 1;
				if(c1 == c2) { 
					for(int j = i + 1; j < length + i; j++) {
						t++;
						c1 = head->data[searchpoint - j];
						c2 = SearchStr[length - t];
						if(c1 != c2)
							break;
					}
					if(c1 == c2) {
						find_mode = FARSI;
						X = i;
						find = true;
					}
				}
				if(find)
					break;
			}
			begin_X = 0;
			Y++;
		}else {
			searchpoint = 0;
			if (begin_X == 0)
				begin_X = 1; /* '>' at the beginning of English lines should NOT be found. */
			for(int i = begin_X ; i < head->len ; i++) {
				UCHAR c1 = head->data[i];
				UCHAR c2 = SearchStr[0];
				int t = 0;
				if(c1 == c2) {
					for(int j = i+1; j < length+i; j++) {
						t++;
						c1 = head->data[j];
						c2 = SearchStr[t];
						if(c1 != c2)
							break;
					}
					if(c1 == c2) {
						find_mode = ENGLISH;
						X = i;
						find = true;
					}
				}
				if(find)
					break;
			}
			begin_X = 0;
			Y++;
		}

	if(find)
		break;
	head = head->next;
	}
				
	if(find) {
			Unselect();
			ctrl = 0;
			UINT i;
			GoDown(Y-1);
			OnKeyDown(VK_HOME, 0, 0);
			if (find_mode == FARSI) { 
				for (i = (searchpoint - m_Curs.x); i < X + length; i++)
					OnKeyDown(VK_LEFT, 0, 0);
				EndSelPoint.x = m_Curs.x;
				EndSelPoint.y = m_Curs.y;
				BeginSelPoint.x = m_Curs.x + length;
				BeginSelPoint.y = m_Curs.y;
				
			}
			if (find_mode == ENGLISH) {
				for (i = 0; i < (X - 1) + length; i++)
					OnKeyDown(VK_RIGHT, 0, 0);
				EndSelPoint = m_Curs;				
				BeginSelPoint.x = m_Curs.x - length;
				BeginSelPoint.y = m_Curs.y;
			
			}
		InvalidateBlock(BeginSelPoint, EndSelPoint);
		search_is_done = true;
	} 
	else if (!replaceAll)
		AfxMessageBox("Cannot find String", MB_ICONEXCLAMATION);
	
	return find;
}


void CFtexedView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	ReleaseCapture();
}

void CFtexedView::OnRunRun() 
{
	// TODO: Add your command handler code here
	
	CString sFileName = pDoc->GetPathName();
	
	if (sFileName.IsEmpty()) {
		AfxMessageBox("Please save the file first");
	
		return;
	}
	
	if (!DoSaveUpdate(sFileName))
		return;

	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");
	
	int backslash_index = sFileName.ReverseFind('\\');
	CString sFirstParam = sFileName.Left(backslash_index);
	sFirstParam = "\"" + sFirstParam + "\"";
	CString sSecParam = (LPCSTR)sFileName + backslash_index + 1;
	sSecParam = "\"" + sSecParam + "\"";
	CString sThirdParam = sFileName.Left(sFileName.Find('\\'));
	
	CString sGoftex = "goftex.bat";
	
	if (_spawnlp( _P_NOWAIT, sGoftex, sGoftex,  sFirstParam, sSecParam, sThirdParam,  NULL ) < 0)
		MessageBox("An error occurred while FarsiTeX Editor was trying to launch FarsiTeX typesetting engine.");
}

void CFtexedView::OnRunCnvrt() 
{
	// TODO: Add your command handler code here
	CString sFileName = pDoc->GetPathName();

	if (sFileName.IsEmpty()) {
		AfxMessageBox("Please save the file first");
		
		return;
	}
	if(!DoSaveUpdate(sFileName))
		return;

	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");

	int backslash_index = sFileName.ReverseFind('\\');
	CString sFirstParam = sFileName.Left(backslash_index);
	sFirstParam = "\"" + sFirstParam + "\"";
	CString sSecParam = (LPCSTR)sFileName + backslash_index + 1;
	sSecParam = "\"" + sSecParam + "\"";
	CString sThirdParam = sFileName.Left(sFileName.Find('\\'));

	CString sCnvrt = "convert.bat";
	
	if (_spawnlp( _P_NOWAIT, sCnvrt, sCnvrt, sFirstParam, sSecParam, sThirdParam,  NULL ) < 0)
		MessageBox("An error occurred while FarsiTeX Editor was trying to launch FarsiTeX-to-TeX Converter.");
}


void CFtexedView::OnRunPs() 
{
	// TODO: Add your command handler code here
	CString sFileName = pDoc->GetPathName();

	if (sFileName.IsEmpty()) {
		AfxMessageBox("Please save the file first");
		
		return;
	}
	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");
	sFileName = "\"" + sFileName + "\"";

	int backslash_index = sFileName.ReverseFind('\\');
	CString sWorkingDir = sFileName.Left(backslash_index);
	::SetCurrentDirectory(sWorkingDir); /* DVIPS needs this because current directory is
										   the base directory address for .eps figures
	                                    */
	CString sDvips = "dvips.exe";

	if (_spawnlp( _P_NOWAIT, sDvips, sDvips, sFileName,  NULL ) < 0)
		MessageBox("An error occurred while FarsiTeX Editor was trying to launch DVIPS.EXE.");
}

void CFtexedView::OnRunView() 
{
	// TODO: Add your command handler code here
	CString sFileName = pDoc->GetPathName();

	if (sFileName.IsEmpty()) {
		AfxMessageBox("Please save the file first");
		
		return;
	}
	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");
	sFileName = "\"" + sFileName + "\"";

	int backslash_index = sFileName.ReverseFind('\\');
	CString sWorkingDir = sFileName.Left(backslash_index);
	::SetCurrentDirectory(sWorkingDir); /* This is needed for placing view log files in the right place. */

	CString sView = "yap.exe";

	if (_spawnlp( _P_NOWAIT, sView, sView,  sFileName,"-1", NULL ) < 0)
		MessageBox("An error occurred while FarsiTeX Editor was trying to launch YAP DVI Viewer application.");

}

void CFtexedView::OnRunGs() 
{
	// TODO: Add your command handler code here
	CString sFileName = pDoc->GetPathName();

	if (sFileName.IsEmpty()) {
		AfxMessageBox("Please save the file first");
		return;
	}
	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");
	sFileName += ".ps";
	sFileName = "\"" + sFileName + "\"";

	if (_spawnl( _P_NOWAIT, m_szpsPath, sFileName, sFileName, NULL ) < 0)
		MessageBox("An error occurred while FarsiTeX Editor was trying to launch GSView application.");
}

void CFtexedView::OnRunMkind() 
{
	// TODO: Add your command handler code here
	CString sFileName = pDoc->GetPathName();

	if (sFileName.IsEmpty()) {
		AfxMessageBox("You should first save and compile your document.");
		return;
	}

	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");

	int backslash_index = sFileName.ReverseFind('\\');
	CString sFirstParam = sFileName.Left(backslash_index);
	sFirstParam = "\"" + sFirstParam + "\"";
	CString sSecParam = (LPCSTR)sFileName + backslash_index + 1;
	sSecParam = "\"" + sSecParam + "\"";
	CString sThirdParam = sFileName.Left(sFileName.Find('\\'));

	CString sMakeInd = "fmakeindex.bat";
	
	if (_spawnlp( _P_NOWAIT, sMakeInd, sMakeInd, sFirstParam, sSecParam, sThirdParam,  NULL ) < 0)
		MessageBox("An error occurred while FarsiTeX Editor was trying to launch MakeIndex.");
}

void CFtexedView::OnRunFtxtouni() 
{
	// TODO: Add your command handler code here
	CString sFileName = pDoc->GetPathName();

	if (sFileName.IsEmpty()) {
		AfxMessageBox("Please save the file first");
		
		return;
	}
	if(!DoSaveUpdate(sFileName))
		return;

	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");

	int backslash_index = sFileName.ReverseFind('\\');
	CString sFirstParam = sFileName.Left(backslash_index);
	sFirstParam = "\"" + sFirstParam + "\"";
	CString sSecParam = (LPCSTR)sFileName + backslash_index + 1;
	sSecParam = "\"" + sSecParam + "\"";
	CString sThirdParam = sFileName.Left(sFileName.Find('\\'));

	CString sCnvrt = "ftx2unicode.bat";
	
	if (_spawnlp( _P_NOWAIT, sCnvrt, sCnvrt, sFirstParam, sSecParam, sThirdParam,  NULL ) < 0)
		MessageBox("An error occurred while FarsiTeX Editor was trying to launch FarsiTeX-to-Unicode Converter.");
	
}

void CFtexedView::OnGhostView()
{
	OnRunGs();
}

void CFtexedView::OnRunFTeX() 
{
	OnRunRun();
}

void CFtexedView::OnDvi() 
{
	OnRunView();
}

void CFtexedView::OnDvips() 
{
	OnRunPs();
}

void CFtexedView::OnUpdateEDITSearchAgain(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!SearchStr.IsEmpty());
}

void CFtexedView::PerformScrolling(CPoint pt)
{
	CSplitterWnd *splitter = (CSplitterWnd *)GetParent();
	CFtexedView *view;
	CPoint ptback = pt;
	int i, j;

	if (pt.x == -1)
		pt.x = topleft.x;
	if (pt.y == -1)
		pt.y = topleft.y;

	ScrollToPosition(pt);
	topleft = pt;
	AdjustScrollers();
	UpdateCaretPos();

	// Perform the scrolling for the other view with the same scroller if it exists
	if (splitter->GetActivePane(&i, &j) != this)
		Invalidate();
	else {
		if (ptback.x == -1) {
			j++;
			j %= 2;
		}

		if (ptback.y == -1) {
			i++;
			i %= 2;
		}

		if ((splitter->GetRowCount() < i + 1) || (splitter->GetColumnCount() < j + 1))
			return;

		view = (CFtexedView *)splitter->GetPane(i, j);
		view->PerformScrolling(ptback);
	}
}

void CFtexedView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

    CMenu menu;
	CMenu *submenu;
    // load the menu
    menu.LoadMenu(IDR_NONAMETYPE);
    // get the popup menu
    submenu = menu.GetSubMenu(1);
    // convert to screen coordinates
    ClientToScreen(&point);
    // post the menu
    submenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                            point.x, point.y,
                            AfxGetApp()->m_pMainWnd, NULL);
}

/* Mehrdad: Printing is now done through YAP. There is no need for the following method.
PrintDlg dialog box still exists in the project; however, it won't be of
any use, anymore. */
/*
void CFtexedView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	CPrintDLG DlgPrint;
	if ( DlgPrint.DoModal() != IDOK)
		return;

	//UINT DlgPrint.m_ToPage;
	//UINT	DlgPrint.m_FromPage;
	//CString	DlgPrint.m_EditToFile;

	CString sFileName = pDoc->GetPathName();

	if (sFileName.IsEmpty()) {
		AfxMessageBox("Please save the file first");
		return;
	}
	sFileName.MakeUpper();
	sFileName.Replace(".FTX", "");
	
	CString sSecParam = (LPCSTR)sFileName + sFileName.ReverseFind('\\') + 1;
	
	

	int len = 0;
	CString sPrtHPLJ, sPrtHPLJH, sPrtLQL, sPrtLQM, sPrtLQH;

	switch (DlgPrint.PrinterType) {
		case 0:
				sPrtHPLJ = m_szftxPath;
				len = strlen(sPrtHPLJ);

				sPrtHPLJ.Delete(len - 15, 15);
				sPrtHPLJ += "prthplj.bat";
		
				if (_spawnl( _P_NOWAIT, sPrtHPLJ, sPrtHPLJ,  sFileName, NULL ) < 0)
					MessageBox("Error");
			break;
		case 1:
				sPrtHPLJH = m_szftxPath;
				len = strlen(sPrtHPLJH);

				sPrtHPLJH.Delete(len - 15, 15);
				sPrtHPLJH += "prthpljh.bat";
		
				if (_spawnl( _P_NOWAIT, sPrtHPLJH, sPrtHPLJH,  sFileName, sSecParam,  NULL ) < 0)
					MessageBox("Error");
			break;
		case 2:
				sPrtLQL = m_szftxPath;
				len = strlen(sPrtLQL);

				sPrtLQL.Delete(len - 15, 15);
				sPrtLQL += "prtlql.bat";
		
				if (_spawnl( _P_NOWAIT, sPrtLQL, sPrtLQL,  sFileName, sSecParam,  NULL ) < 0)
					MessageBox("Error");
			break;
		case 3:
				sPrtLQM = m_szftxPath;
				len = strlen(sPrtLQM);

				sPrtLQM.Delete(len - 15, 15);
				sPrtLQM += "prtlqm.bat";
		
				if (_spawnl( _P_NOWAIT, sPrtLQM, sPrtLQM,  sFileName, sSecParam,  NULL ) < 0)
					MessageBox("Error");
			break;
		case 4:
				sPrtLQH = m_szftxPath;
				len = strlen(sPrtLQH);

				sPrtLQH.Delete(len - 15, 15);
				sPrtLQH += "prtlqh.bat";
		
				if (_spawnl( _P_NOWAIT, sPrtLQH, sPrtLQH,  sFileName, sSecParam,  NULL ) < 0)
					MessageBox("Error");
			break;
	}

}
*/

void CFtexedView::OnSyntaxoff() 
{
	// TODO: Add your command handler code here
	if (m_bHighlight == TRUE) {
		m_bHighlight = FALSE;
		
		Invalidate();
		return;
	}

	m_bHighlight = TRUE;
	Invalidate();
	return;
}

void CFtexedView::RemapCharacters(const BYTE *pFrom, BYTE *pTo)
{
	for (int i = 0; i < MAX_TLEN / 2 + 1; i++)
	{
		pTo[i] = GetFontChar(pFrom[i]);
	}
}

inline BYTE CFtexedView::GetFontChar(BYTE ch)
{
	switch(ch) {
	case 1:  //fathe
		ch = 176;
		break;
	
	case 2:  //kasre
		ch = 177;
		break;
	
	case 3:  //zamme
		ch = 178;
		break;
	
	case 4:  //nasb
		ch = 179;
		break;
	
	case 5:  //tashdid
		ch = 180;
		break;
	
	case 6:  //alef
		ch = 186;
		break;
	
	case 7:  //hamze
		ch = 187;
		break;
	
	case 14:  //
		ch = 192;
		break;
	
	case 19:  //taa
		ch = 193;
		break;
	
	case 20:  //zaa
		ch = 194;
		break;
	
	case 21:  //
		ch = 195;
		break;
	
	case 22:  //saken
		ch = 196;
		break;
	
	case 11:  //
		ch = 188;
		break;
	
	case 12:  //te
		ch = 191;
		break;
	
	case 23:  //zarb
		ch = 200;
		break;
	
	case 25:  //mad
		ch = 201;
		break;
	
	case 27:  //jame'
		ch = 205;
		break;
	}
	
	return ch;
}

BOOL CFtexedView::DoSaveUpdate(CString sFileName)
{
	if (!GetDocument()->IsModified())
		return TRUE;

	DWORD dwAttrib = GetFileAttributes(sFileName);
	
	if (dwAttrib & FILE_ATTRIBUTE_READONLY)
	{
		// we do not have read-write access.
		AfxMessageBox("Write access denied. Either the file is read-only,\
you do not have the required privilages to edit this file, or the file has been moved or removed.\
If you have moved or removed the file manually, save it now.");
		return FALSE;
	}

	if (save_backups)
		GetDocument()->SaveBackup();

	GetDocument()->OnSaveDocument(sFileName);

	GetDocument()->SetModifiedFlag(FALSE);
	CString strDocName = GetDocument()->GetTitle();
	strDocName.Replace(" *", "");
	GetDocument()->SetTitle(strDocName);
	
	return TRUE;
}

void CFtexedView::OnSetFocus(CWnd* pOldWnd) 
{
	CScrollView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	shift = 0;
	ctrl = 0;
	Invalidate();
	UpdateCaretPos();
	ShowCaret();
}

void CFtexedView::OnKillFocus(CWnd* pNewWnd) 
{
	CScrollView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	HideCaret();
}

void CFtexedView::OnUpdateSyntaxoff(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bHighlight == TRUE)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
	
}

void CFtexedView::OnViewDefMode() 
{
	// TODO: Add your command handler code here
	if (defaultMode == FARSI_IS_DEFAULT)
		defaultMode = SAME_AS_CURRENT_LINE_IS_DEFAULT;
	else
		defaultMode = FARSI_IS_DEFAULT;
}

void CFtexedView::OnUpdateViewDefMode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (defaultMode == FARSI_IS_DEFAULT)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}

void CFtexedView::OnEditReplace() 
{
	// TODO: Add your command handler code here
   CReplace m_Replace;

   if (!SearchStr.IsEmpty())
		m_Replace.strFind = SearchStr;
   if (!ReplaceStr.IsEmpty())
	   m_Replace.strReplace = ReplaceStr;

   m_Replace.SetView(this);

   if(m_Replace.DoModal() != IDOK)
	   return;
}

int CFtexedView::SkipEraab(int fromPosition)
{
	int i = fromPosition + 1;
	int j = 0;
	while ((CURLINE->data[i] > 0 && CURLINE->data[i] < 8) || CURLINE->data[i] == 22) //eraab
	{
		i++;
		j++;
	}
	
	return j;
}

BOOL CFtexedView::IsLogicalEraab(BYTE c)
{
	switch (c)
	{
	case 176:  //fathe
	case 177:  //kasre
	case 178:  //zamme
	case 179:  //nasb
	case 180:  //tashdid
	case 186:  //alef
	case 187:  //hamze
	case 196:  //saken
		return TRUE;
	default:
		return FALSE;
	}
}

BOOL CFtexedView::IsLogicalSeparator(BYTE c)
{
	switch (c) {
	case 0:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 58:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 91:
	case 92:
	case 93:
	case 94:
	case 95:
	case 96:
	case 123:
	case 124:
	case 125:
	case 126:
	case 138:
	case 139:
	case 140:
	case 181:
	case 182:
	case 183:
	case 184:
	case 189:
	case 190:
	case 192:
	case 195:
	case 196:
	case 197:
	case 198:
	case 199:
	case 200:
	case 201:
	case 202:
	case 203:
	case 204:
	case 205:
	case 206:
	case 207:
	case 208:
	case 209:
	case 210:
	case 211:
	case 212:
	case 213:
	case 214:
	case 215:
	case 216:
	case 221:
	case 222:
	case 255:
		return TRUE;
		
	default:
		return FALSE;
	}
	
	return FALSE;
}

BOOL CFtexedView::IsNumber(BYTE c)
{
	if ((c >= 128) && (c <= 137)) //Farsi
		return TRUE;

	if ((c >= 48) && (c <= 57)) //English
		return TRUE;

	return FALSE;
}

BOOL CFtexedView::IsLogicalCommandSeparator(BYTE c)
{
	return (IsLogicalSeparator(c) || IsNumber(c) || IsLogicalEraab(c));
}

BOOL CFtexedView::IsRunningOnNT()
{
    if(::GetVersion() & 0x80000000)
		return FALSE;
	return TRUE;
}

BOOL CFtexedView::OnEraseBkgnd(CDC* pDC) 
{
	// Set brush to desired background color
    CBrush backBrush(background);

    // Save the old brush
    CBrush* pOldBrush = pDC->SelectObject(&backBrush);

    // Get the current clipping boundary
    CRect rect;
    pDC->GetClipBox(&rect);

    // Erase the area needed
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(),
         PATCOPY);

    pDC->SelectObject(pOldBrush); // Select the old brush back
    return TRUE;  // message handled

}

void CFtexedView::Replace()
{
	if (search_is_done && BeginSelPoint.x != -1 && !endReplace)
	{
		char* temp = ((CFtexedApp *)AfxGetApp())->ClipBoard;
		int tempCBLen = ((CFtexedApp *)AfxGetApp())->CBLen;

		char str[200];
		strcpy(str, ReplaceStr);
		
		((CFtexedApp *)AfxGetApp())->ClipBoard = str;
		((CFtexedApp *)AfxGetApp())->CBLen = strlen(str);

		RemoveSelectedArea();
		OnEditOnlyPaste();

		((CFtexedApp *)AfxGetApp())->ClipBoard = temp;
		((CFtexedApp *)AfxGetApp())->CBLen = tempCBLen;

		search_is_done = false;
		if (!Search())
			endReplace = true;
	}
	else
	{
		search_is_done = false;
		Search();
	}
}

void CFtexedView::RemoveSelectedArea()
{
	// TODO: Add your command handler code here

	CFtexedDoc::LINETYPE *FirstLine, *temp, *save_first;
	CFtexedView *(Views[2]);

	int nextXCursorPos = BeginSelPoint.x;
	int nextYCursorPos = BeginSelPoint.y;

	FindLine(BeginSelPoint.y, &FirstLine);
	save_first = FirstLine;

	if (BeginSelPoint.y == EndSelPoint.y) {
		int i,j;

		if (ISL2R(FirstLine)) {
			for (i = EndSelPoint.x - m_cmargin, j = BeginSelPoint.x - m_cmargin; i < FirstLine->len; i++, j++)
				FirstLine->data[j] = FirstLine->data[i];
			for (i = j; i < FirstLine->len; i++)
				FirstLine->data[i] = 255;
			FirstLine->len -= (WORD)(EndSelPoint.x - BeginSelPoint.x);
		}
		else {
			for (i = EndSelPoint.x, j = BeginSelPoint.x; i >= MAX_TLEN / 2 - FirstLine->len; i--, j--)
				FirstLine->data[j] = FirstLine->data[i];
			for (i = j; i >= MAX_TLEN / 2 - FirstLine->len; i--)
				FirstLine->data[i] = 255;
			FirstLine->len -= (WORD)(BeginSelPoint.x -EndSelPoint.x);
		}
	}
	else {
		if (ISL2R(FirstLine)) {
			for (int i = BeginSelPoint.x; i < m_cmargin + FirstLine->len; i++)
				FirstLine->data[i - m_cmargin] = 255;
			FirstLine->len = BeginSelPoint.x - m_cmargin;
		}
		else {
			for (int i = MAX_TLEN / 2 - FirstLine->len; i <= BeginSelPoint.x; i++)
				FirstLine->data[i] = 255;
			FirstLine->len = MAX_TLEN / 2 - BeginSelPoint.x - 1;
		}
		
		FirstLine = FirstLine->next;

		for (int i = BeginSelPoint.y + 1; i < EndSelPoint.y; i ++) {
			FirstLine->last->next = FirstLine->next;
			FirstLine->next->last = FirstLine->last;
			temp = FirstLine;
			pDoc->numLines--;
			FirstLine = FirstLine->next;
			delete temp;
		}

		if (ISL2R(save_first)) {
			int i, j;

			if (ISL2R(FirstLine)) {
				for (i = EndSelPoint.x - m_cmargin, j = save_first->len; i < FirstLine->len; i++, j++)
					save_first->data[j] = FirstLine->data[i];
			}
			else {
				for (i = MAX_TLEN / 2 - FirstLine->len, j = save_first->len; i <= EndSelPoint.x ; i++, j++)
					save_first->data[j] = FirstLine->data[i];
			}
			save_first->len = j;
			if (save_first->len == 1) {
				save_first->len = 0;
				save_first->data[0] = 255;
			}
		}
		else {
			int i, j;

			if (ISL2R(FirstLine)) {
				for (i = FirstLine->len - 1, j = MAX_TLEN / 2 - 1 - save_first->len; i >= EndSelPoint.x - m_cmargin; i--, j--)
					save_first->data[j] = FirstLine->data[i];
			}
			else {
				for (i = EndSelPoint.x, j = MAX_TLEN / 2 - 1 - save_first->len; i > MAX_TLEN / 2 - 1 - FirstLine->len; i--, j--)
					save_first->data[j] = FirstLine->data[i];
			}
			save_first->len = MAX_TLEN / 2 - 1 - j;
		}

		FirstLine->last->next = FirstLine->next;
		if (FirstLine->next != NULL)
			FirstLine->next->last = FirstLine->last;
		pDoc->numLines--;
		delete FirstLine;

		if ((save_first->len == 0) && (save_first->next != NULL)) {
			if (save_first == pDoc->m_head)
				pDoc->m_head = save_first->next;
			else
				save_first->last->next = save_first->next;
			save_first->next->last = save_first->last;
			pDoc->numLines --;
			delete save_first;
		}
	}

	FindAllViews(Views);
	for (int k = 0; k < 2; k++)
		if (Views[k] != NULL)
		{
			Views[k]->AdjustScrollers();
			Views[k]->Invalidate(); /*Mehrdad: InvalidateBlock(BeginSelPoint, (-1,-1))
			was commented out, see the comments at the end of this method.*/
		}
		else
			break;

	if (!(pDoc->IsModified())) {
		pDoc->SetModifiedFlag(TRUE);
		pDoc->SetTitle(pDoc->GetTitle() + " *");
	}

	m_Curs.x = nextXCursorPos;
	m_Curs.y = nextYCursorPos;

	FindLine(m_Curs.y, &CURLINE);

	/* Mehrdad: Technically, this check is of no use anymore. But this is a good check afterall! */
	if (m_Curs.y > pDoc->numLines)
		m_Curs.y = pDoc->numLines; 

	SetProperWindow(0);
	ValidateCursorPos();
	UpdateCaretPos();

	BeginSelPoint.x = -1;

	/*Mehrdad: This may not work when we have two splitter panes whose
	sizes are diffrent. You may scroll down several pages when selecting
	text in the smaller pane, while the larger pane may not scroll at all.
	Since the maximum size of invalidated area in the larger pane cannot
	be larger than the size of the smaller window, this leaves traces in
	the larger window after selection is removed.
	*/
	//InvalidateBlock(BeginSelPoint, (-1,-1)); 
}

void CFtexedView::ReplaceAll()
{
	char* temp = ((CFtexedApp *)AfxGetApp())->ClipBoard;
	int tempCBLen = ((CFtexedApp *)AfxGetApp())->CBLen;


	char str[200];
	sprintf(str, "%s", ReplaceStr);
	
	((CFtexedApp *)AfxGetApp())->ClipBoard = str;
	((CFtexedApp *)AfxGetApp())->CBLen = strlen(str);
	
	while(Search())
	{
		RemoveSelectedArea();
		OnEditOnlyPaste();
	}

	((CFtexedApp *)AfxGetApp())->ClipBoard = temp;
	((CFtexedApp *)AfxGetApp())->CBLen = tempCBLen;
}

void CFtexedView::OnViewOptionsCaretcase() 
{
	// TODO: Add your command handler code here
	if (m_bCaretChangeCase)
		m_bCaretChangeCase = false;
	else
		m_bCaretChangeCase = true;
}

void CFtexedView::OnUpdateViewOptionsCaretcase(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bCaretChangeCase)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);

}

void CFtexedView::OnDefCaretNext()
{
	// TODO: Add your command handler code here
	if (m_bDefCaretNext)
		m_bDefCaretNext = false;
	else
		m_bDefCaretNext = true;

}

void CFtexedView::OnUpdateDefCaretNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_bDefCaretNext)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);

}

void CFtexedView::OnViewRefresh() 
{
	// TODO: Add your command handler code here
	Invalidate();
}

BOOL CFtexedView::ReadClipboard(CString *pString)
{
	HGLOBAL hglb;
	LPCSTR  lpcstr;

	if (!IsClipboardFormatAvailable(CF_TEXT))
	{
		AfxMessageBox("Clipboard data has got no ASCII text presentation.");
		return FALSE; 
	}

	if (!OpenClipboard())
	{
		AfxMessageBox("FarsiTeX Editor failed to open the clipboard.");
		return FALSE; 
	}

	hglb = GetClipboardData(CF_TEXT);

	if (hglb != NULL)
	{
		lpcstr = (LPCSTR)GlobalLock(hglb);
		if (lpcstr != NULL)
			GlobalUnlock(hglb);
	}
	
	CloseClipboard();
	*pString = lpcstr;
    return TRUE;
}

void CFtexedView::OnEditImport() 
{
	// TODO: Add your command handler code here
	char *buff;
	UINT bufLen = 0;
	CString strClipboard;
	
	if(!ReadClipboard(&strClipboard))
		return ;
	
	BeginWaitCursor();
	CTokenizer tokenizer(strClipboard, clipboard_wrap_size);
	CString preparedClipboard = tokenizer.GetPreparedLines();
	EndWaitCursor();

	bufLen = preparedClipboard.GetLength() + 1;
	buff = new char[bufLen];

	// Set proper clipboard length
	((CFtexedApp *)AfxGetApp())->CBLen = bufLen - 1;

	strcpy(buff, preparedClipboard);

	for (UINT i = 0; i < bufLen - 1; i++)
	{
		if (buff[i] == '\n')
			buff[i] = '\0';
	}

	// Release previously allocated memory for clipboard
	if ((CFtexedApp *)AfxGetApp() != NULL)
		delete []((CFtexedApp *)AfxGetApp())->ClipBoard;

	// New contents of clipboard
	((CFtexedApp *)AfxGetApp())->ClipBoard = buff;
}