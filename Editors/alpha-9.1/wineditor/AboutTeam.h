#if !defined(AFX_ABOUTTEAM_H__69208193_D26C_4FB8_A82F_27154F29431A__INCLUDED_)
#define AFX_ABOUTTEAM_H__69208193_D26C_4FB8_A82F_27154F29431A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutTeam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutTeam dialog

class CAboutTeam : public CDialog
{
// Construction
public:
	CAboutTeam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutTeam)
	enum { IDD = IDD_ABOUTTEAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutTeam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutTeam)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTTEAM_H__69208193_D26C_4FB8_A82F_27154F29431A__INCLUDED_)
