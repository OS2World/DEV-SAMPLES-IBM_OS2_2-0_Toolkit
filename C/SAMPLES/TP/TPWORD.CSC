#   @(#)tpword.csc 1.3 1/22/92 16:11:39 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "word.sc"

class: TPWord,
  local;

parent: word;

/*
----------------------------------------------------
  Class: TPWord

Purpose: This is a more specialized class derived from
	 the generic Word class.  This is a word which
	 includes more functionality needed for text
	 processing, namely the concept of type.
	 This class also includes a definition for a
	 function, readToken, which returns a newly
	 read in TPWord object.
---------------------------------------------------- */


passthru: C.h;
  #include "fm.h"

  #define TP_WORD 0
  #define TP_LINE_BREAK 1
  #define TP_PARAGRAPH_BREAK 2
  #define TP_TOKEN 3
  #define TP_BLANK_SPACE 4
  #define TP_EOF 5

  SOMAny *readToken(fileMgr *myFile);
endpassthru;

methods:

  int tpwType();
  -- Returns the type of a TPWord.

