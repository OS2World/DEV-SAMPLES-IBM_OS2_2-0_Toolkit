#   @(#)dog.csc 1.3 2/3/92 20:39:47 [2/3/92] (c)IBM Corp. 1992

-- Copyright (c) International Business Machines Corporation
--		 1991, 1992

include "dogmeta.sc"
include "animal.sc"

class: Dog,
  local;

metaclass: DogFactory;

parent: Animal;

data:
  char *breed;
  char *color;

methods:

group: SetMethods;

   void setBreed(char *myBreed);
-- Set the Breed of this Dog.

   void setColor(char *myColor);
-- Set the Color of this Dog.

group: GetMethods;

   char *getBreed();
-- Get the breed of this Dog.

   char *getColor();
-- Get the color of this Dog.

group: AnimalOverrides;

   override getGenus;
-- This overrides the animal version.  This returns the genus
-- of a Dog.

   override getSpecies;
-- This overrides the animal version.  This returns the species
-- of a Dog.

   override display;
-- Displays a Dog.  This method displays the color and breed, and then
-- invokes the parent display to display information about the animal.
-- The parent display will invoke talk() to show what the animal says.
-- The version of talk() defined by Animal uses private Animal data
-- to determine how the animal talks.  But talk() is a method that will
-- be redefined by later derivations of Dog, namely, LittleDog and
-- BigDog.  Both of these classes redefine the talk() method.  So
-- when a LittleDog invokes display(), which will be inherited from
-- this version, the following sequence occurs:
--   1. Dog::display() is invoked.
--   2. Dog::display() invokes Animal::display().
--   3. Animal::display() invokes talk() which has been overridden
--	by LittleDog().
--   4. LittleDog::talk() uses a different algorithm for talking
--	than Animal::talk().

group: SystemMethodOverrides;

   override somInit;
-- This method will be invoked when a new dog is created.
-- The reason this is automatically invoked is that Dog
-- is derived from Animal, and Animal uses SOMClassInit
-- as its metaclass.

   override somUninit;
-- This method is invoked when a Dog object is freed.

   override somDumpSelfInt;
-- Invoked when a Dog is dumped.

