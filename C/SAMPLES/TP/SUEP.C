#ifndef lint
static char *sccsid = "@(#)suep.c 1.3 1/22/92 16:11:05 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define setUpEnvProcessor_Class_Source
#include "suep.ih"

/* ************************************************************ */
SOM_Scope void SOMLINK suProcessOptions(setUpEnvProcessor * somSelf)
{
    int n = 0;
    fileMgr *myfm;
    page *thisPage;
    TPWord *thisWord;

    setUpEnvProcessorMethodDebug("setUpEnvProcessor", "suProcessOptions");
    thisPage = _epGetPage(somSelf);
    myfm = _epGetFileMgr(somSelf);

    for (;;) {
	thisWord = readToken(myfm);
/*  _print(thisWord, stdout); */
	if (_tpwType(thisWord) == TP_EOF) {
	    _somFree(thisWord);
	    break;
	}
	else if (_tpwType(thisWord) == TP_TOKEN)
	    _epStartUpNewEnvironment(somSelf, thisWord);
	else if (_match(thisWord, "width"))
	    _pgSetWidth(thisPage, _suReadIntWord(somSelf));
	else if (_match(thisWord, "height"))
	    _pgSetHeight(thisPage, _suReadIntWord(somSelf));
	else if (_match(thisWord, "columns"))
	    _pgSetNumberOfColumns(thisPage, _suReadIntWord(somSelf));
	_somFree(thisWord);
    }
    thisPage = _epGetPage(somSelf);
    _pgPrint(thisPage, stdout);
}

/* ************************************************************ */
SOM_Scope int SOMLINK suReadIntWord(setUpEnvProcessor * somSelf)
{
    TPWord *thisWord;
    int returnValue;
    setUpEnvProcessorMethodDebug("setUpEnvProcessor", "suReadIntWord");

    thisWord = readToken(_epGetFileMgr(somSelf));  /* Blank */
    _somFree(thisWord);
    thisWord = readToken(_epGetFileMgr(somSelf));  /* Number */
    returnValue = _wordToInt(thisWord);
    _somFree(thisWord);
    return returnValue;
}
