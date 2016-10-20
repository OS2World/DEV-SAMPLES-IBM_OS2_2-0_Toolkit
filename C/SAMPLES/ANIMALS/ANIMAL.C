#ifndef lint
static char *sccsid = "@(#)animal.c 1.3 2/3/92 20:39:51 [2/3/92] (c)IBM Corp. 1992";
#endif

/*
 * Copyright (c) International Business Machines Corporation
 *		 1991, 1992
 */

#define Animal_Class_Source
#include "animal.ih"
#include <string.h>

SOM_Scope char *SOMLINK getGenus(Animal * somSelf)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "getGenus");
    return ("Unknown Genus");
}

SOM_Scope char *SOMLINK getSpecies(Animal * somSelf)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "getSpecies");
    return ("Unknown Species");
}

SOM_Scope void SOMLINK setSound(Animal * somSelf,
				 char *mySound)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "setSound");

    if (_sound)
	(*SOMFree) (_sound);
    _sound = (char *) (*SOMMalloc) (strlen(mySound) + 1);
    strcpy(_sound, mySound);
}

SOM_Scope void SOMLINK talk(Animal * somSelf)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "talk");
    somPrintf("%s\n", _sound);
}

SOM_Scope void SOMLINK display(Animal * somSelf)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "display");
    somPrintf("  Genus: %s\n", _getGenus(somSelf));
    somPrintf("Species: %s\n", _getSpecies(somSelf));
    somPrintf("This Animal says\n");
    _talk(somSelf);
}

SOM_Scope void SOMLINK somInit(Animal * somSelf)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "somInit");
    parent_somInit(somSelf);
    _sound = (char *) NULL;
}

SOM_Scope void SOMLINK somUninit(Animal * somSelf)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "somUninit");
    if (_sound)
	(*SOMFree) (_sound);
    parent_somUninit(somSelf);
}

SOM_Scope void SOMLINK somDumpSelfInt(Animal * somSelf,
				       int level)
{
    AnimalData *somThis = AnimalGetData(somSelf);
    AnimalMethodDebug("Animal", "somDumpSelfInt");
    _display(somSelf);
    parent_somDumpSelfInt(somSelf, level);
}
