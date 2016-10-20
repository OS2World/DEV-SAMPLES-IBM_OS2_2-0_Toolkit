#ifndef lint
static char *sccsid = "@(#)main.c 1.4 2/3/92 20:40:11 [2/3/92] (c)IBM Corp. 1992";
#endif

/*
 * Copyright (c) International Business Machines Corporation
 *		 1991, 1992
 */

#include "animal.h"
#include "dog.h"
#include "ldog.h"
#include "bdog.h"

void main(int argc)
{
    Animal *myAnimal;
    Dog *myDog;
    LittleDog *myLittleDog;
    BigDog *myBigDog;

    /*
     * Create classes.
     */
    AnimalNewClass(Animal_MajorVersion, Animal_MinorVersion);
    DogNewClass(Dog_MajorVersion, Dog_MinorVersion);
    LittleDogNewClass(LittleDog_MajorVersion, LittleDog_MinorVersion);
    BigDogNewClass(BigDog_MajorVersion, BigDog_MinorVersion);

    SOM_TraceLevel = (argc > 1 ? 1 : 0);

    /*
     * Create objects using constructors
     */
    myAnimal = _newAnimal(_Animal, "Roar!!!");
    myDog = _newDog(_Dog, "Grrr", "Retriever", "Yellow");
    myLittleDog = _newDog(_LittleDog, "unknown noise",
			  "French Poodle", "Black");
    myBigDog = _newDog(_BigDog, "unknown noise",
		       "German Shepherd", "Brown");

    /*
     * Display objects.
     */
    somPrintf("=====================\n");
    somPrintf("myAnimal:\n");
    _display(myAnimal);

    somPrintf("=====================\n");
    somPrintf("myDog:\n");
    _display(myDog);

    somPrintf("=====================\n");
    somPrintf("myLittleDog:\n");
    _display(myLittleDog);

    somPrintf("=====================\n");
    somPrintf("myBigDog:\n");
    _display(myBigDog);

    /*
     * Free objects.
     */
    somPrintf("\n");
    _somFree(myAnimal);
    _somFree(myDog);
    _somFree(myLittleDog);
    _somFree(myBigDog);

    exit(0);
}
