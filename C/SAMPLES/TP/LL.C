#ifndef lint
static char *sccsid = "@(#)ll.c 1.3 1/22/92 16:10:02 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define linkedList_Class_Source
#include "link.h"
#include "ll.ih"
#define MAX_INT 30000

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llHead(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llHead");

    if (!_nlinks)
	return (baseType *) NULL;
    _currentLink = _headLink;
    return (_linkGetContents(_currentLink));
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llTail(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llTail");

    if (!_nlinks)
	return (baseType *) NULL;
    _currentLink = _tailLink;
    return (_linkGetContents(_currentLink));
}

/* ************************************************************ */
SOM_Scope int SOMLINK llLength(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llLength");
    return _nlinks;
}

/* ************************************************************ */
SOM_Scope void SOMLINK llSetMax(linkedList * somSelf,
				 int newMax)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llSetMax");
    _max = newMax;
}

/* ************************************************************ */
SOM_Scope int SOMLINK llLeft(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llLeft");
    return (_max - _llLength(somSelf));
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llNext(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llNext");

    if (!_nlinks)
	return (baseType *) NULL;
    if (_linkGetNext(_currentLink)) {
	_currentLink = _linkGetNext(_currentLink);
	return (_linkGetContents(_currentLink));
    }
    else {
	return (baseType *) NULL;
    }
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llPrevious(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llPrevious");

    if (!_nlinks)
	return (baseType *) NULL;
    if (_linkGetPrevious(_currentLink)) {
	_currentLink = _linkGetPrevious(_currentLink);
	return (_linkGetContents(_currentLink));
    }
    else {
	return (baseType *) NULL;
    }
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llRetrieve(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llRetrieve");

    if (!_nlinks)
	return (baseType *) NULL;
    return (_linkGetContents(_currentLink));
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llReplace(linkedList * somSelf,
				       baseType * newElement)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llReplace");

    if (!_nlinks)
	return (baseType *) NULL;
    _linkSetContents(_currentLink, newElement);
    return (_linkGetContents(_currentLink));
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llPromoteTail(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    link *oldTail;
    linkedListMethodDebug("linkedList", "llPromoteTail");
    if (!_nlinks)
	return (baseType *) NULL;
    if (_nlinks == 1)
	return (_linkGetContents(_headLink));
    oldTail = _tailLink;
    _tailLink = _linkGetPrevious(_tailLink);
    _linkSetNext(_linkGetPrevious(oldTail), 0);
    _linkSetPrevious(oldTail, 0);
    _linkSetNext(oldTail, _headLink);
    _linkSetPrevious(_headLink, oldTail);
    _headLink = oldTail;
    _currentLink = _headLink;
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llAddHead(linkedList * somSelf,
				       baseType * newElement)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    link *newLink = linkNew();
    linkedListMethodDebug("linkedList", "llAddHead");

    _linkSetContents(newLink, newElement);
    if (!_llLeft(somSelf)) {
	_llHead(somSelf);
	return (_llReplace(somSelf, newElement));
    }
    if (_llHead(somSelf)) {
	_linkSetPrevious(_currentLink, newLink);
    }
    else
	_tailLink = newLink;
    _linkSetNext(newLink, _currentLink);
    _headLink = _currentLink = newLink;
    _nlinks++;
    return (_linkGetContents(_currentLink));
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llAddTail(linkedList * somSelf,
				       baseType * newElement)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    link *newLink = linkNew();
    linkedListMethodDebug("linkedList", "llAddTail");

    _linkSetContents(newLink, newElement);
    if (!_llLeft(somSelf)) {
	_llTail(somSelf);
	return (_llReplace(somSelf, newElement));
    }
    if (_llTail(somSelf)) {
	_linkSetNext(_currentLink, newLink);
    }
    else
	_headLink = newLink;
    _linkSetPrevious(newLink, _currentLink);
    _tailLink = _currentLink = newLink;
    _nlinks++;
    return (_linkGetContents(_currentLink));
}

/* ************************************************************ */
SOM_Scope baseType *SOMLINK llRemoveHead(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    baseType *thisItem;
    linkedListMethodDebug("linkedList", "llRemoveHead");

    if (!_nlinks)
	return (baseType *) NULL;
    thisItem = _llHead(somSelf);
    if (_nlinks == 1) {
	_somFree(_headLink);
	_headLink = _tailLink = _currentLink = 0;
    }
    if (_nlinks > 1) {
	_llNext(somSelf);
	_somFree(_headLink);
	_headLink = _currentLink;
	_linkSetPrevious(_headLink, 0);
    }
    _nlinks--;
    return thisItem;
}

/* ************************************************************ */
SOM_Scope int SOMLINK llIsTail(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llIsTail");
    return (_currentLink == _tailLink);

}

/* ************************************************************ */
SOM_Scope void SOMLINK llFreeContents(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    baseType *thisItem;

    linkedListMethodDebug("linkedList", "llFreeContents");

    while (thisItem = _llRemoveHead(somSelf))
	_somFree(thisItem);
}

/* ************************************************************ */
SOM_Scope void SOMLINK print(linkedList * somSelf,
			      FILE * outputFile)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    baseType *thisItem;

    linkedListMethodDebug("linkedList", "print");
    thisItem = _llHead(somSelf);
    if (thisItem) {
	while (thisItem) {
	    _print(thisItem, outputFile);
	    thisItem = _llNext(somSelf);
	}
    }
}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "somInit");
    parent_somInit(somSelf);

    _currentLink = 0;
    _headLink = 0;
    _tailLink = 0;
    _nlinks = 0;
    _max = MAX_INT;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(linkedList * somSelf)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "somUninit");

    while (_llRemoveHead(somSelf))
	;
    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(linkedList * somSelf,
				       int level)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "somDumpSelfInt");
    parent_somDumpSelfInt(somSelf, level);
}

/* ************************************************************ */
SOM_Scope void SOMLINK llTrace(linkedList * somSelf, FILE * output)
{
    linkedListData *somThis = linkedListGetData(somSelf);
    linkedListMethodDebug("linkedList", "llTrace");
    fprintf(output, "\n");
    fprintf(output, " Linked List\n");
    fprintf(output, "        max: %d\n", _max);
    fprintf(output, "     nlinks: %d\n", _nlinks);
    fprintf(output, "currentLink: %x\n", _currentLink);
    fprintf(output, "   headLink: %x\n", _headLink);
    fprintf(output, "   tailLink: %x\n", _tailLink);

    _print(_headLink, output);
    _print(_currentLink, output);
    _print(_tailLink, output);
}
