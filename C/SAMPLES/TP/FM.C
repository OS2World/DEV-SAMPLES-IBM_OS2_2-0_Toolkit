#ifndef lint
static char *sccsid = "@(#)fm.c 1.3 1/22/92 16:09:18 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define fileMgr_Class_Source

#define BUFF_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include "fm.ih"

/* ************************************************************ */
SOM_Scope void SOMLINK fmInit(fileMgr * somSelf,
			       char *newFile)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    fileMgrMethodDebug("fileMgr", "fileMgrInit");
    if (!(_funit = fopen(newFile, "r"))) {
	printf("Error: unable to open input file \"%s\".\n", newFile);
	exit(3);
    }
}

/* ************************************************************ */
SOM_Scope int SOMLINK fmGetChar(fileMgr * somSelf)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    int newChar;
    fileMgrMethodDebug("fileMgr", "fmGetChar");

    if (_fmSize(somSelf)) {
	newChar = _buffer[_getSide];
	_getSide = _fmIncr(somSelf, _getSide);
    }
    else {
	newChar = getc(_funit);
    }
    return newChar;
}

/* ************************************************************ */
SOM_Scope int SOMLINK fmPeekChar(fileMgr * somSelf,
				  int offset)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    int newChar;
    char cChar;
    int n;
    fileMgrMethodDebug("fileMgr", "fmPeekChar");

    for (;;) {
	n = _fmSize(somSelf);
	if (n > offset)
	    break;
	newChar = getc(_funit);
	cChar = (char) newChar;
	_buffer[_putSide] = newChar;
	_putSide = _fmIncr(somSelf, _putSide);
    }
    offset = _fmAdd(somSelf, _getSide, offset);
    newChar = _buffer[offset];
    return newChar;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(fileMgr * somSelf)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    fileMgrMethodDebug("fileMgr", "somInit");
    parent_somInit(somSelf);

    _funit = 0;
    _putSide = 0;
    _getSide = 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(fileMgr * somSelf)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    fileMgrMethodDebug("fileMgr", "somUninit");

    if (_funit)
	fclose(_funit);

    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(fileMgr * somSelf,
				       int level)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    fileMgrMethodDebug("fileMgr", "somDumpSelfInt");
    parent_somDumpSelfInt(somSelf, level);
}

/* ************************************************************ */
SOM_Scope int SOMLINK fmSize(fileMgr * somSelf)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    int result;
    fileMgrMethodDebug("fileMgr", "size");

    if (_getSide == _putSide)
	result = 0;
    else if (_getSide < _putSide)
	result = _putSide - _getSide;
    else
	result = (BUFF_SIZE - _getSide - 1) + (_putSide + 1);
    return result;
}

/* ************************************************************ */
SOM_Scope int SOMLINK fmIncr(fileMgr * somSelf,
			      int oldNum)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    fileMgrMethodDebug("fileMgr", "incr");

    if (oldNum == (BUFF_SIZE - 1))
	return 0;
    else
	return (oldNum + 1);
}

/* ************************************************************ */
SOM_Scope int SOMLINK fmAdd(fileMgr * somSelf,
			     int oldNum,
			     int addNum)
{
    fileMgrData *somThis = fileMgrGetData(somSelf);
    fileMgrMethodDebug("fileMgr", "add");
    return ((oldNum + addNum) % BUFF_SIZE);
}
