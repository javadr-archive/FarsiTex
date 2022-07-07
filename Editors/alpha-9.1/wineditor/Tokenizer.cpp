// Tokenizer.cpp: implementation of the CTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tokenizer.h"
#include "Ftexed.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTokenizer::CTokenizer(CString content, int wrapSizeParam)
{
	wrapSize = min(MAX_TLEN / 2 - 4, wrapSizeParam);
	wrapSize = max(30, wrapSize);
	
	index = 0;

	content.Replace("\r\n", "\n");
	content.Replace("\n\r", "\n");
	content.Replace("\r", "\n");
	content.Replace("\t", "  ");

	pBuf = new char[content.GetLength() + 1];
	strcpy(pBuf, content);

	pToken = new char[wrapSize]; /* Maximum line size would be wrapSize - 1 because
	                                each English lines starts with '>'
	                             */
}

LPCSTR CTokenizer::GetToken()
{
	if (pBuf[index] == '\0')
	{
		pToken[0] = pBuf[index];
		return pToken;
	}

	if (pBuf[index] == ' ' || pBuf[index] == '\n')
	{
		pToken[0] = pBuf[index++];
		pToken[1] = '\0';
		return pToken;
	}

	UINT count;

	for (count = 0; count < wrapSize - 1; count++)
	{
		if (pBuf[index] == ' ' || pBuf[index] == '\n' || pBuf[index] == '\0')
			break; /* Never executes when count is zero */
		
		pToken[count] = pBuf[index++];
	}
	
	pToken[count] = '\0';
	return pToken;
}

CString CTokenizer::GetPreparedLines()
{
	CString strPreparedBuf;
	CString strLine = ">";
	LPCSTR p;

	while (1)
	{
		p = GetToken();

		if ((strLine.GetLength() + strlen(p) > wrapSize) || (*p == '\n') || (*p == '\0'))
		{
			strPreparedBuf += (*p != '\0') ? strLine + '\n' : strLine;
			strLine = ">";

			if (*p == '\0')
				break;
			
			if (*p == '\n')
				continue;
		}

		strLine += p;
	}

	return strPreparedBuf;
}

CTokenizer::~CTokenizer()
{
	if (pBuf != NULL)
		delete []pBuf;
	if (pToken != NULL)
		delete []pToken;
}