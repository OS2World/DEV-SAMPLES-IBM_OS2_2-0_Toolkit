#ifndef lint
static char *sccsid = "@(#)ipep.c 1.3 1/22/92 16:10:26 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define indentedParagraphs_Class_Source
#include "ipep.ih"

#define PARAGRAPH_INDENTATION 3
#define LINE_INDENTATION 0


/* ************************************************************ */
SOM_Scope int SOMLINK epGetParagraphIndentation(indentedParagraphs * somSelf)
{
/* indentedParagraphsData *somThis = indentedParagraphsGetData(somSelf); */
     indentedParagraphsMethodDebug("indentedParagraphs",
				    "epGetParagraphIndentation");

    somSelf;
    return PARAGRAPH_INDENTATION;

}

/* ************************************************************ */
SOM_Scope int SOMLINK epGetLineIndentation(indentedParagraphs * somSelf)
{
/* indentedParagraphsData *somThis = indentedParagraphsGetData(somSelf); */
    envProcessor *lastEnv;
    indentedParagraphsMethodDebug("indentedParagraphs",
				  "epGetLineIndentation");
    lastEnv = _epGetPreviousEnv(somSelf);
    if (lastEnv)
	return _epGetLineIndentation(lastEnv) +
	    LINE_INDENTATION;
    else
	return LINE_INDENTATION;

}
