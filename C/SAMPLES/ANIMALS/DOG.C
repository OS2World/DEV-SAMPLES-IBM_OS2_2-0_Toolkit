#ifndef lint
static char *sccsid = "@(#)dog.c 1.3 2/3/92 20:39:45 [2/3/92] (c)IBM Corp. 1992";
#endif

/*
 * Copyright (c) International Business Machines Corporation
 *		 1991, 1992
 */

#define Dog_Class_Source
#include "dog.ih"
#include <string.h>

SOM_Scope char *SOMLINK getBreed(Dog * somSelf)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "getBreed");

    return _breed;
}

SOM_Scope char *SOMLINK getColor(Dog * somSelf)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "getColor");

    return _color;
}

SOM_Scope void SOMLINK setBreed(Dog * somSelf, char *myBreed)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "setBreed");

    if (_breed)
	(*SOMFree) (_breed);
    _breed = (char *) (*SOMMalloc) (strlen(myBreed) + 1);
    strcpy(_breed, myBreed);
}

SOM_Scope void SOMLINK setColor(Dog * somSelf, char *myColor)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "setColor");

    if (_color)
	(*SOMFree) (_color);
    _color = (char *) (*SOMMalloc) (strlen(myColor) + 1);
    strcpy(_color, myColor);
}

SOM_Scope void SOMLINK somInit(Dog * somSelf)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "somInit");
    parent_somInit(somSelf);

    _color = 0;
    _breed = 0;
}

SOM_Scope void SOMLINK somUninit(Dog * somSelf)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "somUninit");

    if (_color)
	(*SOMFree) (_color);
    if (_breed)
	(*SOMFree) (_breed);
    parent_somUninit(somSelf);
}

SOM_Scope void SOMLINK somDumpSelfInt(Dog * somSelf,
				       int level)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "somDumpSelfInt");
    parent_somDumpSelfInt(somSelf, level);
}

SOM_Scope char *SOMLINK getGenus(Dog * somSelf)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "getGenus");
    return ("Canis");
}

SOM_Scope char *SOMLINK getSpecies(Dog * somSelf)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "getSpecies");
    return ("Familiaris");
}

SOM_Scope void SOMLINK display(Dog * somSelf)
{
    DogData *somThis = DogGetData(somSelf);
    DogMethodDebug("Dog", "display");
    somPrintf("  Breed: %s\n", _getBreed(somSelf));
    somPrintf("  Color: %s\n", _getColor(somSelf));
    parent_display(somSelf);
}
