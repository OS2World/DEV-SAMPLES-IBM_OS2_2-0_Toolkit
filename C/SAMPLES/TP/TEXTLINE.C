#ifndef lint
static char *sccsid = "@(#)textline.c 1.3 1/22/92 16:11:00 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define textLine_Class_Source
#include "textline.ih"
#include "helper.h"
#include "tpword.h"

/* ************************************************************ */
SOM_Scope void SOMLINK tlInit(textLine * somSelf,
			       int newSize)
{
    textLineData *somThis = textLineGetData(somSelf);
    textLineMethodDebug("textLine", "tlInit");
    _totalChars = 0;
    _maxSize = newSize;
}

/* ************************************************************ */
SOM_Scope int SOMLINK tlCharsInLine(textLine * somSelf)
{
    textLineData *somThis = textLineGetData(somSelf);
    textLineMethodDebug("textLine", "tlCharsInLine");
    return _totalChars;

}

/* ************************************************************ */
SOM_Scope int SOMLINK tlCharsLeft(textLine * somSelf)
{
    textLineData *somThis = textLineGetData(somSelf);
    textLineMethodDebug("textLine", "tlCharsLeft");
    return _maxSize - _totalChars;
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llAddTail(textLine * somSelf,
				       baseType * newElement)
{
    textLineData *somThis = textLineGetData(somSelf);
    TPWord *myWord = (TPWord *) newElement;
    int newTotal;
    textLineMethodDebug("textLine", "llAddTail");

    newTotal = _totalChars + _getLength(newElement);
    if (newTotal <= _maxSize) {
	_totalChars = newTotal;
	return (parent_llAddTail(somSelf, newElement));
    }
    else
	return newElement;
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llAddHead(textLine * somSelf,
				       baseType * newElement)
{
    textLineData *somThis = textLineGetData(somSelf);
    TPWord *myWord = (TPWord *) newElement;
    int newTotal;
    textLineMethodDebug("textLine", "llAddHead");

    newTotal = _totalChars + _getLength(newElement);
    if (newTotal <= _maxSize) {
	_totalChars = newTotal;
	return (parent_llAddHead(somSelf, newElement));
    }
    else
	return newElement;
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llReplace(textLine * somSelf,
				       baseType * newElement)
{
    textLineData *somThis = textLineGetData(somSelf);
    textLineMethodDebug("textLine", "llReplace");
    shouldHaveOverridden(somSelf, "llReplace");
    newElement;
    return (baseType *) NULL;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(textLine * somSelf)
{
    textLineData *somThis = textLineGetData(somSelf);
    textLineMethodDebug("textLine", "somInit");
    parent_somInit(somSelf);
    _maxSize = 0;
    _totalChars = 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(textLine * somSelf)
{
    textLineData *somThis = textLineGetData(somSelf);
    textLineMethodDebug("textLine", "somUninit");

    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(textLine * somSelf,
				       int level)
{
    textLineData *somThis = textLineGetData(somSelf);
    textLineMethodDebug("textLine", "somDumpSelfInt");

    parent_somDumpSelfInt(somSelf, level);
}
