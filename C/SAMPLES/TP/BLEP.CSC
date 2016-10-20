#   @(#)blep.csc 1.3 1/22/92 16:08:28 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "txtep.sc"

class: bulletedList,
  local;

parent: txtEnvProcessor;

/*
----------------------------------------------------
  Class: bulletedList
Purpose: This environment treats new paragraphs as
	 items in a bulleted list.  It is invoked
	 with the [[bulleted_list]] text command.
	 For example, this text:

	 [[bulleted_list]]
	 one

	 two

	 three
	 [[end_environment]]

	 creates this output:

	   -one
	   -two
	   -three
---------------------------------------------------- */


methods:

  override epGetParagraphIndentation;
  override epGetLineIndentation;
  override epInitializeEnvironment;
  override tpProcessNewParagraph;

