// AboutTeam.cpp : implementation file
//

#include "stdafx.h"
#include "ftexed.h"
#include "AboutTeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutTeam dialog


CAboutTeam::CAboutTeam(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutTeam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutTeam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutTeam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutTeam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutTeam, CDialog)
	//{{AFX_MSG_MAP(CAboutTeam)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutTeam message handlers
