#   @(#)ipep.csc 1.3 1/22/92 16:10:30 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "txtep.sc"

class: indentedParagraphs,
  local;

parent: txtEnvProcessor;

/*
----------------------------------------------------
  Class: indentedParagrpahs

Purpose: This environment treats new paragraphs as
	 new paragraphs which are to be indented.  It
	 is invoked with the [[indent_paragraphs]].
	 For example, this text:

	 [[indent_paragraphs]]
	 Tis but thy name that is my enemy.
	 Thou art thyself, though not a Montague.
	 What's Montague?  It is

	 results in this output:

	    Tis but thy name that is
	 my enemy. Thou art thyself,
	 though not a Montague.
	 What's Montague?  It is
---------------------------------------------------- */


methods:

  override epGetParagraphIndentation;
  -- See envProcessor defintion for more information.

  override epGetLineIndentation;
  -- See envProcessor defintion for more information.

