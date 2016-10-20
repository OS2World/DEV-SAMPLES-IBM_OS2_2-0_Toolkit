#   @(#)word.csc 1.3 1/22/92 16:12:12 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include "bt.sc"

class: word,
  local;

parent: baseType;

/*
----------------------------------------------------
  Class: word

Purpose: This is a generalized concept of a word,
	 meaning a string of characters.
---------------------------------------------------- */


passthru: C.h;
void showWordStats();
endpassthru;

data:
  char *storage;
  int length;

methods:

group: newMethods;

   word *wordInit1(char *newWord);
   -- Initialize a word with a character string.

   word *wordInit2(char newChar, int count);
   -- Initialize a word with a character and
   -- count.  The new word will contain a null
   -- terminated buffer containing count number of
   -- newChars.

   int getLength();
   -- Get the length of a word.

   int wordToInt();
   -- Translate a word to an integer, such as "123" to 123.

   void wrdReplace(char *newWord);
   -- Replace the contents of a word by another word.

group: baseTypeOverrides;
   override match;
   -- See the definition of baseType for more information.

   override print;
   -- See the definition of baseType for more information.

group: SystemMethodOverrides;
   override somInit;
   override somUninit;
   override somDumpSelfInt;
