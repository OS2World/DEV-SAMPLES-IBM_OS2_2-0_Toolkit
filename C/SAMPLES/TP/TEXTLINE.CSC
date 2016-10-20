#   @(#)textline.csc 1.3 1/22/92 16:11:18 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "ll.sc"

class: textLine,
  local;

parent: linkedList;

/*
----------------------------------------------------
  Class: textLine

Purpose: This is a low-level storage class.  It
	 represents a specialized version of a linkedList.
	 A textLine is a linkedList which is only used for
	 storing TPWords.  It has additional methods (over
	 and above the linkedList methods) which deal with
	 the number of characters in a line.  The linkedList
	 method llAddTail is overridden to allow character
	 counts to be updated as TPWords are inserted in
	 the list.  The linkedList method llReplace is
	 not supported in this derived class.
---------------------------------------------------- */


data:

  int maxSize;
  int totalChars;

methods:

group: Group1;

group: newMethods;

   void tlInit(int newSize);
   -- Initialize a new text line with the number of characters
   -- it can contain.

   int tlCharsInLine();
   -- Returns the number of characters in a textLine.

   int tlCharsLeft();
   -- Returns the number of characters that can still be placed
   -- in the textLine.

group: OverriddenLinkedListMethods;

   override llAddTail;
   -- See the linkedList definition for more information.

   override llAddHead;
   -- See the linkedList definition for more information.

group: UnsupportedLinkedListMethods;

   override llReplace;
   -- Cannot be called for textLines.

group: SystemMethodOverrides;

   override somInit;

   override somUninit;

   override somDumpSelfInt;
