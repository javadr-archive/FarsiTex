// Ftexed.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Ftexed.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "FtexedDoc.h"
#include "FtexedView.h"
#include "Splash.h"
#include "AboutTeam.h"

// This array maps each of 256 possible ASCII characters to the corresponding 
// farsi character. It is read from the file "FTEXKEYB.DAT" in the constructor of 
// CFtexedApp.
UCHAR map[256];

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFtexedApp

BEGIN_MESSAGE_MAP(CFtexedApp, CWinApp)
	//{{AFX_MSG_MAP(CFtexedApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtexedApp construction

CFtexedApp::CFtexedApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	CBLen = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFtexedApp object

CFtexedApp theApp;

//colors
COLORREF background = GetSysColor(COLOR_WINDOW);
COLORREF normal_farsi_text = RGB(0, 0, 0);
COLORREF english_background = RGB(180, 190, 250);
COLORREF normal_english_text = RGB(0, 0, 0);
COLORREF selected_text = RGB(255, 255, 255);
COLORREF selection_background = RGB(50, 50, 200);
COLORREF commented_text = RGB(150, 150, 150);
COLORREF command_text = RGB(255, 50, 50);
COLORREF eraab_text = RGB(200, 200, 200);
COLORREF english_line_marker = RGB(100, 255, 100);

//options
BOOL syntax_highlighting = TRUE;
BOOL save_backups = TRUE;
UINT clipboard_wrap_size = 80;
BOOL pair_brackets_and_braces = FALSE;
BOOL dash_is_number_separator = TRUE;

/////////////////////////////////////////////////////////////////////////////
// CFtexedApp initialization

BOOL CFtexedApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_NONAMETYPE,
		RUNTIME_CLASS(CFtexedDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CFtexedView));
	AddDocTemplate(pDocTemplate);

	FILE *pFile;
	CString pathName = m_pszHelpFilePath;
	pathName = pathName.Left(pathName.ReverseFind('\\') + 1);

	CString keyboardSettingsFile = pathName + "ftexkeyb.dat";
	CString colorsFile = pathName + "colors.ftc";
	CString colorSettingFile = pathName + "colorsettings.ftc";
	CString optionsFile = pathName + "options.ftc";

	if ((pFile = fopen(keyboardSettingsFile, "rb")) == 0)
	{
		AfxMessageBox("Can't find ftexkeyb.dat!");
		exit(1);
	}
	fread(map, 1, 256, pFile);
	fclose(pFile);

	SetColors(colorSettingFile, colorsFile);
	SetOptions(optionsFile);


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnViewteam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_VIEWTEAM, OnViewteam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFtexedApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFtexedApp commands

BOOL CFtexedApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}


CMapStringToPtr* CFtexedApp::ReadColors(CString fileName)
{
	FILE *stream;
	
	stream = fopen(fileName, "rt");

	if( stream == NULL )
	{
		AfxMessageBox("FarsiTeX Editor failed to read your custom colors. Default colors will be used.");
		return NULL;
	}
	
	CMapStringToPtr *colorMapper = new CMapStringToPtr;

	char oneLine[1025];
	CString strLine;
	
	COLORREF *rgbColor;
	
	CString strRed, strGreen, strBlue;
	CString strColorName;
	int red, green, blue;
	int index;
	int success;
	
	/* Set pointer to beginning of file: */
    fseek(stream, 0L, SEEK_SET);

	while (!feof(stream))
	{
		fgets(oneLine, 1024, stream);
	
		strLine = oneLine;
		strLine.TrimLeft();
		strLine.TrimRight();

		if (strLine.IsEmpty())
			continue;

		if (strLine.GetAt(0) == '#')
			continue;
		
		index = strLine.Find(':', 0);
		if (index == -1)
			continue;
		strColorName = strLine.Left(index);
		strColorName.TrimLeft();
		strColorName.TrimRight();
		strLine.Delete(0, index + 1);

		index = strLine.Find(',', 0);
		if (index == -1)
			continue;
		strRed = strLine.Left(index);
		strRed.TrimLeft();
		strRed.TrimRight();
		strLine.Delete(0, index + 1);

		index = strLine.Find(',', 0);
		if (index == -1)
			continue;
		strGreen = strLine.Left(index);
		strGreen.TrimLeft();
		strGreen.TrimRight();
		strLine.Delete(0, index + 1);

		strBlue = strLine;
		strBlue.TrimLeft();
		strBlue.TrimLeft();

		success = sscanf(strRed, "%d", &red);
		if (!success)
			continue;

		success = sscanf(strGreen, "%d", &green);
		if (!success)
			continue;

		success = sscanf(strBlue, "%d", &blue);
		if (!success)
			continue;

		rgbColor = new COLORREF;
		*rgbColor = RGB(red, green, blue);
		strColorName.MakeUpper();
		colorMapper->SetAt(strdup(strColorName), rgbColor);
    }

	fclose(stream);

	return colorMapper;
}


void CFtexedApp::SetColors(CString settingsFileName, CString colorsFileName)
{

	void *temp = NULL;

	char oneLine[1025];
	CString strLine;
	CString strSettingName;
	CString strColorName;

	int index;

	CMapStringToPtr *mapper = ReadColors(colorsFileName);
	
	if (mapper == NULL)
		return;

	FILE *stream;
	
	stream = fopen(settingsFileName, "rt");

	if( stream == NULL )
	{
		AfxMessageBox("FarsiTeX Editor failed to read your custom colors settings. Default colors will be used.");
		return;
	}
	
	/* Set pointer to beginning of file: */
    fseek(stream, 0L, SEEK_SET);

	while (!feof(stream))
	{
		fgets(oneLine, 1024, stream);

		strLine = oneLine;
		strLine.TrimLeft();
		strLine.TrimRight();

		if (strLine.IsEmpty())
			continue;

		if (strLine.GetAt(0) == '#')
			continue;

		index = strLine.Find(':', 0);
		if (index == -1)
			continue;

		strSettingName = strLine.Left(index);
		strSettingName.TrimLeft();
		strSettingName.TrimRight();
		strLine.Delete(0, index + 1);

		strColorName = strLine;
		strColorName.TrimLeft();
		strColorName.TrimRight();

		strColorName.MakeUpper();

		if (!strSettingName.CompareNoCase("background"))
			background = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : background;

		else if (!strSettingName.CompareNoCase("normal_farsi_text"))
			normal_farsi_text = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : normal_farsi_text;

		else if (!strSettingName.CompareNoCase("english_background"))
			english_background = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : english_background;

		else if (!strSettingName.CompareNoCase("normal_english_text"))
			normal_english_text = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : normal_english_text;

		else if (!strSettingName.CompareNoCase("selected_text"))
			selected_text = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : selected_text;

		else if (!strSettingName.CompareNoCase("selection_background"))
			selection_background = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : selection_background;

		else if (!strSettingName.CompareNoCase("commented_text"))
			commented_text = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : commented_text;

		else if (!strSettingName.CompareNoCase("command_text"))
			command_text = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : command_text;

		else if (!strSettingName.CompareNoCase("eraab_text"))
			eraab_text = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : eraab_text;

		else if (!strSettingName.CompareNoCase("english_line_marker"))
			english_line_marker = (mapper->Lookup(strColorName, temp) != 0) ? *((COLORREF*)temp) : english_line_marker;
	}
	
	fclose(stream);
	
	mapper->RemoveAll();
	delete mapper;

	/* This causes memeory leak, but it is negligable.
	   I really miss Java Garbage Collector when
	   I'm working with C++ containers.
	*/

}

void CFtexedApp::SetOptions(CString optionsFileName)
{
	char oneLine[1025];
	CString strLine;
	CString strOptionName;
	CString strValue;

	int index;

	FILE *stream;
	
	stream = fopen(optionsFileName, "rt");

	if( stream == NULL )
	{
		AfxMessageBox("FarsiTeX Editor failed to read your options file. Default option values will be used.");
		return;
	}
	
	/* Set pointer to beginning of file: */
    fseek(stream, 0L, SEEK_SET);

	while (!feof(stream))
	{
		fgets(oneLine, 1024, stream);

		strLine = oneLine;
		strLine.TrimLeft();
		strLine.TrimRight();

		if (strLine.IsEmpty())
			continue;

		if (strLine.GetAt(0) == '#')
			continue;

		index = strLine.Find(':', 0);
		if (index == -1)
			continue;

		strOptionName = strLine.Left(index);
		strOptionName.TrimLeft();
		strOptionName.TrimRight();
		strLine.Delete(0, index + 1);

		strValue = strLine;
		strValue.TrimLeft();
		strValue.TrimRight();

		strValue.MakeUpper();

		/* Many options are booleans, so this worths a try */
		BOOL value = (!strValue.Compare("YES") || !strValue.Compare("TRUE"));
		
		if (!strOptionName.CompareNoCase("syntax_highlighting"))
			syntax_highlighting = value;

		else if (!strOptionName.CompareNoCase("save_backups"))
			save_backups = value;

		else if (!strOptionName.CompareNoCase("clipboard_wrap_size"))
		{
			UINT temp;
			BOOL success = sscanf(strValue, "%d", &temp);
			clipboard_wrap_size = success ? temp : clipboard_wrap_size;
		}
		else if (!strOptionName.CompareNoCase("pair_brackets_and_braces"))
			pair_brackets_and_braces = value;

		else if (!strOptionName.CompareNoCase("dash_is_number_separator"))
			dash_is_number_separator = value;
	}
	
	fclose(stream);
}

void CAboutDlg::OnViewteam() 
{
	// TODO: Add your control notification handler code here
	CAboutTeam dlg;
	dlg.DoModal();
}
