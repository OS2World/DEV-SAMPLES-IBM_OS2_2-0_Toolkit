#ifndef lint
static char *sccsid = "@(#)word.c 1.3 1/22/92 16:12:04 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define word_Class_Source
#include "word.ih"
#include <stdlib.h>
#include <string.h>

static int nNews = 0;
static int nDeletes = 0;
#define PARRAY_SIZE		1000
static char *parray[PARRAY_SIZE];


/* ************************************************************ */
SOM_Scope word *SOMLINK wordInit1(word * somSelf,
				   char *string)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "wordInit1");

    if (_storage)
	free(_storage);
    _storage = malloc(strlen(string) + 1);
    strcpy(_storage, string);
    _length = strlen(string);
    parray[nNews] = _storage;
    nNews++;
    return somSelf;
}

/* ************************************************************ */
SOM_Scope word *SOMLINK wordInit2(word * somSelf,
				   char newChar,
				   int nChars)
{
    wordData *somThis = wordGetData(somSelf);
    int n;

    wordMethodDebug("word", "wordInit2");

    if (_storage)
	free(_storage);
    _storage = malloc(nChars + 1);
    for (n = 0; n < nChars; n++) {
	_storage[n] = newChar;
    }
    _storage[n] = '\0';
    _length = strlen(_storage);
    parray[nNews] = _storage;
    nNews++;
    return somSelf;
}

/* ************************************************************ */
SOM_Scope int SOMLINK getLength(word * somSelf)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "getLength");
    return _length;
}

/* ************************************************************ */
SOM_Scope int SOMLINK wordToInt(word * somSelf)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "wordToInt");
    return atoi(_storage);
}

/* ************************************************************ */
SOM_Scope int SOMLINK match(word * somSelf,
			     void *target)
{
    wordData *somThis = wordGetData(somSelf);
    int targetLength = strlen(target);
    wordMethodDebug("word", "match");
    return (!strncmp(_storage, target, targetLength));
}

/* ************************************************************ */
SOM_Scope void SOMLINK print(word * somSelf,
			      FILE * outputFile)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "print");

    fprintf(outputFile, "%s", _storage);
    fflush(outputFile);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(word * somSelf)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "somInit");
    parent_somInit(somSelf);
    _storage = 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(word * somSelf)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "somUninit");
    if (_storage)
	free(_storage);
    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(word * somSelf,
				       int level)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "somDumpSelfInt");
    parent_somDumpSelfInt(somSelf, level);
}

void showWordStats()
{
    int n;
    printf("\n");
    printf("   nNews: %d\n", nNews);
    printf("nDeletes: %d\n", nDeletes);
    for (n = 0; n < PARRAY_SIZE; n++) {
	if (parray[n]) {
	    printf("n: %d storage: %s\n", n, parray[n]);
	}
    }
}


/* ************************************************************ */
SOM_Scope void SOMLINK wrdReplace(word * somSelf,
				   char *newWord)
{
    wordData *somThis = wordGetData(somSelf);
    wordMethodDebug("word", "wrdReplace");

    _length = strlen(newWord);
    if (_storage)
	free(_storage);
    _storage = malloc(_length + 1);
    strcpy(_storage, newWord);
}
