#ifndef lint
static char *sccsid = "@(#)header.c 1.3 1/22/92 16:09:53 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define header_Class_Source
#include "header.ih"

/* ************************************************************ */
SOM_Scope void SOMLINK epProcessEnvironment(header * somSelf)
{
/* headerData *somThis = headerGetData(somSelf); */
    page *thisPage;
    textLine *thisHd;
    TPWord *thisWord;

    headerMethodDebug("header", "epProcessEnvironment");

    thisPage = _epGetPage(somSelf);
    thisHd = _pgGetHeaderBlock(thisPage);

    for (;;) {
	thisWord = readToken(_epGetFileMgr(somSelf));
	if (_match(thisWord, "[[end_environment]]")) {
	    _somFree(thisWord);
	    return;
	}
	if (_tpwType(thisWord) == TP_LINE_BREAK) {
	    _somFree(thisWord);
	    continue;
	}
	_llAddTail(thisHd, thisWord);
	if (_match(thisWord, "[[page_number]]"))
	    _pgSetPageNumber(thisPage, thisWord);
    }

}
