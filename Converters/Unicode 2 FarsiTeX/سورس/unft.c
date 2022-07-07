/*
IN THE NAME OF ALLAH

PROGRAM TO CONVERT UTF-8 ENCODING TO FARSITEX INPUT ENCODING.
AUTHOR: HTTP://FARSITEX.BLOGFA.COM.
PUBLISHED UNDER GPL.

THE SOURCE FILE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "unft.h"

void PrintUsage ()
{
	fprintf (stderr, "%s\n", ERROR_MESSAGE);
}

int InputFilesAreReady (short ArgumentCounter)
{
	if (ArgumentCounter <= 2) {
		PrintUsage ();
		return 0;
	}
	return 1;
}

char GetSymbol (char chr)
{
	if (line_dir == RTL) {
      		short i, j;
         	i = j = 0;
         	for (; i <= SYMB_LIST_SIZE; ++i, ++j) 
	 		if (chr == symbol_list [j])
				return (symbol_list [j + 1]);
	}
	else return chr;
}

/*
 The Convert function.
 Each unicode character consists of two ascii characters.
 First char is 194, 216, 217, 218, or 219 -th character in machine 
 characters set (ASCII).
*/

char Convert (char chr1, char chr2, char chr3, char chr4)
{
	short i, j;

	i = j = 0;
	for (; i <= CHAR_LIST_SIZE; ++i, ++j) {
		if (chr1 == char_list [j] && chr2 == char_list [j + 1]) {
			if ((!NEXT_CHAR_IS_NON_JOINER) && (prev_char == NON_JOINER)) {
				if ((char_list [j + 2] == char_list [j + 4]) 
				|| (char_list [j + 2] == char_list [j + 5]))
					prev_char = NON_JOINER;
				else prev_char = JOINER;
				return (char_list [j + 2]);
			}
			else if ((!NEXT_CHAR_IS_NON_JOINER) && (prev_char == JOINER)) {
				if (char_list [j + 2] == char_list [j + 4])
					prev_char = NON_JOINER;
				else prev_char = JOINER;
				return (char_list [j + 3]);
			}
			else if (NEXT_CHAR_IS_NON_JOINER && (prev_char == JOINER)) {
				prev_char = NON_JOINER;
				return (char_list [j + 4]);
			}
			else if (NEXT_CHAR_IS_NON_JOINER && (prev_char == NON_JOINER)) {
				prev_char = NON_JOINER;
				return (char_list [j + 5]);
			}
		}
	}
}

/*
 The Process function:
 Opens, writes regular characters in destination file and sends unicode
 characters to Convert function. After processing, closes files used.
*/ 

char LineDirector (char chr)
{
	if (chr >= 0 && chr <= '~') {
		line_dir = LTR; return ('>');
	}
	else {
		line_dir = RTL; return ('<');
	}
}

void Process (char *ArgumentVector1, char *ArgumentVector2)
{
	char chr1;
	FILE *InFile = fopen (ArgumentVector1, "r");
	FILE *OutFile = fopen (ArgumentVector2, "w");
	
	if (InFile == NULL) {
		PrintUsage ();
		exit (EXIT_FAILURE);
	}

	fputs ("<·Ú“¨ôóóùó¤Ÿõöó¤Ÿþô\n<", OutFile);	
        if ((chr1 = getc (InFile)) == 'ï')
                fgets ("»¿", 3, InFile); /* Erases BOM */

	while ((chr1 = getc (InFile)) != EOF)
		if (chr1 == '\n') {
			char chr2 = getc (InFile);
			fprintf (OutFile, "%c%c", chr1, LineDirector (chr2)); 
			ungetc (chr2, InFile);
			prev_char = NON_JOINER;
		}
		
		else if (chr1 == REDIRECTOR_CHAR) {
			char chr2;
			if ((chr2 = getc (InFile)) >= ' ' && chr2 <= '~') {
				if (line_dir == RTL)
					line_dir = LTR;
				else {
					line_dir = line_dir;
					putc (chr1, OutFile);
				}
				putc (chr2, OutFile);
			}
			else {
				if (line_dir == RTL) {
					line_dir = RTL;
					putc (GetSymbol (chr1), OutFile);
				}
				else line_dir = RTL;
				ungetc (chr2, InFile);
			}
		}

		else if ((chr1 > 0 && chr1 < 10) 
		|| (chr1 > 10 && chr1 < ' ') || (chr1 >= '0' && chr1 <= '9') 
		|| (chr1 >= 'A' && chr1 <= 'Z')	|| (chr1 >= 'a' && chr1 <= 'z')) {
			putc (chr1, OutFile);
			prev_char = NON_JOINER;		
		}
		
		else if (chr1 >= ' ' && chr1 <= '~') {
			putc (GetSymbol (chr1), OutFile);
			prev_char = NON_JOINER;
		}		
		else {
                        char chr3, chr4;
                        char result;
                        result = Convert (chr1, getc (InFile), 
                                (chr3 = getc (InFile)), 
                                (chr4 = getc (InFile)));

                        if (result == '' || result == '‘')
                                prev_char = NON_JOINER;

                        putc (result, OutFile);
			line_dir = RTL;
                        if (chr3 != 'â' && chr4 != '€') {
                                ungetc (chr4, InFile); ungetc (chr3, InFile);
			}
			else getc (InFile);
		}
			
	fclose (InFile);
	fclose (OutFile);
}

/*
 The main function:
 verifies the input stream objects and invokes needed other functions. 
*/

int main (int argc, char *argv [])
{
	if (InputFilesAreReady (argc)) {
		Process (argv [1], argv [2]);	
		return (EXIT_SUCCESS);
	}
	else return (EXIT_FAILURE);
}
