#ifndef lint
static char *sccsid = "@(#)animeta.c 1.3 2/3/92 20:39:56 [2/3/92] (c)IBM Corp. 1992";
#endif

/*
 * Copyright (c) International Business Machines Corporation
 *		 1991, 1992
 */

#define AnimalFactory_Class_Source
#include "animeta.ih"
#include "animal.h"

/*
 *  Create an instance of an Animal with a specific sound.
 */

SOM_Scope SOMAny *SOMLINK newAnimal(AnimalFactory * somSelf,
				     char *sound)
{
    /* AnimalFactoryData *somThis = AnimalFactoryGetData(somSelf); */
    Animal *newAnimal;
    AnimalFactoryMethodDebug("AnimalFactory", "newAnimal");

    newAnimal = _somNew(somSelf);
    _setSound(newAnimal, sound);
    return (newAnimal);
}
