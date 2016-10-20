#ifndef lint
static char *sccsid = "@(#)ldog.c 1.3 2/3/92 20:40:07 [2/3/92] (c)IBM Corp. 1992";
#endif

/*
 * Copyright (c) International Business Machines Corporation
 *		 1991, 1992
 */

#define LittleDog_Class_Source
#include "ldog.ih"

SOM_Scope void SOMLINK talk(LittleDog * somSelf)
{
/*  LittleDogData *somThis = LittleDogGetData(somSelf); */
    LittleDogMethodDebug("LittleDog", "talk");
    somPrintf("woof woof\n");
    somPrintf("woof woof\n");
    somSelf;			       /* Avoid unreferenced parameter compiler
					* warning for OS/2 compiler */
}
