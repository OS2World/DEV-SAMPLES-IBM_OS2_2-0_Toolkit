#ifndef lint
static char *sccsid = "@(#)page.c 1.3 1/22/92 16:10:49 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define page_Class_Source
#include <stdio.h>
#include "page.ih"

#define MAX_WORDS_IN_HEADER 100
#define MAX_WORDS_IN_FOOTER 100

/* ************************************************************ */
SOM_Scope void SOMLINK pgPrint(page * somSelf,
				FILE * output)
{
    pageData *somThis = pageGetData(somSelf);
    char buffer[10];
    pageMethodDebug("page", "pgPrint");

/* Print header.
   ------------- */
    _pageNumber++;
    if (_pageWord) {
	sprintf(buffer, "%d", _pageNumber);
	_wrdReplace(_pageWord, buffer);
    }
    fprintf(output, "\n\f");
    if (_header)
	_print(_header, output);
    fprintf(output, "\n\n");

/* Print text.
   ----------- */
    if (_columns)
	_print(_columns, output);
    fprintf(output, "\n\n");

/* Print footer.
   ------------- */
    if (_footer)
	_print(_footer, output);

/* Clear out text from somThis column block.
   -------------------------------------- */
    _somFree(_columns);
    _columns = 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK pgSetHeight(page * somSelf,
				    int newHeight)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "pgSetHeight");
    _height = newHeight;
}

/* ************************************************************ */
SOM_Scope void SOMLINK pgSetWidth(page * somSelf,
				   int newWidth)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "pgSetWidth");
    _width = newWidth;

}

/* ************************************************************ */
SOM_Scope void SOMLINK pgSetNumberOfColumns(page * somSelf,
					     int newColumns)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "pgSetNumberOfColumns");
    _ncolumns = newColumns;
}

/* ************************************************************ */
SOM_Scope void SOMLINK pgSetPageNumber(page * somSelf,
					TPWord * newPageWord)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "pgSetPageNumber");
    _pageWord = newPageWord;
}

/* ************************************************************ */
SOM_Scope columnBlock *SOMLINK pgGetColumnBlock(page * somSelf)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "pgGetColumnBlock");

    if (!_columns) {
	_columns = columnBlockNew();
	_cbInit(_columns, _ncolumns, _height, _width);
    }
    return _columns;
}

/* ************************************************************ */
SOM_Scope textLine *SOMLINK pgGetHeaderBlock(page * somSelf)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "pgGetHeaderBlock");

    if (!_header) {
	_header = textLineNew();
	_tlInit(_header, MAX_WORDS_IN_HEADER);
    }
    return _header;
}

/* ************************************************************ */
SOM_Scope textLine *SOMLINK pgGetFooterBlock(page * somSelf)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "pgGetFooterBlock");
    if (!_footer) {
	_footer = textLineNew();
	_tlInit(_footer, MAX_WORDS_IN_FOOTER);
    }
    return _footer;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(page * somSelf)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "somInit");

    parent_somInit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(page * somSelf)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "somUninit");

    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(page * somSelf,
				       int level)
{
    pageData *somThis = pageGetData(somSelf);
    pageMethodDebug("page", "somDumpSelfInt");

    parent_somDumpSelfInt(somSelf, level);
}
