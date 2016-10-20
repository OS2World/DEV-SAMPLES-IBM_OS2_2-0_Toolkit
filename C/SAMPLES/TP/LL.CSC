#   @(#)ll.csc 1.3 1/22/92 16:10:39 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "bt.sc"

class: linkedList,
  local;

parent: baseType;

/*
----------------------------------------------------
  Class: linkedList

Purpose: A generic linked list class for storing
	 heterogenous elements.  Objects of any class
	 derived from baseType can be placed on this
	 list.
---------------------------------------------------- */


passthru: C.h;
#include "bt.h"
#include <stdio.h>
endpassthru;

data:
  int max;
  int nlinks;
  link *currentLink;
  link *headLink;
  link *tailLink;

methods:

group: linkedListMethods;

  baseType *llHead();
  -- Make the head of the list the current link, and
  -- return its contents.

  baseType *llTail();
  -- Make the tail of the list the current link, and
  -- returns its contents.

  int llLength();
  -- Return the number of links is the list.

  void llSetMax(int newMax);
  -- Set the maximum number of links the list can contain.

  int llLeft();
  -- Return the number of links that can still be added to the
  -- list.

  baseType *llNext();
  -- Make the link after current the new current link, and
  -- return its contents.

  baseType *llPrevious();
  -- Make the link before current the new current link, and
  -- return its contents.

  baseType *llRetrieve();
  -- Return the contents of the current link.

  baseType *llReplace(baseType *newElement);
  -- Replace the contents of the current list but this new
  -- element, and return a pointer to the new contents.

  baseType *llPromoteTail();
  -- Move the tail link to the head of the list, and return
  -- its contents.

  baseType *llAddHead(baseType *newElement);
  -- Add a link containing this new Element to the head of the
  -- list, and return a pointer to the new Element.

  baseType *llAddTail(baseType *newElement);
  -- Add a link containing this new Element to the tail of the
  -- list, and return a pointer to the new Element.

  baseType *llRemoveHead();
  -- Delete the link at the head of the list.

  int llIsTail();
  -- Returns TRUE if the current link is the head of the list,
  -- FALSE otherwise.

  void llFreeContents();
  -- Frees the entire list, including the contents of each link.

  void llTrace(FILE *output);
  -- Trace the linkedList, useful for debugging.

group: BaseOverrides;

   override print;
   -- see the baseType defintion for more information.

group: SystemMethodOverrides;

   override somInit;

   override somUninit;

   override somDumpSelfInt;
