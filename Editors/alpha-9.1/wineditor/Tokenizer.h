// Tokenizer.h: interface for the CTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKENIZER_H__CF8630C7_EEF2_477A_A30E_3F2F4A5E48A1__INCLUDED_)
#define AFX_TOKENIZER_H__CF8630C7_EEF2_477A_A30E_3F2F4A5E48A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTokenizer  
{
private:
	UINT wrapSize;
	long index;
	char *pBuf;
	char *pToken;
	LPCSTR GetToken();

public:
	CTokenizer(CString content, int wrapSizeParam);
	CString GetPreparedLines();
	virtual ~CTokenizer();
};

#endif // !defined(AFX_TOKENIZER_H__CF8630C7_EEF2_477A_A30E_3F2F4A5E48A1__INCLUDED_)
