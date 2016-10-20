#   @(#)dogmeta.csc 1.3 2/3/92 20:40:04 [2/3/92] (c)IBM Corp. 1992

-- Copyright (c) International Business Machines Corporation
--		 1991, 1992

include <animeta.sc>

class: DogFactory,
  local;

-- This is an example of a simple metaclass.
-- This metaclass provides a constructor method for
-- the Dog class.

parent: AnimalFactory;

methods:

group: Constructors;

   SOMAny * newDog(char *sound, char *breed, char *color);
-- Create an instance of a Dog with a specific sound, breed, & color.

