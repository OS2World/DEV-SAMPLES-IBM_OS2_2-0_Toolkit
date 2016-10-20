#   @(#)page.csc 1.3 1/22/92 16:10:55 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include <somobj.sc>

class: page,
  local;

parent: SOMObject;

/*
----------------------------------------------------
  Class: page

Purpose: This is a low level storage class, used to
	 coordinate the different information which
	 will be printed on the current page.
---------------------------------------------------- */


passthru: C.h;
#include "tpword.h"
#include "textline.h"
#include "colblk.h"
endpassthru;

data:

  int height;
  int width;
  int ncolumns;
  int currentCol;
  int pageNumber;

  textLine *header;
  textLine *footer;

  columnBlock *columns;
  TPWord *pageWord;

methods:

group: GeneralMethods;

  void pgPrint(FILE *output);

group: SetMethods;

  void pgSetHeight(int newHeight);
  -- Set the height of a page in characters.

  void pgSetWidth(int newWidth);
  -- Set the width of a page in characters.

  void pgSetNumberOfColumns(int ncolumns);
  -- Set the number of columns in a page.

  void pgSetPageNumber(TPWord *newPageWord);
  -- Tell the page about a special word to be used to
  -- store page numbers.

group: GetMethods;

  columnBlock *pgGetColumnBlock();
  -- Get the columnBlock being used by this page.

  textLine *pgGetHeaderBlock();
  -- Get the textLine representing the page header.

  textLine *pgGetFooterBlock();
  -- Get the textLine representing the page footer.

group: SystemMethodOverrides;

   override somInit;

   override somUninit;

   override somDumpSelfInt;
