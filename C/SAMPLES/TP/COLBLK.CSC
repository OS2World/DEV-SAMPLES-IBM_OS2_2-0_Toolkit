#   @(#)colblk.csc 1.3 1/22/92 16:09:15 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "ll.sc"

class: columnBlock,
  local;

parent: linkedList;

/*
----------------------------------------------------
  Class: columnBlock

Purpose: One of the lower level classes used to store
	 information for a page.  A columnBlock is a
	 special type of linked list, in which each link
	 contains a column of text.  A columnBlock will
	 contain one link for each column of text, as
	 defined in the SetUpEnvironment.  So if the input
	 text contains

	    width 60
	    height 15
	    columns 2

	 the columnBlock will contain two links.
	 Each link in the columnBlock is another linked
	 list of textlines.  Each of these linked lists
	 represents one column of text in the page.
---------------------------------------------------- */


data:

  int columnWidth;

methods:

group: AdditionalMethods;

  void cbInit(int newColumns, int newHeight, int newWidth);
  --   Initialize a new columnBlock.

  int cbGetColumnWidth();
  --  Returns the width of a column (in characters).

  int cbLinesLeft();
  --  Returns TRUE if there is room for at least one more
  --  line in the columnBlock, FALSE otherwise.

group: BaseOverrides;

   override llAddTail;
   -- See the linkedList class definition for more information.

   override print;
   --  See the baseType class definition for more information.

group: SystemMethodOverrides;

   override somInit;
   override somUninit;
   override somDumpSelfInt;

group: PrivateMethods;

   void cbPrintBlanks(FILE *output, int nblanks), private;
   --	Prints blank characters to the output file.

