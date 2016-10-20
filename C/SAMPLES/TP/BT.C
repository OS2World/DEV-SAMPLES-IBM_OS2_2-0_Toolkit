#ifndef lint
static char *sccsid = "@(#)bt.c 1.3 1/22/92 16:07:58 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define baseType_Class_Source
#include "bt.ih"
#include "helper.h"

SOM_Scope int SOMLINK match(baseType * somSelf,
			     void *target)
{
    /* baseTypeData *somThis = baseTypeGetData(somSelf); */
    baseTypeMethodDebug("baseType", "match");
    shouldHaveOverridden(somSelf, "match");
    target;			       /* Avoid unreferenced parameter compiler
					* warning for OS/2 compiler */
    return 0;
}

SOM_Scope void SOMLINK print(baseType * somSelf,
			      FILE * outputFile)
{
    /* baseTypeData *somThis = baseTypeGetData(somSelf); */
    baseTypeMethodDebug("baseType", "print");
    shouldHaveOverridden(somSelf, "print");
    outputFile; 		       /* Avoid unreferenced parameter compiler
					* warning for OS/2 compiler */
}
