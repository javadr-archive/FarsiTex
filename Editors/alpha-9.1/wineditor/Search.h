#if !defined(AFX_SEARCH_H__50C9DF21_3261_11D3_B33E_8DCDF03A410C__INCLUDED_)
#define AFX_SEARCH_H__50C9DF21_3261_11D3_B33E_8DCDF03A410C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Search.h : header file
//
#include "FarsiRichEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CSearch dialog
#define MAX_SEARCH_SIZE 435
class CSearch : public CDialog
{
// Construction
public:
	CSearch(CWnd* pParent = NULL);   // standard constructor
	CFarsiRichEdit m_Edit;
	LOGFONT logFont;    // Font structure used in OnDraw
	CFont *font;        // Used in manipulating fonts 
	CString str;

	BYTE GetFontChar(BYTE ch);
	CString UnMap(CString s);


// Dialog Data
	//{{AFX_DATA(CSearch)
	enum { IDD = IDD_SEARCH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearch)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCH_H__50C9DF21_3261_11D3_B33E_8DCDF03A410C__INCLUDED_)
