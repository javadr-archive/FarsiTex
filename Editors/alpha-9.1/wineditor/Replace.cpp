// Replace.cpp : implementation file
//

#include "stdafx.h"
#include "Ftexed.h"
#include "Replace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplace dialog


CReplace::CReplace(CWnd* pParent /*=NULL*/)
	: CDialog(CReplace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplace)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
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
	font -> CreateFontIndirect(&logFont);

}


void CReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplace)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplace, CDialog)
	//{{AFX_MSG_MAP(CReplace)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_BN_CLICKED(IDC_REPLACE, OnReplace)
	ON_BN_CLICKED(IDC_REPLACE_ALL, OnReplaceAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplace message handlers

int CReplace::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_Edit.Create(WS_VISIBLE |WS_CHILD |WS_BORDER |
		WS_TABSTOP  |WS_HSCROLL  |
		/*ES_AUTOHSCROLL |*/ ES_MULTILINE |ES_RIGHT ,
		CRect(85, 120, MAX_REPLACE_SIZE, 145), this, ID_EDITBOX);
	m_Edit.SetFont(font, true);

	m_Replace.Create(WS_VISIBLE |WS_CHILD |WS_BORDER |
		WS_TABSTOP  |WS_HSCROLL  |
		 ES_MULTILINE |ES_RIGHT ,
		CRect(85, 150, MAX_REPLACE_SIZE, 175), this, ID_EDITBOX);
	m_Replace.SetFont(font, true);


	
	if (!strFind.IsEmpty()) {
		m_Edit.str = strFind;
		m_Edit.SetWindowText(strFind);//Set pervios Text
		m_Edit.SetSel(0, 255);//Select prervios Text
	}

	if (!strReplace.IsEmpty()) {
		m_Replace.str = strReplace;
		m_Replace.SetWindowText(strReplace);//Set pervios Text
		m_Replace.SetSel(0, 255);//Select prervios Text
	}

	return 0;
}


inline BYTE CReplace::GetFontChar(BYTE ch)
{
	switch(ch) {
	case 176:  //fathe
		ch = 1;
		break;
	
	case 177:  //kasre
		ch = 2;
		break;
	
	case 178:  //zamme
		ch = 3;
		break;
	
	case 179:  //nasb
		ch = 4;
		break;
	
	case 180:  //tashdid
		ch = 5;
		break;
	
	case 186:  //alef
		ch = 6;
		break;
	
	case 187:  //hamze
		ch = 7;
		break;
	
	case 192:  //
		ch = 14;
		break;
	
	case 193:  //taa
		ch = 19;
		break;
	
	case 194:  //zaa
		ch = 20;
		break;
	
	case 195:  //
		ch = 21;
		break;
	
	case 196:  //saken
		ch = 22;
		break;
	
	case 188:  //
		ch = 11;
		break;
	
	case 191:  //te
		ch = 12;
		break;
	
	case 200:  //zarb
		ch = 23;
		break;
	
	case 201:  //mad
		ch = 25;
		break;
	
	case 205:  //jame'
		ch = 27;
		break;
	}
	return ch;
}

CString CReplace::UnMap(CString s)
{
	CString ret;
	for (int i = 0; i < s.GetLength(); i++)
	{
		ret += GetFontChar(s[i]);
	}
	return ret;
}


void CReplace::OnFindNext() 
{
	// TODO: Add your control notification handler code here
	m_Edit.GetWindowText(strFind);
	if (strFind.IsEmpty())
		return;
	strFind = UnMap(strFind);

	pFtexView->SearchStr = strFind;
	pFtexView->search_is_done = false;
	pFtexView->Search();
	
}

void CReplace::OnReplace() 
{
	// TODO: Add your control notification handler code here
	m_Edit.GetWindowText(strFind);
	if (strFind.IsEmpty())
		return;
	strFind = UnMap(strFind);

	m_Replace.GetWindowText(strReplace);
	/*
	if (strReplace.IsEmpty())
		return;
	*/
	strReplace = UnMap(strReplace);

	pFtexView->SearchStr = strFind;
	pFtexView->ReplaceStr = strReplace;
	pFtexView->Replace();
	
}


void CReplace::SetView(CFtexedView* pView)
{
	pFtexView = pView;
	pFtexView->endReplace = false;
	pFtexView->search_is_done = false;
}




void CReplace::OnReplaceAll() 
{
	// TODO: Add your control notification handler code here
		
	m_Edit.GetWindowText(strFind);
	if (strFind.IsEmpty())
		return;
	strFind = UnMap(strFind);

	m_Replace.GetWindowText(strReplace);
	if (strReplace.IsEmpty())
		return;
	strReplace = UnMap(strReplace);

	pFtexView->replaceAll = true;
	pFtexView->SearchStr = strFind;
	pFtexView->ReplaceStr = strReplace;
	pFtexView->ReplaceAll();
	pFtexView->replaceAll = false;
	
}
