#ifndef lint
static char *sccsid = "@(#)bdog.c 1.3 2/3/92 20:40:00 [2/3/92] (c)IBM Corp. 1992";
#endif

/*
 * Copyright (c) International Business Machines Corporation
 *		 1991, 1992
 */

#define BigDog_Class_Source
#include "bdog.ih"

SOM_Scope void SOMLINK talk(BigDog * somSelf)
{
/*  BigDogData *somThis = BigDogGetData(somSelf); */
    BigDogMethodDebug("BigDog", "talk");
    somPrintf("WOOF WOOF\n");
    somPrintf("WOOF WOOF\n");
    somPrintf("WOOF WOOF\n");
    somPrintf("WOOF WOOF\n");
    somPrintf("WOOF WOOF\n");
    somSelf;			       /* Avoid unreferenced parameter compiler
					* warning for OS/2 compiler */
}
