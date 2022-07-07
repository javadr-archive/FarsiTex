// Ftexed.h : main header file for the FTEXED application
//

#define MAX_TLEN 510

#if !defined(AFX_FTEXED_H__8BAF8714_913B_11D2_8C6F_9734034F0434__INCLUDED_)
#define AFX_FTEXED_H__8BAF8714_913B_11D2_8C6F_9734034F0434__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFtexedApp:
// See Ftexed.cpp for the implementation of this class
//

class CFtexedApp : public CWinApp
{
private:
	void SetOptions(CString optionsFileName);
	void SetColors(CString settingsFileName, CString colorsFileName);
	CMapStringToPtr *ReadColors(CString fileName);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CFtexedApp();
	CView *ActiveView;
	char *ClipBoard;
	int CBLen;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtexedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFtexedApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTEXED_H__8BAF8714_913B_11D2_8C6F_9734034F0434__INCLUDED_)
