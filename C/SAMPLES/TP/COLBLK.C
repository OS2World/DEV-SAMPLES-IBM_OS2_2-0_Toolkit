#ifndef lint
static char *sccsid = "@(#)colblk.c 1.3 1/22/92 16:09:11 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define columnBlock_Class_Source
#include "colblk.ih"
#include "textline.h"

#define SPACE_BETWEEN 3
#define HEADER_SPACE 3
#define FOOTER_SPACE 3

/* ************************************************************ */
SOM_Scope void SOMLINK cbInit(columnBlock * somSelf,
			       int newColumns,
			       int newHeight,
			       int newWidth)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    int n;
    linkedList *newBlock;
    columnBlockMethodDebug("columnBlock", "cbInit");

    _columnWidth = newWidth - ((newColumns - 1) * SPACE_BETWEEN);
    _columnWidth = _columnWidth / newColumns;

    _llSetMax(somSelf, newColumns);
    for (n = 0; n < newColumns; n++) {
	newBlock = linkedListNew();
	_llSetMax(newBlock, newHeight - HEADER_SPACE - FOOTER_SPACE);
	parent_llAddTail(somSelf, (baseType *) newBlock);
    }
    _llHead(somSelf);
}

/* ************************************************************ */
SOM_Scope int SOMLINK cbGetColumnWidth(columnBlock * somSelf)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    columnBlockMethodDebug("columnBlock", "cbGetColumnWidth");
    return _columnWidth;
}

/* ************************************************************ */
SOM_Scope int SOMLINK cbLinesLeft(columnBlock * somSelf)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    linkedList *thisBlock;
    columnBlockMethodDebug("columnBlock", "cbLinesLeft");

    thisBlock = (linkedList *) _llRetrieve(somSelf);
    return (_llLeft(thisBlock) || !_llIsTail(somSelf)) ? 1 : 0;
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llAddTail(columnBlock * somSelf,
				       baseType * newLine)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    linkedList *thisBlock;
    columnBlockMethodDebug("columnBlock", "llAddTail");

    thisBlock = (linkedList *) _llRetrieve(somSelf);
    if (!thisBlock)
	return (baseType *) NULL;
    if (!_llLeft(thisBlock)) {
	if (!(thisBlock = (linkedList *) _llNext(somSelf))) {
	    return (baseType *) NULL;
	}
    }
    return _llAddTail(thisBlock, newLine);
}

/* ************************************************************ */
SOM_Scope void SOMLINK print(columnBlock * somSelf,
			      FILE * output)
{
/* Set up.
   ------- */
    columnBlockData *somThis = columnBlockGetData(somSelf);
    int n, blockLength, blankLines;
    linkedList *thisBlock;
    textLine *thisLine;
    columnBlockMethodDebug("columnBlock", "print");

/* Determine number of lines in typical block.
   ------------------------------------------- */
    thisBlock = (linkedList *) _llHead(somSelf);
    blockLength = _llLength(thisBlock);
    blankLines = _llLeft(thisBlock);

/* For each horizontal line...
   --------------------------- */
    for (n = 0; n < blockLength; n++) {

/*     For each text block...
       ---------------------- */
	thisBlock = (linkedList *) _llHead(somSelf);
	while (thisBlock) {

/*	  Print the column line.
	  ---------------------- */
	    thisLine = (textLine *) _llHead(thisBlock);
	    if (thisLine) {
		_print(thisLine, output);
		_llFreeContents(thisLine);
		_cbPrintBlanks(somSelf, output, _tlCharsLeft(thisLine));
	    }
	    else {
		_cbPrintBlanks(somSelf, output, _cbGetColumnWidth(somSelf));
	    }
	    _llRemoveHead(thisBlock);

/*	  Print space between columns.
	  ---------------------------- */
	    _cbPrintBlanks(somSelf, output, SPACE_BETWEEN);

/*	  Move to next block.
	  ------------------- */
	    thisBlock = (linkedList *) _llNext(somSelf);
	}
	fprintf(output, "\n");
    }
/* Print blank lines.
   ------------------ */
    for (n = 0; n < blankLines; n++) {
	fprintf(output, "\n");
    }

}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(columnBlock * somSelf)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    columnBlockMethodDebug("columnBlock", "somInit");
    parent_somInit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(columnBlock * somSelf)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    columnBlockMethodDebug("columnBlock", "somUninit");
    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(columnBlock * somSelf,
				       int level)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    columnBlockMethodDebug("columnBlock", "somDumpSelfInt");
    parent_somDumpSelfInt(somSelf, level);
}

/* ************************************************************ */
SOM_Scope void SOMLINK cbPrintBlanks(columnBlock * somSelf,
				      FILE * output,
				      int nblanks)
{
    columnBlockData *somThis = columnBlockGetData(somSelf);
    int n;
    columnBlockMethodDebug("columnBlock", "cbPrintBlanks");

    for (n = 0; n < nblanks; n++) {
	putc(' ', output);
    }
}
