// FtexedDoc.h : interface of the CFtexedDoc class
//
/////////////////////////////////////////////////////////////////////////////

#define ISL2R(x) ((((x)->data)[0]) == '>')

#if !defined(AFX_FTEXEDDOC_H__8BAF871C_913B_11D2_8C6F_9734034F0434__INCLUDED_)
#define AFX_FTEXEDDOC_H__8BAF871C_913B_11D2_8C6F_9734034F0434__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CFtexedDoc : public CDocument
{
protected: // create from serialization only
	CFtexedDoc();
	DECLARE_DYNCREATE(CFtexedDoc)

// Attributes
public:
	// Each node of the link list has this structure:
	
	struct LINETYPE {
		BYTE *data;                  // A pointer to the line.
		LINETYPE *last, *next;       // Previous and next nodes &
		WORD len;                    // Length of this line
		WORD base;
	} *m_head, *m_current;  // Head of link list

	int numLines;           // Number of lines in the document

	// Beginning and end of selected area
	CPoint BeginSelected, EndSelected;
	
	// Will be used as a string of spaces!
	char blanks[MAX_TLEN / 2 + 1];

// Operations
public:
	void ConvertToLogical(const char *ph, char *lg);
	void ConvertToPhysical(const char *lg, char *ph, BYTE *, BOOL isFarsiLine);
	void SaveBackup();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtexedDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFtexedDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFtexedDoc)
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTEXEDDOC_H__8BAF871C_913B_11D2_8C6F_9734034F0434__INCLUDED_)
