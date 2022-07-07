// FtexedView.h : interface of the CFtexedView class
//
/////////////////////////////////////////////////////////////////////////////


// Every Farsi or English line can have up to 256 charactes. So we define:
#define CDELETE 4
#define CTRLE 5
#define CTRLF 6
#define CTRLG 7
#define CTRLJ 10
#define BACKSPACE 8
#define ENTER 13
#define CTRLY 25
#define SPACE 32
#define SHIFTB 66
#define MAX_LINE_NUM_IN_WIN9X 2047
#define ISL2R(x) ((((x)->data)[0]) == '>')
#define CURLINE (pDoc->m_current)
#define BeginSelPoint (pDoc->BeginSelected)
#define EndSelPoint (pDoc->EndSelected)

#if !defined(AFX_FTEXEDVIEW_H__8BAF871E_913B_11D2_8C6F_9734034F0434__INCLUDED_)
#define AFX_FTEXEDVIEW_H__8BAF871E_913B_11D2_8C6F_9734034F0434__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CFtexedView : public CScrollView
{
protected: // create from serialization only
	CFtexedView();
	DECLARE_DYNCREATE(CFtexedView)


private:
	BOOL m_bHighlight;
	BOOL m_bCaretChangeCase;
	BOOL m_bDefCaretNext;

protected:

	BOOL m_bNewView;	// Indicates if this view has received any MouseMove Message before.
	CPoint m_Curs;       // Storing cursor position
	int m_pmargin;      // Number of pixels in the left margin of the window    
	int m_cmargin;      // Number of characters in the left margin of the window
	LOGFONT logFont;    // Font structure used in OnDraw
	CFont *font;        // Used in manipulating fonts 

	// The current language of editor.
	enum LANGUAGE {FARSI, ENGLISH} mode;
	
	// Default new line direction
	enum DEFAULT_MODE { FARSI_IS_DEFAULT, SAME_AS_CURRENT_LINE_IS_DEFAULT } defaultMode;


	CRect window;           // Size of current client
	CPoint topleft;         // Logical coordinates of the current window 

	int numchar1, numchar2;
	int shift;  // 0 when shift key is not being pressed, 1 otherwise. 
	int ctrl;   // 0 when control key is not being pressed, 1 otherwise.
	
	// This variable is 0 in normal mode. But when it is one,
	// in FARSI mode user is typing a FARSI number and
	// in ENGLISH mode, user is typing a command in R2L mode.
	int special_mode;

	//This variable is 1 when we are typing a Farsi number in inserted mode.
	int inserted_farsi_num;

	// Pointer to the document.
	CFtexedDoc *pDoc;

	


	//Paths 
	char m_szftxPath[100], m_szpsPath[100];
	
	//Carets
	CBitmap *m_pEnCaret;
	CBitmap *m_pFaCaret;

		


// Attributes
public:
	CFtexedDoc* GetDocument();

// Operations
public:
	
	// This procedure scrolls the client window such that cursor comes into
	// the client window and updates the topleft variable.
	// mode = 0 : normal mode
	// mode = 1 : window is moved due to use of PageUp or PageDown keys.
	// mode = 2 : window is moved due to use of Up or Down arrow keys.
	void SetProperWindow(int mode);

	// This procedure sets the scroll sizes 
	void AdjustScrollers(void);

	// This procedure does scrolling for all views of the document associated to this view
	void PerformScrolling(CPoint pt);

	// This procedure sets the caret position using m_Curs
	// data members
	void UpdateCaretPos(void);

	// Changes the language and adjusts the cursor shape
	void SetMode(LANGUAGE inp);

	// Maps ch to the corresponding Farsi character
	int Map(UINT &ch);

	// Finds the line whose number is LineNo, if LineNo is greater than
	// total number of existing lines, returns the difference between these
	// two value.
	int FindLine(int LineNo, CFtexedDoc::LINETYPE **Line);

	// Prints a line in the specified position and with specified colors
	void AssignColor(BYTE *logical, BYTE *c_vec, BOOL isFarsiLine);

	void PrintLine(CDC *pDC, int x, int y, BYTE *line, int length);

	// Moves cursor up "howmany" lines and sets the proper value for m_current 
	void GoUp(int howmany);

	// Moves cursor down "howmany" lines and sets the proper value for m_current 
	void GoDown(int howmany);

	// Checks if the cursor is after the end of line and moves it to the end of
	// line in both L2R and R2L lines
	void ValidateCursorPos(void);

	// Deletes a character in the current line and current cursor position.
	void DelChar(void);

	int join_to_prev(UCHAR);
	int not_join_to_prev(UCHAR);
	UCHAR farsi_upper_case(UCHAR c);
	UCHAR prev_char();
	int joins_to_next (UCHAR c);

	UCHAR ShiftSpaceMap ( UCHAR c );

	// Handles the special keys when being called from OnChar
	void HandleSpecialKeys(UINT nChar);
	void Handle$(UINT nChar);

	// Determines whether or not p1 is after p2
	BOOL IsGreater(CPoint p1, CPoint p2);
	
	// Shrinks rectangle in document so that it is completely visible
	void ShrinkRect(CRect &Rect);

	// Invalidates a block between two points p1 and p2
	// p1 = (-1,x) means from beginning of the line
	// p2 = (-1,x) means to the end of the line
	// p2 = (-1,-1) means invalidate to the end of view
	// Otherwise, p1 and p2 are the logical coordinates of the region
	// which is supposed to be invalidated.
	void InvalidateBlock(CPoint p1, CPoint p2);

	// Unselects the selected portion of text
	void Unselect(void);

	// Finds all the views of this view's document
	void FindAllViews(CFtexedView **Views);

	// Finds number of bytes needed to save the clipboard
	int NumberOfBytes(CFtexedDoc::LINETYPE *FirstLine);

	// Invalidates the specified region. Note that this region is specified logically, not physically!
	void LogicalInvalidate(CPoint BeginP, CPoint EndP);


	//Determines whether ch is a separator character or not
	BOOL IsSeparator(BYTE ch);

	// searches for a word
	BOOL Search(void);
	//Search String
	CString SearchStr;

	CString ReplaceStr;
	bool endReplace;
	bool search_is_done;
	bool replaceAll;
	void Replace();
	void ReplaceAll();
	void RemoveSelectedArea();
	void OnEditOnlyPaste();

	BYTE GetFontChar(BYTE ch);
	void RemapCharacters(const BYTE *pFrom, BYTE *pTo);
	BOOL DoSaveUpdate(CString sFileName);
	int  SkipEraab(int fromPosition);
	BOOL IsLogicalEraab(BYTE c);
	BOOL IsLogicalSeparator(BYTE c);
	BOOL IsNumber(BYTE c);
	BOOL IsLogicalCommandSeparator(BYTE c);
	BOOL IsRunningOnNT();
	BOOL ReadClipboard(CString *pString);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtexedView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFtexedView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CFtexedView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEditGo();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateFarsi(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnglish(CCmdUI* pCmdUI);
	afx_msg void OnFarsi();
	afx_msg void OnEnglish();
	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLnCol(CCmdUI* pCmdUI);
	afx_msg void OnEditSearch();
	afx_msg void OnEditSearchAgain();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRunRun();
	afx_msg void OnRunCnvrt();
	afx_msg void OnRunPs();
	afx_msg void OnRunView();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGhostView();
	afx_msg void OnRunFTeX();
	afx_msg void OnUpdateEDITSearchAgain(CCmdUI* pCmdUI);
	afx_msg void OnRunGs();
	afx_msg void OnSyntaxoff();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnUpdateSyntaxoff(CCmdUI* pCmdUI);
	afx_msg void OnViewDefMode();
	afx_msg void OnUpdateViewDefMode(CCmdUI* pCmdUI);
	afx_msg void OnEditReplace();
	afx_msg void OnDvi();
	afx_msg void OnDvips();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewOptionsCaretcase();
	afx_msg void OnUpdateViewOptionsCaretcase(CCmdUI* pCmdUI);
	afx_msg void OnDefCaretNext();
	afx_msg void OnUpdateDefCaretNext(CCmdUI* pCmdUI);
	afx_msg void OnViewRefresh();
	afx_msg void OnEditImport();
	afx_msg void OnRunMkind();
	afx_msg void OnRunFtxtouni();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FtexedView.cpp
inline CFtexedDoc* CFtexedView::GetDocument()
   { return (CFtexedDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTEXEDVIEW_H__8BAF871E_913B_11D2_8C6F_9734034F0434__INCLUDED_)
