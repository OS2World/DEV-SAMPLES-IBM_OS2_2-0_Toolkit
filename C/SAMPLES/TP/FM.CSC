#   @(#)fm.csc 1.3 1/22/92 16:09:34 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include <somobj.sc>

class: fileMgr,
  local;

parent: SOMObject;

/*
----------------------------------------------------
  Class: fileMgr

Purpose: This is a class interface to the file system.
	 It is simplified in only providing read functionality.
	 It supports one major concept in addition to standard
	 file functions, and that is the method fmPeekChar().
	 This method allows the client to "peek-ahead" into
	 the file, looking at characters without changing
	 the result of fmGetChar().
---------------------------------------------------- */

data:

  FILE *funit;
  int buffer[BUFF_SIZE];
  int putSide;
  int getSide;

methods:

group: fmMethods;

   void fmInit(char *newFile);
   -- Initialize and open a new file.

   int fmGetChar();
   -- Get the next character in the file.

   int fmPeekChar(int offset);
   -- Peek ahead in the file.

group: internalMethods;

   int fmSize(), private;
   int fmIncr(int oldNum), private;
   int fmAdd(int oldNum, int addNum), private;

group: SystemMethodOverrides;

   override somInit;

   override somUninit;

   override somDumpSelfInt;
