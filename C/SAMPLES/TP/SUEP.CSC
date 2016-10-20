#   @(#)suep.csc 1.3 1/22/92 16:11:09 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "ep.sc"

class: setUpEnvProcessor,
  local;

parent: envProcessor;

/*
----------------------------------------------------
  Class: setUpEnvProcessor

Purpose: This environment processes the setup information
	 which starts the input file.  An example of such
	 information is

	 width 60
	 height 15
	 columns 2

	 The three sub-commands recognized by this environment
	 are width, height, and columns, which determined the
	 width and height (in characters) of an output page,
	 and the number of output print columns.
---------------------------------------------------- */


methods:

  int suReadIntWord();
  -- Used to read an integer word.

  void suProcessOptions();
  -- Used to process set up options.

