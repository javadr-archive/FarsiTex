#if !defined(AFX_REPLACE_H__8880EC24_B9F7_4853_A4A1_A1088786076D__INCLUDED_)
#define AFX_REPLACE_H__8880EC24_B9F7_4853_A4A1_A1088786076D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Replace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplace dialog
#include "FarsiRichEdit.h"
#include "FtexedDoc.h"
#include "FtexedView.h"

#define MAX_REPLACE_SIZE 475

class CReplace : public CDialog
{
// Construction
public:
	CReplace(CWnd* pParent = NULL);   // standard constructor
	CFarsiRichEdit m_Edit;
	CFarsiRichEdit m_Replace;
	LOGFONT logFont;    // Font structure used in OnDraw
	CFont *font;        // Used in manipulating fonts 
	CString strFind;
	CString strReplace;
	CString UnMap(CString s);
	inline BYTE GetFontChar(BYTE ch);
	void SetView(CFtexedView* pView);
	CFtexedView* pFtexView;

// Dialog Data
	//{{AFX_DATA(CReplace)
	enum { IDD = IDD_REPLACE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplace)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFindNext();
	afx_msg void OnReplace();
	afx_msg void OnReplaceAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACE_H__8880EC24_B9F7_4853_A4A1_A1088786076D__INCLUDED_)
