#   @(#)bt.csc 1.3 1/22/92 16:08:08 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include <somobj.sc>

class: baseType,
  local;

parent: SOMObject;

/*
----------------------------------------------------
  Class: baseType

Purpose: This class defines the general functionality
	 that must be supported by any class, objects of which
	 are going to be placed on the linkedList class.
	 This class should not be instantiated directly.
	 It should be used only for further class derivations.
---------------------------------------------------- */


passthru: C.h;
#include <stdio.h>
endpassthru;

methods:

group: Group1;

  int match(void *target);
  --  Returns TRUE if the target object matches target,
  --  FALSE otherwise.

  void print(FILE *outputFile);
  --   Prints the target object in some reasonable format.

