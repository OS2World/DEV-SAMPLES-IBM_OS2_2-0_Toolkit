#ifndef lint
static char *sccsid = "@(#)tpword.c 1.3 1/22/92 16:11:32 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define TPWord_Class_Source
#include <string.h>
#include "tpword.ih"

/* ************************************************************ */
SOM_Scope int SOMLINK tpwType(TPWord * somSelf)
{
/* TPWordData *somThis = TPWordGetData(somSelf); */
     TPWordMethodDebug("TPWord", "tpwType");

    if (_match(somSelf, "[[EOF]]"))
	return TP_EOF;
    else if (_match(somSelf, "[["))
	return TP_TOKEN;
    else if (_match(somSelf, "\n\n"))
	return TP_PARAGRAPH_BREAK;
    else if (_match(somSelf, "\n"))
	return TP_LINE_BREAK;
    else if (_match(somSelf, " "))
	return TP_BLANK_SPACE;
    else
	return TP_WORD;
}

TPWord *readToken(fileMgr * myFile)
{
    char buffer[100];
    int nxtChr;
    int n = 0;
    int brackets;
    TPWord *newWord;
    nxtChr = _fmPeekChar(myFile, 0);

/* Check for string of blanks.
   --------------------------- */
    if (nxtChr == ' ') {
	while (_fmPeekChar(myFile, 0) == ' ') {
	    buffer[n++] = (char) _fmGetChar(myFile);
	}
    }
/* Check for string of newlines.
   ----------------------------- */
    else if (nxtChr == '\n') {
	while (_fmPeekChar(myFile, 0) == '\n') {
	    buffer[n++] = (char) _fmGetChar(myFile);
	}
    }
/* Check for EOF.
   -------------- */
    else if (nxtChr == EOF) {
	strcpy(buffer, "[[EOF]]");
	n = strlen(buffer);
    }
/* Check for special token.
   ------------------------ */
    else if ((nxtChr == '[') && (_fmPeekChar(myFile, 1) == '[')) {
	brackets = 0;
	while (brackets < 2) {
	    nxtChr = _fmGetChar(myFile);
	    buffer[n++] = (char) nxtChr;
	    if (nxtChr == ']')
		brackets++;
	    else
		brackets = 0;
	}
    }
/* Otherwise, handle as word.
   -------------------------- */
    else {
	for (;;) {
	    nxtChr = _fmPeekChar(myFile, 0);
	    if (nxtChr == ' ')
		break;
	    if (nxtChr == '\n')
		break;
	    if (nxtChr == EOF)
		break;
	    if (nxtChr == '[')
		break;
	    buffer[n++] = (char) _fmGetChar(myFile);
	}
    }
/* Return converted buffer.
   ------------------------ */
    buffer[n] = '\0';
    newWord = TPWordNew();
    _wordInit1(newWord, buffer);
    return newWord;
}
