#ifndef lint
static char *sccsid = "@(#)txtep.c 1.3 1/22/92 16:11:45 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define txtEnvProcessor_Class_Source
#include "txtep.ih"
#include "tpword.h"
#include "textline.h"
#include "page.h"
#include "colblk.h"

#define PARAGRAPH_INDENTATION 0
#define LINE_INDENTATION 0

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessWord(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    textLine *thisLine = _tpGetLine(somSelf);
    page *thisPage;
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpProcessWord");

    thisPage = _epGetPage(somSelf);
    _thisCB = _pgGetColumnBlock(thisPage);
    if (!_cbLinesLeft(_thisCB))
	_tpProcessFullPage(somSelf);
    if (_getLength(_thisWord) > _tlCharsLeft(thisLine)) {
	_tpProcessFullLine(somSelf);
	_tpProcessNewLine(somSelf);
	thisLine = _tpGetLine(somSelf);
    }
    _llAddTail(thisLine, (baseType *) _thisWord);
}

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessBlanks(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    textLine *thisLine = _tpGetLine(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpProcessBlanks");

    if (!_tlCharsLeft(thisLine)) {
	_somFree(_thisWord);
	return;
    }
    _tpProcessWord(somSelf);

}

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessLineBreak(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    textLine *thisLine = _tpGetLine(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpProcessLineBreak");

    _somFree(_thisWord);
    if (!_tlCharsInLine(thisLine))
	return;
    if (!_tlCharsLeft(thisLine))
	return;
    _thisWord = TPWordNew();
    _wordInit1(_thisWord, " ");
    _tpProcessWord(somSelf);

}

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessFullLine(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    textLine *thisLine = _tpGetLine(somSelf);
    page *thisPage;
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpProcessFullLine");

    thisPage = _epGetPage(somSelf);
    _thisCB = _pgGetColumnBlock(thisPage);
    _llAddTail(_thisCB, (baseType *) thisLine);

    thisLine = textLineNew();
    _tlInit(thisLine, _cbGetColumnWidth(_thisCB));
    _tpSetLine(somSelf, thisLine);
}

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessFullPage(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    page *thisPage;
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpProcessFullPage");

    thisPage = _epGetPage(somSelf);
    _pgPrint(thisPage, stdout);
    _thisCB = _pgGetColumnBlock(thisPage);
}

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessNewLine(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    int charsToIndent;
    TPWord *blanks;
    textLine *thisLine;
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpProcessNewLine");

    charsToIndent = _epGetLineIndentation(somSelf);
    if (charsToIndent) {
	thisLine = _tpGetLine(somSelf);
	blanks = TPWordNew();
	_wordInit2(blanks, ' ', charsToIndent);
	_llAddTail(thisLine, (baseType *) blanks);
    }
}

/* ************************************************************ */
SOM_Scope void SOMLINK tpProcessNewParagraph(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    int charsToIndent;
    TPWord *blanks;
    textLine *thisLine;
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpProcessNewParagraph");

    charsToIndent = _epGetParagraphIndentation(somSelf);
    _tpProcessFullLine(somSelf);
    _tpProcessNewLine(somSelf);
    thisLine = _tpGetLine(somSelf);

    if (charsToIndent) {
	blanks = TPWordNew();
	_wordInit2(blanks, ' ', charsToIndent);
	_llAddTail(thisLine, (baseType *) blanks);
    }
    _somFree(_thisWord);
}

/* ************************************************************ */
SOM_Scope textLine *SOMLINK tpGetLine(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpGetLine");

    if (!_thisLine) {
	_thisLine = textLineNew();
	_tlInit(_thisLine, _cbGetColumnWidth(_thisCB));
    }
    return _thisLine;
}

/* ************************************************************ */
SOM_Scope void SOMLINK tpSetLine(txtEnvProcessor * somSelf,
				  textLine * newLine)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor", "tpSetLine");
    _thisLine = newLine;
}

/* ************************************************************ */
SOM_Scope void SOMLINK epProcessEnvironment(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);

/* Declare local variables.
   ------------------------ */
    page *thisPage;
    fileMgr *thisFile;
    int n = 0;
/* char *myClass = getClassName(); */
    thisPage = _epGetPage(somSelf);
    thisFile = _epGetFileMgr(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor", "epProcessEnvironment");

/* Prepare for looping.
   -------------------- */
    _epInitializeEnvironment(somSelf);

/* Loop until end of file.
   ----------------------- */
    while (_thisWord = readToken(thisFile)) {
/*    _print(_thisWord, stdout); */
	if (_tpwType(_thisWord) == TP_EOF) {
	    _somFree(_thisWord);
	    break;
	}
	if (_match(_thisWord, "[[end_environment]]")) {
	    _epShutdownEnvironment(somSelf);
	    break;
	}
	switch (_tpwType(_thisWord)) {
	    case TP_LINE_BREAK:
		_tpProcessLineBreak(somSelf);
		continue;
	    case TP_WORD:
		_tpProcessWord(somSelf);
		continue;
	    case TP_PARAGRAPH_BREAK:
		_tpProcessNewParagraph(somSelf);
		continue;
	    case TP_BLANK_SPACE:
		_tpProcessBlanks(somSelf);
		continue;
	    case TP_TOKEN:
		_epStartUpNewEnvironment(somSelf, _thisWord);
		_somFree(_thisWord);
		continue;
	}
    }
    _tpProcessFullLine(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK epShutdownEnvironment(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    envProcessor *lastEnv;
    txtEnvProcessorMethodDebug("txtEnvProcessor", "epShutdownEnvironment");

    lastEnv = _epGetPreviousEnv(somSelf);
    if (lastEnv)
	_epInitializeEnvironment(lastEnv);
}

/* ************************************************************ */
SOM_Scope void SOMLINK epInitializeEnvironment(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    int charsToIndent;
    TPWord *blanks;
    TPWord *lineFeed;
    textLine *thisLine;
    fileMgr *thisFile;

    txtEnvProcessorMethodDebug("txtEnvProcessor",
			       "epInitializeEnvironment");

    thisFile = _epGetFileMgr(somSelf);
    lineFeed = readToken(thisFile);
    _somFree(lineFeed);
    charsToIndent = _epGetParagraphIndentation(somSelf);
    _tpProcessNewLine(somSelf);

    thisLine = _tpGetLine(somSelf);
    if (charsToIndent) {
	blanks = TPWordNew();
	_wordInit2(blanks, ' ', charsToIndent);
	_llAddTail(thisLine, (baseType *) blanks);
    }
}

/* ************************************************************ */
SOM_Scope void SOMLINK epPrepareForNewEnvironment(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor",
			       "epPrepareForNewEnvironment");
    _tpProcessFullLine(somSelf);
}

/* ************************************************************ */
SOM_Scope int SOMLINK epGetParagraphIndentation(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    envProcessor *previousEnv;
    txtEnvProcessorMethodDebug("txtEnvProcessor",
			       "epGetParagraphIndentation");

    previousEnv = _epGetPreviousEnv(somSelf);
    if (previousEnv)
	return _epGetParagraphIndentation(previousEnv) +
	    PARAGRAPH_INDENTATION;
    else
	return 0;
}

/* ************************************************************ */
SOM_Scope int SOMLINK epGetLineIndentation(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    envProcessor *previousEnv;
    txtEnvProcessorMethodDebug("txtEnvProcessor", "epGetLineIndentation");

    previousEnv = _epGetPreviousEnv(somSelf);
    if (previousEnv)
	return _epGetLineIndentation(previousEnv) +
	    LINE_INDENTATION;
    else
	return 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor", "somUninit");
    if (_thisWord)
	_somFree(_thisWord);
    if (_thisLine)
	_somFree(_thisLine);
    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(txtEnvProcessor * somSelf)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    txtEnvProcessorMethodDebug("txtEnvProcessor", "somInit");
    parent_somInit(somSelf);

    _thisWord = 0;
    _thisLine = 0;
    _thisCB = 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK epInit1(txtEnvProcessor * somSelf,
				envProcessor * lastEnv)
{
    txtEnvProcessorData *somThis = txtEnvProcessorGetData(somSelf);
    page *thisPage;

    txtEnvProcessorMethodDebug("txtEnvProcessor", "epInit1");
    parent_epInit1(somSelf, lastEnv);

    thisPage = _epGetPage(somSelf);
    _thisCB = _pgGetColumnBlock(thisPage);
}
