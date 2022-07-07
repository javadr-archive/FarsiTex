// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Ftexed.h"

#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_TEXT5, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_LnCol, OnUpdateLnCol)
	ON_UPDATE_COMMAND_UI(ID_ENGLISH, OnUpdateEnglish)
	ON_UPDATE_COMMAND_UI(ID_FARSI, OnUpdateFarsi)
	ON_COMMAND(IDD_READ_HELP, OnReadHelp)
	ON_COMMAND(IDD_VISIT_HOMEPAGE, OnVisitHomepage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern CFtexedApp theApp;

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_LnCol,
	ID_TEXT5,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

void CMainFrame::OnUpdateMode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->SetText("");
}

void CMainFrame::OnUpdateLnCol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetText("");
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateEnglish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(0);
	pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateFarsi(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(0);
	pCmdUI->Enable(FALSE);
}

void CMainFrame::OnReadHelp() 
{
	// TODO: Add your command handler code here
	int iRes;
	CString helpFile = theApp.m_pszHelpFilePath;
	helpFile = helpFile.Left(helpFile.ReverseFind('\\') + 1);
	helpFile += "ftexed_man.html";
	iRes = (int) ShellExecute(this->m_hWnd, "open", helpFile, NULL, NULL, SW_SHOWNORMAL);
	if (iRes <= 32)
	{
		// If unable to browse then put up an error box.
		AfxMessageBox("FarsiTeX Editor was unable to browse the manual.");
	}
}

void CMainFrame::OnVisitHomepage() 
{
	// TODO: Add your command handler code here
	int iRes;
	iRes = (int) ShellExecute(this->m_hWnd, "open", "http://www.farsitex.org", NULL, NULL, SW_SHOWNORMAL);
	if (iRes <= 32)
	{
		// If unable to browse then put up an error box.
		AfxMessageBox("FarsiTeX Editor was unable to browse FarsiTeX Homepage.");
	}
	
}
