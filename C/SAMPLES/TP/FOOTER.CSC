#   @(#)footer.csc 1.3 1/22/92 16:09:24 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "ep.sc"

class: footer,
  local;

parent: envProcessor;

/*
----------------------------------------------------
  Class: footer

Purpose: This environment processes information needed
	 to set up a page heading.  It recognizes the
	 special environment command [[footer]],
	 which is used to indicate placement for a
	 page footer.  Typical text that this environment
	 would be called upon to process is

	 [[footer]]
	 Juliet's Lament
	 [[end_environment]]

	 which would result in this footer printed on
	 each page:

	 Juliet's Lament
---------------------------------------------------- */


methods:

  override epProcessEnvironment;
  -- See envProcessor definition for more information.

