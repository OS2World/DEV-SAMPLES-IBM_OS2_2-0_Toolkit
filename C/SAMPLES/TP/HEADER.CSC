#   @(#)header.csc 1.3 1/22/92 16:09:44 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "ep.sc"

class: header,
  local;

parent: envProcessor;

/*
----------------------------------------------------
  Class: header

Purpose: This environment processes information needed
	 to set up a page heading.  It recognizes the
	 special environment command [[header]],
	 which is used to indicate placement for a
	 page header.  Typical text that this environment
	 would be called upon to process is

	 [[header]]
	 Romeo and Juliet		   Page: [[page_number]]
	 [[end_environment]]

	 which would result in this header printed on
	 each page:

	 Romeo and Juliet		   Page: 1
---------------------------------------------------- */


methods:

  override epProcessEnvironment;
  -- See envProcessor definition for more information.

