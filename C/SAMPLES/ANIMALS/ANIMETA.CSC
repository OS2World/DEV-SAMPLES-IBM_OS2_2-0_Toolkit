#   @(#)animeta.csc 1.3 2/3/92 20:39:58 [2/3/92] (c)IBM Corp. 1992

-- Copyright (c) International Business Machines Corporation
--		 1991, 1992

include <somcls.sc>

class: AnimalFactory,
  local;

-- This is an example of a simple metaclass.
-- This metaclass provides a constructor method for
-- the Animal class.

parent: SOMClass;

methods:

group: Constructors;

   SOMAny * newAnimal(char *sound);
-- Create an instance of an Animal with a specific sound.

