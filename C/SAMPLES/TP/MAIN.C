#ifndef lint
static char *sccsid = "@(#)main.c 1.3 1/22/92 16:10:45 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * Adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#include <stdlib.h>
#include "suep.h"

void main(int argc, char *argv[])
{
    setUpEnvProcessor *nextEnv;
    fileMgr *myFile;
    page *myPage;
    char *inputFile;

    somEnvironmentNew();
    SOM_TraceLevel = (argc > 2 ? 1 : 0);
    inputFile = (argc > 1 ? argv[1] : "test.dat");

    nextEnv = setUpEnvProcessorNew();
    myFile = fileMgrNew();
    myPage = pageNew();
    _fmInit(myFile, inputFile);

    _epSetPage(nextEnv, myPage);
    _epSetFileMgr(nextEnv, myFile);
    _suProcessOptions(nextEnv);

    _somFree(nextEnv);
    exit(0);
}
