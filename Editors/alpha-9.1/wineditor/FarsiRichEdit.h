#if !defined(AFX_CFarsiRichEdit_H__50C9DF22_3261_11D3_B33E_8DCDF03A410C__INCLUDED_)
#define AFX_CFarsiRichEdit_H__50C9DF22_3261_11D3_B33E_8DCDF03A410C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FarsiRichEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FarsiRichEdit window

#define CTRLE 5
#define CTRLF 6
#define CTRLG 7
#define BACKSPACE 8
#define ENTER 13
#define CTRLY 25
#define SPACE 32
#define W_font 8
#define MAX_LEN 51
#define begin_x 420
#define ALEF  145
#define LAM	  243
#define LA  242
#define CAPSLOCK 20

class CFarsiRichEdit : public CRichEditCtrl
{
// Construction
public:
	CFarsiRichEdit();
	int join_to_prev(UCHAR);
	int not_join_to_prev(UCHAR);
	UCHAR farsi_upper_case ( UCHAR c );
	int Map(UINT &ch);
	void SetCursorPos();
	UCHAR prev_char();
	int joins_to_next (UCHAR c);
	
	UCHAR Line[512];
	UCHAR search_map[256];
	BYTE GetFontChar(BYTE ch);
	CString RemapCharacters(CString s);


// Attributes
public:
	BOOL fMode, fFirsttime;
	BOOL fSelect, caps, shift;

// Operations
public:
	int pos;
	int number_digit;
	CString str;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFarsiRichEdit)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFarsiRichEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFarsiRichEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFarsiRichEdit_H__50C9DF22_3261_11D3_B33E_8DCDF03A410C__INCLUDED_)
