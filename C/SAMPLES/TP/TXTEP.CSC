#   @(#)txtep.csc 1.3 1/22/92 16:11:53 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "ep.sc"

class: txtEnvProcessor,
  local;

parent: envProcessor;

/*
----------------------------------------------------
  Class: txtEnvProcessor

Purpose: This is the primary definition of a text processing
	 environment.  As written, this creates left-justified
	 text.	Other text processing environements, such
	 as bulletedText are derived from this environment,
	 overriding only those specific areas treated differently.
	 For example, bulletedText is just like this default
	 environment, except that it deals with new paragraphs
	 differently.  Therefore it will override those
	 methods of txtEnvProcessor which specifically deal
	 with new paragraphs.
---------------------------------------------------- */

data:

  TPWord       *thisWord;
  textLine     *thisLine;
  columnBlock  *thisCB;

methods:

  void tpProcessWord();
  -- Default word processor: Add it to the current line, if
  -- space is available, otherwise create a new line.

  void tpProcessBlanks();
  -- Default blank processor: Add to current line, if
  -- space is available, otherwise discard (ie don't
  -- use in a new line).

  void tpProcessLineBreak();
  -- Default line break processor: Treat line breaks as
  -- blanks (ie an input line break does not cause a line
  -- break in the output file).

  void tpProcessFullLine();
  -- Default full line processor: Add full input line to
  -- columnBlock and start a new line.

  void tpProcessFullPage();
  -- Default full page processor: Print the page and start
  -- another.

  void tpProcessNewLine();
  -- Default new line processor: Handles a new output line.
  -- Default is indent line 2 characters.

  void tpProcessNewParagraph();
  -- Default new paragraph processor: Breaks the output line.
  -- Starts a new output line.

  textLine *tpGetLine();
  -- Gets the current line.

  void tpSetLine(textLine *newLine);
  -- Sets the current line.

  override epProcessEnvironment;
  -- See the envProcessor definition for more information.

  override epShutdownEnvironment;
  -- See the envProcessor definition for more information.

  override epInitializeEnvironment;
  -- See the envProcessor definition for more information.

  override epPrepareForNewEnvironment;
  -- See the envProcessor definition for more information.

  override epGetParagraphIndentation;
  -- See the envProcessor definition for more information.

  override epGetLineIndentation;
  -- See the envProcessor definition for more information.

  override epInit1;
  -- See the envProcessor definition for more information.

  override somInit;

  override somUninit;
