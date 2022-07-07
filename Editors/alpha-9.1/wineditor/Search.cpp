// Search.cpp : implementation file
//

#include "stdafx.h"
#include "Ftexed.h"
#include "Search.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearch dialog


CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearch)
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


void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearch, CDialog)
	//{{AFX_MSG_MAP(CSearch)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearch message handlers

int CSearch::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	m_Edit.Create(WS_VISIBLE |WS_CHILD |WS_BORDER |
		WS_TABSTOP  |WS_HSCROLL  |
		/*ES_AUTOHSCROLL |*/ ES_MULTILINE |ES_RIGHT ,
		CRect(5, 100, MAX_SEARCH_SIZE, 125), this, ID_EDITBOX);
	m_Edit.SetFont(font, true);

	if (!str.IsEmpty()) {
		m_Edit.str = str;
		m_Edit.SetWindowText(str);//Set pervios Text
		m_Edit.SetSel(0, 255);//Select prervios Text
	}

	
	return 0;
}

void CSearch::OnOK() 
{
	// TODO: Add extra validation here
		
	CDialog::OnOK();
	m_Edit.GetWindowText(str);
	if (str.IsEmpty())
		return;
	str = UnMap(str);
	
}

inline BYTE CSearch::GetFontChar(BYTE ch)
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

CString CSearch::UnMap(CString s)
{
	CString ret;
	for (int i = 0; i < s.GetLength(); i++)
	{
		ret += GetFontChar(s[i]);
	}
	return ret;
}







