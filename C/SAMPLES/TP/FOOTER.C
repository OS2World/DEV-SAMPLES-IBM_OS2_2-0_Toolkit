#ifndef lint
static char *sccsid = "@(#)footer.c 1.3 1/22/92 16:09:39 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define footer_Class_Source
#include "footer.ih"

#include "page.h"
#include "tpword.h"

/* ************************************************************ */
SOM_Scope void SOMLINK epProcessEnvironment(footer * somSelf)
{
/* footerData *somThis = footerGetData(somSelf); */
    page *thisPage;
    textLine *thisFt;
    TPWord *thisWord;

    footerMethodDebug("footer", "epProcessEnvironment");

    thisPage = _epGetPage(somSelf);
    thisFt = _pgGetFooterBlock(thisPage);

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
	_llAddTail(thisFt, thisWord);
	if (_match(thisWord, "[[page_number]]"))
	    _pgSetPageNumber(thisPage, thisWord);
    }
}
