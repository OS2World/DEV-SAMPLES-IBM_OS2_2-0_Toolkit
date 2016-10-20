#   @(#)link.csc 1.3 1/22/92 16:10:11 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include <bt.sc>

class: link,
  local;

parent: baseType;

/*
----------------------------------------------------
  Class: link

Purpose: A low-level class used to implement the
	 linkedList class.
---------------------------------------------------- */

passthru: C.h;
#include "bt.h"
endpassthru;

data:

  link *next;
  link *previous;
  baseType *contents;

methods:

group: SetMethods;

  void linkSetNext(link *nextLink);
  -- Set the next pointer on target link to new link.

  void linkSetPrevious(link *nextLink);
  -- Set the previous pointer on target link to new link.

  void linkSetContents(baseType *newContents);
  -- Set the contents pointer on target link to new object.

group: GetMethods;

  link *linkGetNext();
  -- Get the next link after the target link.

  link *linkGetPrevious();
  -- Get the previous link before the target link.

  baseType *linkGetContents();
  -- Get the contents of the target link.

group: ParentOverrides;

  override print;
  -- See the baseType definition for more information.

group: SystemMethodOverrides;

   override somInit;

   override somDumpSelfInt;

