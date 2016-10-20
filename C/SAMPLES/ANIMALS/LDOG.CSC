#   @(#)ldog.csc 1.3 2/3/92 20:40:09 [2/3/92] (c)IBM Corp. 1992

-- Copyright (c) International Business Machines Corporation
--		 1991, 1992

include "dog.sc"

class: LittleDog,
  local;

parent: Dog;

methods:

group: parentOverrides;

   override talk;
-- Overrides the Dog::talk().  See display() in Dog for a discussion
-- of how this changes the display() of a LittleDog.
