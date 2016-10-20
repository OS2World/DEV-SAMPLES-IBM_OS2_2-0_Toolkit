#   @(#)animal.csc 1.3 2/3/92 20:39:53 [2/3/92] (c)IBM Corp. 1992

-- Copyright (c) International Business Machines Corporation
--		 1991, 1992

include "animeta.sc"
include <somobj.sc>

class: Animal,
  local;

metaclass: AnimalFactory;

parent: SOMObject;

data:
  char *sound;
  int  nsound;

methods:

group: SetMethods;

   void setSound(char *mySound);
-- Tell animal what kind of a sound it makes.

group: GetMethods;

   char *getGenus();
-- Returns the genus of animal.
-- This method should be overridden by derived classes.
-- The default version here just gives "unknown' as the genus.

   char *getSpecies();
-- Returns the species of animal.
-- This method should be overridden by derived classes.
-- The default version here just gives "unknown' as the species.

group: DisplayMethods;

   void talk();
-- Ask the animal to talk.  Normally this just prints out the
-- string set by setSound(), but it can be overriden to do something
-- else.

   void display();
-- Displays an animal.	Derived classes should override this to
-- display new derived information, and then call their parent
-- version. Note: this method makes use of talk() to describe what
-- the animal says.

group: SystemMethodOverrides;

   override somInit;
-- This method will be invoked when a new animal is created.

   override somUninit;
-- This is invoked when an animal object is freed.

   override somDumpSelfInt;
-- Invoked when an animal is dumped.
