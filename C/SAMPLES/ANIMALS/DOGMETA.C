#ifndef lint
static char *sccsid = "@(#)dogmeta.c 1.3 2/3/92 20:40:05 [2/3/92] (c)IBM Corp. 1992";
#endif

/*
 * Copyright (c) International Business Machines Corporation
 *		 1991, 1992
 */

#define DogFactory_Class_Source
#include "dogmeta.ih"
#include "dog.h"

/*
 *  Create an instance of a Dog with a specific sound, breed, & color.
 */

SOM_Scope SOMAny *SOMLINK newDog(DogFactory * somSelf,
				  char *sound,
				  char *breed,
				  char *color)
{
    /* DogFactoryData *somThis = DogFactoryGetData(somSelf); */
    Dog *newDog;
    DogFactoryMethodDebug("DogFactory", "newDog");

    newDog = _newAnimal(somSelf, sound);
    _setBreed(newDog, breed);
    _setColor(newDog, color);

    return (newDog);

}
