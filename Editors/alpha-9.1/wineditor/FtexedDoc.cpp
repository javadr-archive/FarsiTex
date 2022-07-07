// FtexedDoc.cpp : implementation of the CFtexedDoc class
//

#include "stdafx.h"
#include "Ftexed.h"

#include "FtexedDoc.h"

extern BOOL save_backups;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFtexedDoc

IMPLEMENT_DYNCREATE(CFtexedDoc, CDocument)

BEGIN_MESSAGE_MAP(CFtexedDoc, CDocument)
	//{{AFX_MSG_MAP(CFtexedDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtexedDoc construction/destruction

CFtexedDoc::CFtexedDoc()
{
	// TODO: add one-time construction code here

	numLines = 0;

	// Initialize header of link list.
	m_head = new LINETYPE;
	m_head -> data = new BYTE[MAX_TLEN / 2 + 1];
	m_head -> last = NULL;
	m_head -> next = NULL;
	m_head -> len = m_head -> base = 0;
	m_current = m_head;
	
	// Filling the silly blank string.
	for (int i = 0; i < MAX_TLEN / 2; i++)
		blanks[i] = (char)255;
	blanks[MAX_TLEN / 2] = 0;

	strcpy((char *)m_head -> data, blanks);

	BeginSelected.x = EndSelected.x = -1;
}

CFtexedDoc::~CFtexedDoc()
{
	// Delete the link list.
	LINETYPE *p;

	while (m_head != NULL) {
		p = m_head;
		m_head = m_head -> next;
		
		delete[] p->data;
		delete p;
	}
}

BOOL CFtexedDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// This function is used while saving a file. It maps some of farsi characters 
// to the corresponding non_standard farsi characters in the ".ftx" file.
inline UCHAR SavingMap(UCHAR ch)
{
	switch(ch) {
	case 255: //space 
		ch = 218;
		break;

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

// This function is used while loading a file. It maps some of non_standard
// characters in the ".ftx" file to the corresponding farsi character.
// It also replaces tabs with appropriate number of tabs.

inline void LoadingMap(UCHAR &ch, BOOL &is_char_pushed, int &num_space_in_tab)
{

	switch (ch) {
	case 218: // farsi space 
		ch = 255;
		break;

	case 176: //fathe
		ch = 1;
		break;
	
	case 177: //kasre
		ch = 2;
		break;
	
	case 178: //zamme
		ch = 3;
		break;
	
	case 179: //nasb
		ch = 4;
		break;
	
	case 180: //tashdid
		ch = 5;
		break;
	
	case 186: //alef e maghsure
		ch = 6;
		break;
	
	case 187: //hamze
		ch = 7;
		break;
	
	case 192: //
		ch = 14;
		break;
	
	case 193: //taa
		ch = 19;
		break;
	
	case 194: //zaa
		ch = 20;
		break;
	
	case 195: //
		ch = 21;
		break;
	
	case 196: //saken
		ch = 22;
		break;
	
	case 188: //
		ch = 11;
		break;
	
	case 191: //te
		ch = 12;
		break;
	
	case 200: //zarb
		ch = 23;
		break;
	
	case 201: //mad
		ch = 25;
		break;
	
	case 205: //jame'
		ch = 27;
		break;
	
	case 9:  //tab
		num_space_in_tab ++;
		if (num_space_in_tab != 7)								
			is_char_pushed = FALSE;
		else 
			num_space_in_tab = 0;
		ch = 255;
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CFtexedDoc serialization

void CFtexedDoc::Serialize(CArchive& ar)
{
	LINETYPE *tmp = m_head;

	if (ar.IsStoring())
	{
		// TODO: add storing code here

		UCHAR ch, buf[MAX_TLEN / 2]; 
		CString CSinit;

		UINT base, current, len, buflen = 0;
		enum tag_mode{UNDEFINED, FARSI, ENGLISH} mode = UNDEFINED;
	
		BeginWaitCursor();

		while (tmp) {
		
			if (mode == UNDEFINED) {
			
				if ISL2R(tmp) {
					mode = ENGLISH;
					base = 1;
					current = 1;
					ar << '>';
					len = tmp -> len;

				}
		
				else {
					mode = FARSI;
					base = MAX_TLEN / 2 - 1;
					current = 0;
					ar << '<';
					len = tmp -> len;
				}
			}

			else {
				if (current == len) {
				
					if (buflen) {
						while (buflen--)
							ar << buf[buflen];
						buflen++;
					}
				
					tmp = tmp->next;
			
					mode = UNDEFINED;
				
					if (tmp) {
						ar << '\15';
						ar << '\12';
					}
				}
		
				else {
					switch (mode) {
					case FARSI:
						ch = (tmp->data)[base - current];

						if ((ch & 0x80) || (ch < 32)) {
						
							if (!buflen)
								ar << SavingMap((tmp->data)[base - current++]);
						
							else {
								while (buflen--)
									ar << buf[buflen];
								buflen++;	
							
								ar << SavingMap((tmp->data)[base - current++]);
							}
						}
						else
							buf[current++, buflen++] = ch;
										
					break;
		
					case ENGLISH:
						ch = (tmp->data)[current];
						if (!((ch & 0x80) || (ch < 32))) {
					
							if (!buflen)
								ar << (tmp->data)[current++];
							else {
								while (buflen--)
									ar << buf[buflen];
								buflen++;
								ar << (tmp->data)[current++];
							}
						}
						else
							buf[current++, buflen++] = SavingMap(ch);
					
					break;
					}
				
				}
			}	
		} 

		if (buflen) {
			while (buflen--)
				ar << buf[buflen];
			buflen++;
		}

		SetModifiedFlag(FALSE);

		EndWaitCursor();
	}

	else
	{
		// TODO: add loading code here

		UCHAR ch, buf[MAX_TLEN / 2]; 
		UINT base, len = 0, buflen = 0;
		int num_space_in_tab = 0;
		enum tag_mode {UNDEFINED, FARSI, ENGLISH} mode = UNDEFINED;
		BOOL is_char_pushed = FALSE;
		BOOL tab_flag = FALSE;

		BeginWaitCursor();
		while (1) {
			if (!is_char_pushed)
				if (ar.Read(&ch, 1) == 0)
					break;
			
			is_char_pushed = FALSE;
			if (ch == '\r')
				continue;

			if (mode == UNDEFINED) {
			
				if (ch == '<') {
					mode = FARSI;
					base = MAX_TLEN / 2 - 1;
					len = 0;
				}
		
				else {
					mode = ENGLISH;
					len = base = 1;
					(tmp->data)[0] = '>';
				
					if (ch != '>')
						is_char_pushed = TRUE;
				}
			}

			else {
				if (ch == '\n') {
					if (buflen)
						switch (mode) {
						case FARSI:
							while (buflen--)
								(tmp->data)[base--] = buf[len++, buflen];
							buflen++;
						break;
					
						case ENGLISH:
							while (buflen--)
								(tmp->data)[base++] = buf[len++, buflen];
							buflen++;
						break;
						}
					tmp->len = len;
				
					numLines++;
					tmp->next = new LINETYPE;
					tmp->next->data = new BYTE[MAX_TLEN / 2 + 1];
					tmp->next->last = tmp;
					tmp = tmp->next;
					tmp->next = NULL;
				
					strcpy((char *)tmp->data, blanks);
					len = 0;
					mode = UNDEFINED;
				}
		
				else {

					switch (mode) {
	
					case FARSI:
						if (ch & 0x80) {
						
							LoadingMap(ch, is_char_pushed, num_space_in_tab);
						
							if (!buflen)
								(tmp->data)[len++, base--] = ch;
						
							else {
								while (buflen--)
									(tmp->data)[base--] = buf[len++, buflen];
								buflen++;	
								(tmp->data)[len++, base--] = ch;
							}
						}
						else
							buf[buflen++] = ch;
										
						break;
		
					case ENGLISH:
						if (!(ch & 0x80)) {
						
							if (ch == 9) {//tab
								num_space_in_tab ++;
								if (num_space_in_tab != 7) {
									is_char_pushed = TRUE;
									tab_flag = TRUE;
								}
								else {
									num_space_in_tab = 0;
									is_char_pushed = FALSE;
									tab_flag = FALSE;
									ch = 32;
								}
							
							}

							if (!buflen)
								(tmp->data)[len++, base++] = (tab_flag) ? 32 : ch;
							else {
								while (buflen--)
									(tmp->data)[base++] = buf[len++, buflen];
								buflen++;

								(tmp->data)[len++, base++] =  (tab_flag) ? 32 : ch;;
							}
						}
						else {
							LoadingMap(ch, is_char_pushed, num_space_in_tab);
							buf[buflen++] = ch;
						}
					
					break;
					}
				}
			}	
		} 

		if (buflen)
			switch (mode) {
			case FARSI:
				while (buflen--)
					(tmp->data)[base--] = buf[len++, buflen];
				buflen++;
			break;
				
			case ENGLISH:
				while (buflen--)
					(tmp->data)[base++] = buf[len++, buflen];
				buflen++;
			break;
			}

		// Set proper length for last line.
		tmp->len = len;

		EndWaitCursor();
	}

	CString strFilePath = ar.GetFile()->GetFilePath();
	int endOfPath = strFilePath.ReverseFind('\\');
	CString path;
	for (int i = 0; i < endOfPath; i++)
	{
		path += strFilePath.GetAt(i);
	}
	
	::SetCurrentDirectory(path);

}

void CFtexedDoc::ConvertToLogical(const char *ph, char *lg)
{

	UCHAR ch, buf[MAX_TLEN / 2]; 
	UINT base, current, len, buflen = 0;
	enum tag_mode{UNDEFINED, FARSI, ENGLISH} mode = UNDEFINED;
	
	len = strlen(ph);

	while (1) {

		if (mode == UNDEFINED) {
		
			if (*ph == '>') {
				mode = ENGLISH;
				base = 1;
				current = 1;
				*(lg++) = '>';
			}
		
			else {
				mode = FARSI;
				base = MAX_TLEN / 2 - 1;
				current = 0;
			}
		}

		else {
			if (current == len) {
			
				if (buflen) {
					while (buflen--)
						*(lg++) = buf[buflen];
					buflen++;
				}
				
				*lg = '\0';

				return;
			}
		
			else {
				switch (mode) {
				case FARSI:
					ch = ph[base - current];
					if ((ch & 0x80) || (ch < 32)) {
					
						if (!buflen)
							*(lg++) = ph[base - current++];
						
						else {
							while (buflen--)
								*(lg++) = buf[buflen];
							buflen++;	
							
							*(lg++) = ph[base - current++];
						}
					}

					else
						buf[current++, buflen++] = ch;
								
				break;
	
				case ENGLISH:
					ch = ph[current];
					if (!((ch & 0x80) || (ch < 32))) {
					
						if (!buflen)
							*(lg++) = ph[current++];
						else {
							while (buflen--)
								*(lg++) = buf[buflen];
							buflen++;
							*(lg++) = ph[current++];
						}
					}

					else
						buf[current++, buflen++] = ch;

				break;
				}
				
			}
		}	
	} 

	if (buflen)
		while (buflen--)
			*(lg++) = buf[buflen];

}

void CFtexedDoc::ConvertToPhysical(const char *lg, char *ph, BYTE *c, BOOL isFarsiLine)
{
	UCHAR ch, buf[MAX_TLEN / 2];
	
	BYTE *base_c = c;
	BYTE color, cbuf[MAX_TLEN / 2], d[MAX_TLEN / 2];

	UINT base, len = 0, buflen = 0;


	BYTE stored = 0;

	enum tag_mode {UNDEFINED, FARSI, ENGLISH} mode = UNDEFINED;

	while (1) {
		
		if (!stored) {
			if (*lg) {
				ch = *(lg++);
				color = *(c++);
			}
			else
				break;
		}

		stored = 0;

		if (mode == UNDEFINED) {
		
			if (isFarsiLine) {
				mode = FARSI;
				base = MAX_TLEN / 2 - 1;
				len = 0;
				stored = 1;
			}
	
			else {
				mode = ENGLISH;
				len = base = 1;
				ph[0] = '>';
				d[0] = color;
			}
		}

		else {
			if (ch == '\0') {
				if (buflen)
					switch (mode) {
					case FARSI:
						while (buflen--) {
								d[base] = cbuf[buflen];
								ph[base--] = buf[len++, buflen];
						}
							buflen++;
					break;
				
					case ENGLISH:
						while (buflen--) {
							d[base] = cbuf[buflen];
							ph[base++] = buf[len++, buflen];
						}
						buflen++;
					break;
					}
							
			}
		
			else {

				switch (mode) {

				case FARSI:
					if ((ch & 0x80)  || (ch < 32)) {

						if (!buflen) {
							d[base] = color;
							ph[len++, base--] = ch;
						}
						
						else {
							while (buflen--) {
								d[base] = cbuf[buflen];
								ph[base--] = buf[len++, buflen];
							}
							buflen++;
							d[base] = color;
							ph[len++, base--] = ch;
						}
					}
					else {
						cbuf[buflen] = color;
						buf[buflen++] = ch;
					}			
					break;
		
				case ENGLISH:
						if (!(ch & 0x80 || (ch < 32 && ch != 19 && ch != 20 && ch != 1 && ch != 2 && 
						   ch != 3 && ch != 4 && ch != 5 && ch != 6 && ch != 7 && ch != 14
						   && ch != 21 && ch != 22 && ch != 11 && ch != 12 && ch != 23 
						   && ch != 25 && ch != 27))) {

						if (!buflen) {
							d[base] = color;
							ph[len++, base++] = ch;
						}
						else {
							while (buflen--) {
								d[base] = cbuf[buflen];
								ph[base++] = buf[len++, buflen];
							}
							buflen++;

							d[base] = color;
							ph[len++, base++] = ch;
						}
					}
					else {
						cbuf[buflen] = color;
						buf[buflen++] = ch;
					}
				
				break;
				}
			}
		}	
	} 

	if (buflen)
		switch (mode) {
		case FARSI:
			while (buflen--) {
				d[base] = cbuf[buflen];
				ph[base--] = buf[len++, buflen];
			}
			buflen++;
		break;
				
		case ENGLISH:
			while (buflen--) {
				d[base] = cbuf[buflen];
				ph[base++] = buf[len++, buflen];
			}
			buflen++;
		break;
		}
	
	for (int i = 0; i < MAX_TLEN / 2; i++)
		base_c[i] = d[i];

}

void CFtexedDoc::SaveBackup()
{
	CString sFileName = GetPathName();

	if (!sFileName.IsEmpty())
	{
		sFileName.MakeUpper();
		sFileName.Replace(".FTX", "");
		
		DWORD dwAttrib = GetFileAttributes(sFileName + ".BAK");
		if (dwAttrib != 0xFFFFFFFF)
		{
			if (dwAttrib & FILE_ATTRIBUTE_READONLY)
			{
				SetFileAttributes(sFileName + ".BAK", dwAttrib & ~FILE_ATTRIBUTE_READONLY);
			}
		}
		if(!CopyFile(sFileName + ".FTX", sFileName + ".BAK", FALSE))
		{
			AfxMessageBox("FarsiTeX Editor failed to save a backup file.");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFtexedDoc diagnostics

#ifdef _DEBUG
void CFtexedDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFtexedDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFtexedDoc commands

void CFtexedDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	if (save_backups)
		SaveBackup();

	CDocument::OnFileSave();
}
