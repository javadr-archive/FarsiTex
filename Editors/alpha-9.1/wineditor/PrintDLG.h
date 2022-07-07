#if !defined(AFX_PRINTDLG_H__40E37181_807A_11D4_ADAD_F79EE3FA262B__INCLUDED_)
#define AFX_PRINTDLG_H__40E37181_807A_11D4_ADAD_F79EE3FA262B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintDLG dialog

class CPrintDLG : public CDialog
{
// Construction
public:
	CPrintDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintDLG)
	enum { IDD = IDD_DIALOGPRINT };
	UINT	m_ToPage;
	UINT	m_FromPage;
	CString	m_EditToFile;
	//}}AFX_DATA

	UINT PrinterType;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintDLG)
	afx_msg void OnRadiohplj();
	afx_msg void OnRadiohpljh();
	afx_msg void OnRadiolqh();
	afx_msg void OnRadiolql();
	afx_msg void OnRadiolqm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTDLG_H__40E37181_807A_11D4_ADAD_F79EE3FA262B__INCLUDED_)
