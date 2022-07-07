; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutTeam
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ftexed.h"
LastPage=0

ClassCount=13
Class1=CChildFrame
Class2=CFarsiRichEdit
Class3=CFtexedApp
Class4=CAboutDlg
Class5=CFtexedDoc
Class6=CFtexedView
Class7=CGotoDlg
Class8=CMainFrame
Class9=CPrintDLG
Class10=CReplace
Class11=CSearch
Class12=CSplashWnd

ResourceCount=15
Resource1=IDR_NONAMETYPE
Resource2=IDD_REPLACE (English (U.S.))
Resource3=IDD_DIALOGPRINT
Resource4=IDD_REPLACE
Resource5=IDD_ABOUTBOX
Resource6=IDD_SEARCH
Resource7=IDR_MAINFRAME
Resource8=IDD_ABOUTBOX (English (U.S.))
Resource9=IDD_SEARCH (English (U.S.))
Resource10=IDR_NONAMETYPE (English (U.S.))
Resource11=IDR_MAINFRAME (English (U.S.))
Resource12=IDD_GOTO (English (U.S.))
Resource13=IDD_DIALOGPRINT (English (U.S.))
Resource14=IDD_GOTO
Class13=CAboutTeam
Resource15=IDD_ABOUTTEAM

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CFarsiRichEdit]
Type=0
BaseClass=CRichEditCtrl
HeaderFile=FarsiRichEdit.h
ImplementationFile=FarsiRichEdit.cpp

[CLS:CFtexedApp]
Type=0
BaseClass=CWinApp
HeaderFile=Ftexed.h
ImplementationFile=Ftexed.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Ftexed.cpp
ImplementationFile=Ftexed.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CFtexedDoc]
Type=0
BaseClass=CDocument
HeaderFile=FtexedDoc.h
ImplementationFile=FtexedDoc.cpp
LastObject=CFtexedDoc
Filter=N
VirtualFilter=DC

[CLS:CFtexedView]
Type=0
BaseClass=CScrollView
HeaderFile=FtexedView.h
ImplementationFile=FtexedView.cpp
LastObject=CFtexedView
Filter=C
VirtualFilter=VWC

[CLS:CGotoDlg]
Type=0
BaseClass=CDialog
HeaderFile=GotoDlg.h
ImplementationFile=GotoDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=IDD_VISIT_HOMEPAGE

[CLS:CPrintDLG]
Type=0
BaseClass=CDialog
HeaderFile=PrintDLG.h
ImplementationFile=PrintDLG.cpp

[CLS:CReplace]
Type=0
BaseClass=CDialog
HeaderFile=Replace.h
ImplementationFile=Replace.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_REPLACE_ALL

[CLS:CSearch]
Type=0
BaseClass=CDialog
HeaderFile=Search.h
ImplementationFile=Search.cpp

[CLS:CSplashWnd]
Type=0
BaseClass=CWnd
HeaderFile=Splash.h
ImplementationFile=Splash.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342177294
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_VIEWTEAM,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_GOTO]
Type=1
Class=CGotoDlg
ControlCount=3
Control1=IDC_GOTO_Line,edit,1350631552
Control2=IDOK,button,1342242816
Control3=IDCANCEL,button,1342242816

[DLG:IDD_DIALOGPRINT]
Type=1
Class=CPrintDLG
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIOHPLJ,button,1342177289
Control5=IDC_RADIOHPLJH,button,1342177289
Control6=IDC_RADIOLQL,button,1342177289
Control7=IDC_RADIOLQM,button,1342177289
Control8=IDC_RADIOLQH,button,1342177289
Control9=IDC_EDITFROMPAGE,edit,1350631552
Control10=IDC_EDITTOPAGE,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDITTOFILE,edit,1350631552

[DLG:IDD_REPLACE]
Type=1
Class=CReplace
ControlCount=7
Control1=IDC_FIND_NEXT,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_REPLACE,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_REPLACE_ALL,button,1342242816

[DLG:IDD_SEARCH]
Type=1
Class=CSearch
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_ABOUT
Command8=ID_FARSI
Command9=ID_ENGLISH
Command10=ID_RUN
Command11=ID_DVI
Command12=ID_DVIPS
Command13=ID_GS
CommandCount=13

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=IDD_READ_HELP
Command8=ID_APP_ABOUT
Command9=IDD_VISIT_HOMEPAGE
CommandCount=9

[MNU:IDR_NONAMETYPE]
Type=1
Class=CFtexedView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_IMPORT
Command12=ID_EDIT_GO
Command13=ID_EDIT_SEARCH
Command14=ID_EDIT_SEARCHAGAIN
Command15=ID_EDIT_REPLACE
Command16=ID_VIEW_REFRESH
Command17=ID_VIEW_DEF_MODE
Command18=ID_VIEW_OPTIONS_DEF_CARET_NEXT
Command19=ID_VIEW_OPTIONS_CARETCASE
Command20=ID_SYNTAXOFF
Command21=ID_VIEW_TOOLBAR
Command22=ID_VIEW_STATUS_BAR
Command23=ID_RUN_RUN
Command24=ID_RUN_VIEW
Command25=ID_RUN_CNVRT
Command26=ID_RUN_PS
Command27=ID_RUN_GS
Command28=ID_RUN_FTXTOUNI
Command29=ID_RUN_MKIND
Command30=ID_WINDOW_CASCADE
Command31=ID_WINDOW_TILE_HORZ
Command32=ID_WINDOW_ARRANGE
Command33=IDD_READ_HELP
Command34=ID_APP_ABOUT
Command35=IDD_VISIT_HOMEPAGE
CommandCount=35

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_SEARCHAGAIN
Command3=ID_EDIT_REPLACE
Command4=ID_EDIT_GO
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_EDIT_SEARCH
Command9=ID_FILE_SAVE
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_IMPORT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_NEXT_PANE
Command15=ID_PREV_PANE
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_EDIT_CUT
Command19=ID_EDIT_UNDO
Command20=ID_VIEW_REFRESH
Command21=ID_RUN_MKIND
Command22=ID_RUN_FTXTOUNI
Command23=ID_RUN_CNVRT
Command24=ID_RUN_VIEW
Command25=ID_RUN_RUN
Command26=ID_RUN_PS
Command27=ID_RUN_GS
CommandCount=27

[DLG:IDD_REPLACE (English (U.S.))]
Type=1
Class=CReplace
ControlCount=6
Control1=IDC_FIND_NEXT,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_REPLACE,button,1342242816
Control6=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_ABOUT
Command8=ID_FARSI
Command9=ID_ENGLISH
Command10=ID_RUN
Command11=ID_DVI
Command12=ID_DVIPS
Command13=ID_GS
CommandCount=13

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_NONAMETYPE (English (U.S.))]
Type=1
Class=CFtexedView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_GO
Command13=ID_EDIT_SEARCH
Command14=ID_EDIT_SEARCHAGAIN
Command15=ID_EDIT_REPLACE
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_VIEW_DEF_MODE
Command19=ID_SYNTAXOFF
Command20=ID_RUN_RUN
Command21=ID_RUN_VIEW
Command22=ID_RUN_CNVRT
Command23=ID_RUN_PS
Command24=ID_RUN_GS
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
Command28=ID_APP_ABOUT
CommandCount=28

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_SEARCHAGAIN
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_EDIT_SEARCH
Command7=ID_FILE_SAVE
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342177294

[DLG:IDD_GOTO (English (U.S.))]
Type=1
Class=CGotoDlg
ControlCount=3
Control1=IDC_GOTO_Line,edit,1350631552
Control2=IDOK,button,1342242816
Control3=IDCANCEL,button,1342242816

[DLG:IDD_SEARCH (English (U.S.))]
Type=1
Class=CSearch
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOGPRINT (English (U.S.))]
Type=1
Class=CPrintDLG
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIOHPLJ,button,1342177289
Control5=IDC_RADIOHPLJH,button,1342177289
Control6=IDC_RADIOLQL,button,1342177289
Control7=IDC_RADIOLQM,button,1342177289
Control8=IDC_RADIOLQH,button,1342177289
Control9=IDC_EDITFROMPAGE,edit,1350631552
Control10=IDC_EDITTOPAGE,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDITTOFILE,edit,1350631552

[DLG:IDD_ABOUTTEAM]
Type=1
Class=CAboutTeam
ControlCount=27
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342177294
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352

[CLS:CAboutTeam]
Type=0
HeaderFile=AboutTeam.h
ImplementationFile=AboutTeam.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutTeam

