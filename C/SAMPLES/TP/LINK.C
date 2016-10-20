#ifndef lint
static char *sccsid = "@(#)link.c 1.3 1/22/92 16:09:29 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define link_Class_Source
#include "link.ih"

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(link * somSelf)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "somInit");
    parent_somInit(somSelf);

    _next = 0;
    _previous = 0;
    _contents = 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(link * somSelf,
				       int level)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "somDumpSelfInt");
    parent_somDumpSelfInt(somSelf, level);
}

/* ************************************************************ */
SOM_Scope void SOMLINK linkSetNext(link * somSelf,
				    link * nextLink)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "linkSetNext");
    _next = nextLink;
}

/* ************************************************************ */
SOM_Scope void SOMLINK linkSetPrevious(link * somSelf,
					link * nextLink)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "linkSetPrevious");
    _previous = nextLink;
}

/* ************************************************************ */
SOM_Scope void SOMLINK linkSetContents(link * somSelf,
					baseType * newContents)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "linkSetContents");
    _contents = newContents;
}

/* ************************************************************ */
SOM_Scope link *SOMLINK linkGetNext(link * somSelf)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "linkGetNext");
    return (_next);
}

/* ************************************************************ */
SOM_Scope link *SOMLINK linkGetPrevious(link * somSelf)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "linkGetPrevious");
    return (_previous);
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK linkGetContents(link * somSelf)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "linkGetContents");
    return (_contents);
}

/* ************************************************************ */
SOM_Scope void SOMLINK print(link * somSelf,
			      FILE * outputFile)
{
    linkData *somThis = linkGetData(somSelf);
    linkMethodDebug("link", "print");
    fprintf(outputFile, "\n");
    fprintf(outputFile, "    Link\n");
    fprintf(outputFile, "    self: %x \n", somSelf);
    fprintf(outputFile, "    next: %x \n", _next);
    fprintf(outputFile, "previous: %x\n", _previous);
    fprintf(outputFile, "contents: %x\n", _contents);
}
