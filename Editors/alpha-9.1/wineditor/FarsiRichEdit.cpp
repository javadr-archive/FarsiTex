// CFarsiRichEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Ftexed.h"
#include "FarsiRichEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFarsiRichEdit


CFarsiRichEdit::CFarsiRichEdit()
{
	fMode = true;
	pos = 0;
	shift = false;
	caps = false;
	fSelect = false;
	number_digit = 0;
	fFirsttime = true;

	/***********Reading Current directory from Registry*********/
	HKEY ftxHandle;
	char szftxPath[100];
	long lftxSize = 100;

	if (RegOpenKey(HKEY_LOCAL_MACHINE,
		"Software\\CLASSES\\FarsiTeX.Document\\shell\\open\\command", &ftxHandle) == ERROR_SUCCESS) {
	    RegQueryValue(ftxHandle, NULL, szftxPath, &lftxSize);
		RegCloseKey(ftxHandle);
	}

	CString sKey = szftxPath;
	int len = sKey.GetLength();

	sKey.Delete(len - 15, 15);
	sKey += "ftexkeyb.dat";

	FILE *pf;

	if ((pf = fopen(sKey,"rb")) == 0) {
		AfxMessageBox("Can't find ftexkeyb.dat!");
		return;
	}

	fread(search_map, 1, 256, pf);
	fclose(pf);

	
}

CFarsiRichEdit::~CFarsiRichEdit()
{
}


BEGIN_MESSAGE_MAP(CFarsiRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CFarsiRichEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFarsiRichEdit message handlers

LRESULT CFarsiRichEdit::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (message == WM_KEYDOWN && fSelect &&(wParam == VK_LEFT || wParam == VK_DELETE ||
		wParam == VK_UP)) {
		fSelect = false;
		SetWindowText(RemapCharacters(str));
		SetCursorPos();
	}

	
	if (message == WM_KEYUP)
		if (wParam == VK_SHIFT)//SHIFT
			shift = false;
	
	if (message == WM_KEYDOWN && fMode) {//FARSI
		if (wParam == CAPSLOCK)//Caps Lock
			caps = !caps;

		if (wParam == VK_SHIFT)
			shift = true;

		if (!str.IsEmpty()) {
			GetWindowText(str);

			if (wParam == BACKSPACE) {

				wParam = VK_DELETE;
			}else if (wParam == VK_DELETE) {
				if (number_digit > 0)
					number_digit--;
				
				if (pos > 0)
					pos--;
				wParam = BACKSPACE;

			}if (wParam == VK_LEFT) {
				if (number_digit > 0)
					number_digit--;

				if (pos >0)
					pos--;
			}else if (wParam == VK_RIGHT) {

				if (pos < str.GetLength()) {
					number_digit = 0;
					pos++;
				}
			}else if (wParam == VK_HOME) {
				number_digit = 0;
				pos = str.GetLength();
				wParam = VK_END;
			}else if (wParam == VK_END) {
				number_digit = 0;
				pos = 0;
				wParam = VK_HOME;
			}		

		}
	}else if (message == WM_KEYDOWN) {//ENGLISH
		if (wParam == CAPSLOCK)//Caps Lock
			caps = !caps;

		if (wParam == VK_SHIFT)
			shift = true;

		if (!str.IsEmpty()) {

			if (wParam == BACKSPACE) {
				if (pos > 0)
					pos--;				
			}if (wParam == VK_LEFT) {
				if (pos >0)
					pos--;
			}else if (wParam == VK_RIGHT) {
				if (pos < str.GetLength()) {
					pos++;
				}
			}else if (wParam == VK_HOME) {
				pos = str.GetLength();
				wParam = VK_END;
			}else if (wParam == VK_END) {
				pos = 0;
				wParam = VK_HOME;
			}		

		}
	}

	return CRichEditCtrl::DefWindowProc(message, wParam, lParam);

}

void CFarsiRichEdit::SetCursorPos()
{
	
	UINT upTemp = pos;
	UINT unTemp = number_digit;

	if (!fSelect) {
		WindowProc(WM_KEYDOWN, VK_END, 0);
		number_digit = unTemp;
		for (UINT i = 0; i < upTemp; i++) 
			WindowProc(WM_KEYDOWN, VK_RIGHT, 0);
		number_digit = unTemp;
	}else {
		HideSelection(TRUE, FALSE);//hide selected text (not change the background color)
		WindowProc(WM_KEYDOWN, VK_END, 0);
		for (UINT i = 0; i < upTemp; i++) 
			WindowProc(WM_KEYDOWN, VK_RIGHT, 0);
	}

}

void CFarsiRichEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	//Changing mode 
	if (nChar ==  CTRLG)
		if (fMode)
			fMode = false;
		else
			fMode = true;

	else if (nChar == CTRLF)
		fMode = true;

	else if (nChar == CTRLE)
		fMode = false;
	

	if ((nChar <= 128) && (nChar >= 32) && (fFirsttime))
		ReplaceSel("");//Erase Text firsttime if a character recive

	GetWindowText(str);

	if (str.GetLength() == 0)
		pos = 0;
	
	if (str.GetLength() >= MAX_LEN)//if String exceeds from return
		return;

	
	if (fFirsttime)
		fFirsttime = false;

	if(caps != shift)
		fSelect = true;

	if (number_digit > 0 && !isdigit(nChar) && nChar <= 128 && nChar >= 32){
		//directing number mode
		pos -= number_digit;
		number_digit = 0;
	}

	if (fMode && nChar >= 32 && nChar <= 128 && !isdigit(nChar)) {//Farsi
		
		Map(nChar);
		CString sTemp = nChar;

		if (pos == 0) {//if cursor is end of string
			sTemp += str;
			SetWindowText(RemapCharacters(sTemp));
		}else {
			CString sNew;

			
			for (int i = 0; i < pos; i++)
				if (i >= 0 && i < str.GetLength())
					sNew += str[(int)i];

			sNew += sTemp;

			for (i = pos; i < str.GetLength(); i++)
				if (i >= 0 && i < str.GetLength())
					sNew += str[(int)i];

			SetWindowText(RemapCharacters(sNew));

			SetCursorPos();
		}
		
		/*directing la*/
		
		UCHAR ucPrev;
		if (nChar == ALEF) {
			if (pos < str.GetLength() && pos >= 0)
				 ucPrev = str[(int)pos];

			if (ucPrev == LAM) {
				CString sNew;

				if (pos <= str.GetLength())
					for (int i = 0; i < pos; i++)
						sNew += str[(int)i];

				sNew += (UINT)LA;
				
				int i = 0;
				for (i = pos + 1; i < str.GetLength(); i++)
					sNew += str[(int)i];

				SetWindowText(RemapCharacters(sNew));
				SetCursorPos();

			}
		}
	}else if (fMode && nChar>=32 && nChar <=128 && isdigit(nChar)) {//writing digit
		number_digit++;
		CString sNew;

		Map(nChar);
		CString sTemp = nChar;	
		
		if (pos <= str.GetLength())
			for (int i = 0; i < pos; i++)
				sNew += str[(int)i];

		sNew += sTemp;

		int i = 0;
		for (i = pos; i < str.GetLength(); i++)
			sNew += str[(int)i];


		SetWindowText(RemapCharacters(sNew));

		pos++;
		SetCursorPos();
		
	}else if ((nChar >= 32)&&(nChar <= 128)) {//English Charater
		pos ++;
		CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
	}
	GetWindowText(str);
}

void CFarsiRichEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	int x = (begin_x - point.x) / W_font;
	/*
	int y  = (begin_x - point.x) - x * W_font;
	int z = W_font / 2;
	*/
	
	GetWindowText(str);
	if (!str.IsEmpty()) 
		if (x < str.GetLength()) 
			pos = str.GetLength() - x - 1;
		
	
	CRichEditCtrl::OnLButtonDown(nFlags, point);
}

UCHAR  CFarsiRichEdit::prev_char()
{
	
	int i = pos ;
	while ((str[i] > 0 && str[i] < 8) || str[i] == 22) {//eraab
		i++;
		if (i == str.GetLength())
			break;
	}
	if (i == str.GetLength())
		return(' ');
	return (str[i]);
		
}

int CFarsiRichEdit::Map(UINT &ch)
{

	UCHAR prev, next;

	GetWindowText(str);

	if (pos < str.GetLength() && pos >= 0)
		prev = prev_char();
	else
		prev = ' ';

	if ((pos > str.GetLength())&&(!isdigit(ch)))
		if (str.GetLength() > 0)
			next = str[str.GetLength()-1];
	else if (pos > 0 && pos <= str.GetLength())
		next = str[(int)pos - 1];
	else
		next = ' ';

	int retval = 0;

	/* return value:
	0 : changing is done compeletly in this function.
	1 : we are in R2L direction and prev character(just right the cursor)
		is converted to uppercase and must be rewritten.
	2 : we are in L2R direction and the character(just left the cursor)
		is converted and must be rewritten. */

/*******************************************************/
		// 1-maping inserted char
		if (ch == 121 || ch == 117 || ch == 105 || 
			ch == 104) {
				if (join_to_prev(prev)) {			
					switch (ch) {
						case 121://ghein!!
							ch = 231;
							break;
						case 117://ein!!
							ch = 227; 
							break;
						case 105://he!!
							ch = 250;
							break;
						case 104://aa!!
							ch = 145;
							break;
					}
				}
				else
					ch = search_map[UCHAR(ch)];
				
		}

		else 
				ch = search_map[UCHAR(ch)];

/****************************************************************/
		//2-mapping next char (after inserted char if exists).
			
				UCHAR c = next;

				if (join_to_prev((UCHAR)ch)) {			
			
					switch (c) {
						case 229://ghein!!
							c = 230;
							break;
						case 232://ghein!!
							c = 231;
							break;
						case 228://ein!!
							c = 227; 
							break;
						case 225://ein!!
							c = 226; 
							break;
						case 251://he!!
							c = 250;
							break;
						case 144://aa!!
							c = 145;
							break;
					}
				}
				else {
					switch (c) {
						case 230://ghein!!
							c = 229;
							break;
						case 231://ghein!!
							c = 232;
							break;
						case 227://ein!!
							c = 228; 
							break;
						case 226://ein!!
							c = 225; 
							break;
						case 250://he!!
							c = 251;
							break;
						case 145://aa!!
							c = 144;
							break;
					}
				}

				if (next != c) {
					if (pos <= str.GetLength() && pos > 0) {
						str.SetAt(pos-1, c);
						SetWindowText(RemapCharacters(str));
					}
				}			
			
		

	

/*********************************************************************/
		//3-mapping prev char

		// returns 1 if ch does not join to prev farsi char
		if (not_join_to_prev(ch)) {
			//if ch does not join to prev farsi char a convert
			//for making prev farsi char upper case is needed

			UCHAR c =farsi_upper_case(prev);

			if (c == 252) //ie
				if (pos + 1 < str.GetLength()) {
					if (!joins_to_next(str[pos + 1]))
						c = 253;
				}else
						c = 253;

			if (c != prev) {
				if (pos >= 0 && pos < str.GetLength()) {
					str.SetAt(pos, c);
					SetWindowText(RemapCharacters(str));
				}

			}
			//if 1 the last two character must be written			
		}
		
		
		return retval;

}

int CFarsiRichEdit::joins_to_next (UCHAR c)
{
                                // çéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ
     char far *group_141_to_175 = "-1----1-1-1-1-1-1-1-1------1-1-1-11";
                                // ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛
     char far *group_224_to_254 = "1--11--11-1-1-1-1--1-1-1--11--1";

	 if (c == 0)
		 return 0;

	 if (c==19 || c==20 || c==12) return 0;
	 if (c<8 || c==22) return 1;
	 if (c>=141 && c<=175)
		return group_141_to_175[c-141]=='1';
	else if (c>=224)
        return group_224_to_254[c-224]=='1';
	//MEHR strech
	if (c==(UCHAR)'ã')
		return 1;
	//MEHR end
	return 0;
}

int CFarsiRichEdit::join_to_prev(UCHAR ch)
{
	//if prev char is one of these ,next char will join to prev
	if ((ch == 142)||(ch == 147)||(ch ==149)||(ch == 151)||(ch==153)||
		(ch== 155)||(ch == 157)||(ch == 159)||(ch == 161)||(ch ==168)||
		(ch == 170)||(ch == 172)|| (ch ==  174)|| (ch == 175)||
		(ch == 224 )||(ch== 227)||(ch ==228)||(ch ==231)||(ch ==232)||
		(ch ==234)||(ch ==236)||(ch ==238)|| (ch ==240)||(ch == 243)|| 
		(ch == 245)||(ch ==247)||(ch ==250)||(ch == 251)||(ch ==254))
		return 1;
	return 0;

}

int CFarsiRichEdit::not_join_to_prev(UCHAR ch)
{
	
	if ((ch>=' ') && (ch<=(UCHAR)'ä'))  // english char or Farsi digit
		return 1;
	if ((ch>=(UCHAR)'ç') && (ch<=(UCHAR)'Ø'))
		return 0;
	if ((ch<8) || (ch==22))               // e'raab
		return 0;
	if ((ch==19) || (ch==20) || (ch==12))   // taa and zaa tanhaa and te gerd
		return 0;
	if ((ch>=(UCHAR)'‡') && (ch<=(UCHAR)'˛'))
		return 0;
	if (ch==(UCHAR)'ã')
		return 0;
	if (ch ==(UCHAR)210)/*\*/
		return 0;
		
	return 1;
}

UCHAR CFarsiRichEdit::farsi_upper_case ( UCHAR c )
{
								// çéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ	
	char *group_141_to_175 = "çèèêëííîîññòòööúúûû††¢£§•¶ßß©©´´≠≠.";
							// ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛
	char *group_224_to_254 = ".·‚‚·ÂÊÊÂÈÈÎÎÌÌÔÔÒÚÒÙÙˆˆ¯˘˘˘¸˝¸";

 
	if (c>=141 && c<175)
		return (UCHAR)group_141_to_175[c-141];
	else if ((c>224)&&(c<=254))
        return (UCHAR)group_224_to_254[c-224];
	else if (c == 175)
		return(search_map[88]);//taa tanhaa 
	else if (c == 224)
		return(search_map[90]);//zaa tanhaa
	return c;
}


inline BYTE CFarsiRichEdit::GetFontChar(BYTE ch)
{
	switch(ch) {
	case 1:  //fathe
		ch = 176;
		break;
	
	case 2:  //kasre
		ch = 177;
		break;
	
	case 3:  //zamme
		ch = 178;
		break;
	
	case 4:  //nasb
		ch = 179;
		break;
	
	case 5:  //tashdid
		ch = 180;
		break;
	
	case 6:  //alef
		ch = 186;
		break;
	
	case 7:  //hamze
		ch = 187;
		break;
	
	case 14:  //
		ch = 192;
		break;
	
	case 19:  //taa
		ch = 193;
		break;
	
	case 20:  //zaa
		ch = 194;
		break;
	
	case 21:  //
		ch = 195;
		break;
	
	case 22:  //saken
		ch = 196;
		break;
	
	case 11:  //
		ch = 188;
		break;
	
	case 12:  //te
		ch = 191;
		break;
	
	case 23:  //zarb
		ch = 200;
		break;
	
	case 25:  //mad
		ch = 201;
		break;
	
	case 27:  //jame'
		ch = 205;
		break;
	}
	return ch;
}

CString CFarsiRichEdit::RemapCharacters(CString s)
{
	CString ret;
	for (int i = 0; i < s.GetLength(); i++)
	{
		ret += GetFontChar(s[i]);
	}
	return ret;
}
