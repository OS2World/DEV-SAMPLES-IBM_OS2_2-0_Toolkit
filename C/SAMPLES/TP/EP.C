#ifndef lint
static char *sccsid = "@(#)ep.c 1.3 1/22/92 16:08:42 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

#define envProcessor_Class_Source

#include <stdlib.h>

#include "helper.h"
#include "tpword.h"
#include "page.h"

#include "txtep.h"
#include "header.h"
#include "footer.h"
#include "ipep.h"
#include "blep.h"

#include "ep.ih"

/* ************************************************************ */
SOM_Scope void SOMLINK epInit1(envProcessor * somSelf,
				envProcessor * lastEnv)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epInit1");

    _previousEnv = lastEnv;
    _thisFile = _epGetFileMgr(_previousEnv);
    _thisPage = _epGetPage(_previousEnv);

}

/* ************************************************************ */
SOM_Scope void SOMLINK epProcessEnvironment(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epProcessEnvironment");
    shouldHaveOverridden(somSelf, "epProcessEnvironment");
}

/* ************************************************************ */
SOM_Scope void SOMLINK epStartUpNewEnvironment(envProcessor * somSelf,
						TPWord * envName)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessor *nextEnv;
    envProcessorMethodDebug("envProcessor", "epStartUpNewEnvironment");

    if (_match(envName, "[[standard_text]]")) {
	nextEnv = txtEnvProcessorNew();
	_epInit1(nextEnv, somSelf);
    }
    else if (_match(envName, "[[header]]")) {
	nextEnv = headerNew();
	_epInit1(nextEnv, somSelf);
    }
    else if (_match(envName, "[[footer]]")) {
	nextEnv = footerNew();
	_epInit1(nextEnv, somSelf);
    }
    else if (_match(envName, "[[standard_text]]")) {
	nextEnv = txtEnvProcessorNew();
	_epInit1(nextEnv, somSelf);
    }
    else if (_match(envName, "[[indent_paragraphs]]")) {
	nextEnv = indentedParagraphsNew();
	_epInit1(nextEnv, somSelf);
    }
    else if (_match(envName, "[[bulleted_list]]")) {
	nextEnv = bulletedListNew();
	_epInit1(nextEnv, somSelf);
    }
    else {
	printf("Unknown environment: ");
	_print(envName, stdout);
	exit(2);
    }

    _epPrepareForNewEnvironment(somSelf);
    _epProcessEnvironment(nextEnv);
    _somFree(nextEnv);
}

/* ************************************************************ */
SOM_Scope void SOMLINK epInitializeEnvironment(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epInitializeEnvironment");
}

/* ************************************************************ */
SOM_Scope void SOMLINK epShutdownEnvironment(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epShutdownEnvironment");
}

/* ************************************************************ */
SOM_Scope void SOMLINK epPrepareForNewEnvironment(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epPrepareForNewEnvironment");
}

/* ************************************************************ */
SOM_Scope int SOMLINK epGetParagraphIndentation(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epGetParagraphIndentation");
    return (0);
}

/* ************************************************************ */
SOM_Scope int SOMLINK epGetLineIndentation(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epGetLineIndentation");
    return (0);
}

/* ************************************************************ */
SOM_Scope page *SOMLINK epGetPage(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epGetPage");
    return _thisPage;
}

/* ************************************************************ */
SOM_Scope fileMgr *SOMLINK epGetFileMgr(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epGetFileMgr");
    return _thisFile;
}

/* ************************************************************ */
SOM_Scope envProcessor *SOMLINK epGetPreviousEnv(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epGetPreviousEnv");
    return _previousEnv;
}

/* ************************************************************ */
SOM_Scope char *SOMLINK epGetClassName(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    static char *myClass = "envProcessor";
    envProcessorMethodDebug("envProcessor", "epGetClassName");
    return myClass;
}

/* ************************************************************ */
SOM_Scope void SOMLINK epSetPage(envProcessor * somSelf,
				  page * newPage)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epSetPage");
    _thisPage = newPage;
}

/* ************************************************************ */
SOM_Scope void SOMLINK epSetFileMgr(envProcessor * somSelf,
				     fileMgr * newFileMgr)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "epSetFileMgr");
    _thisFile = newFileMgr;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somInit(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "somInit");

    parent_somInit(somSelf);
    _previousEnv = 0;
    _thisFile = 0;
    _thisPage = 0;
}

/* ************************************************************ */
SOM_Scope void SOMLINK somUninit(envProcessor * somSelf)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "somUninit");

    if (!_previousEnv) {
	_somFree(_thisFile);
	_somFree(_thisPage);
	printf("\n");                  /* Last line feed for document. */
    }
    parent_somUninit(somSelf);
}

/* ************************************************************ */
SOM_Scope void SOMLINK somDumpSelfInt(envProcessor * somSelf,
				       int level)
{
    envProcessorData *somThis = envProcessorGetData(somSelf);
    envProcessorMethodDebug("envProcessor", "somDumpSelfInt");

    parent_somDumpSelfInt(somSelf, level);
}
