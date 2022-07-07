// GotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ftexed.h"
#include "GotoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg dialog


CGotoDlg::CGotoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoDlg)
	m_nLineNum = 1;
	//}}AFX_DATA_INIT
}


void CGotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoDlg)
	DDX_Text(pDX, IDC_GOTO_Line, m_nLineNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoDlg, CDialog)
	//{{AFX_MSG_MAP(CGotoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg message handlers

void CGotoDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
	
	CDialog::OnCancel();
}
