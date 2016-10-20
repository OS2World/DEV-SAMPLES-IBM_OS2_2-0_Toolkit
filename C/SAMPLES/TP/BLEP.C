#ifndef lint
static char *sccsid = "@(#)blep.c 1.3 1/22/92 16:08:17 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define bulletedList_Class_Source
#include "blep.ih"
#include "tpword.h"

#define PARAGRAPH_INDENTATION 0
#define LINE_INDENTATION 2
#define BULLET " - "

/* ************************************************************ */
SOM_Scope int SOMLINK epGetParagraphIndentation(bulletedList * somSelf)
{
    /* bulletedListData *somThis = bulletedListGetData(somSelf); */
    bulletedListMethodDebug("bulletedList", "epGetParagraphIndentation");

    somSelf;			       /* Avoid unreferenced parameter compiler
					* warning for OS/2 compiler */
    return PARAGRAPH_INDENTATION;

}

/* ************************************************************ */
SOM_Scope int SOMLINK epGetLineIndentation(bulletedList * somSelf)
{
    /* bulletedListData *somThis = bulletedListGetData(somSelf); */
    envProcessor *lastEnv = _epGetPreviousEnv(somSelf);
    bulletedListMethodDebug("bulletedList", "epGetLineIndentation");

    if (lastEnv)
	return _epGetLineIndentation(lastEnv) + LINE_INDENTATION;
    else
	return LINE_INDENTATION;
}

/* ************************************************************ */
SOM_Scope void SOMLINK epInitializeEnvironment(bulletedList * somSelf)
{
    /* bulletedListData *somThis = bulletedListGetData(somSelf); */
    textLine *thisLine;
    TPWord *bullet;
    bulletedListMethodDebug("bulletedList", "epInitializeEnvironment");

    parent_epInitializeEnvironment(somSelf);

    bullet = TPWordNew();
    _wordInit1(bullet, BULLET);
    thisLine = _tpGetLine(somSelf);
    _llAddTail(thisLine, (baseType *) bullet);
}

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessNewParagraph(bulletedList * somSelf)
{
/* bulletedListData *somThis = bulletedListGetData(somSelf); */
    textLine *thisLine;
    TPWord *bullet;
    bulletedListMethodDebug("bulletedList", "tpProcessNewParagraph");

    parent_tpProcessNewParagraph(somSelf);

    bullet = TPWordNew();
    _wordInit1(bullet, BULLET);
    thisLine = _tpGetLine(somSelf);
    _llAddTail(thisLine, (baseType *) bullet);
}
