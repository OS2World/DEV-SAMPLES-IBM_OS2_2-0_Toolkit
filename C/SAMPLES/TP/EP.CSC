#   @(#)ep.csc 1.3 1/22/92 16:08:51 [1/26/92] (c)IBM Corp. 1992

-- This class is adapted from the book
--   Class Construction in C and C++, Object Oriented Fundamentals
--   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
-- Reprinted with permission.

include <somobj.sc>

class: envProcessor,
  local;

parent: SOMObject;

/*
----------------------------------------------------
  Class: envProcessor

Purpose: This is the most basic environment processor, from
	 which both the setUpEnvProcessor and txtEnvProcessor
	 is derived.  This class provides defaults for many
	 methods, but, with the exception of the get methods,
	 many will be overridden by later derivations.
	 This class will not be instantiated directly.
	 It will be used as the basis for further class
	 derivations.
---------------------------------------------------- */


passthru: C.h;
#include "page.h"
#include "fm.h"
#include "tpword.h"
endpassthru;

data:

    page	 *thisPage;
    fileMgr	 *thisFile;
    envProcessor *previousEnv;

methods:

group: Initializers;

   void epInit1(envProcessor *lastEnv);
   -- Used to initialize a new environment from an
   -- existing environment.

group: ClassMethods;

  void epProcessEnvironment();
  -- Defines what it means to process a given
  -- environment.  This method MUST be overridden in
  -- derived classes.

  void epStartUpNewEnvironment(TPWord *envName);
  -- Defines what steps need to be taken at the start
  -- of this environment.

  void epInitializeEnvironment();
  -- Defines what steps need to be taken to initialize
  -- a given environment.

  void epShutdownEnvironment();
  -- Defines what steps need to be taken to shutdown this
  -- environment.

  void epPrepareForNewEnvironment();
  -- Defines what steps this environment should take as it
  -- prepares to transfer control to a new environment.

group: GetMethods;

  int  epGetParagraphIndentation();
  -- Get the indentation for a new paragraph for this environment.

  int  epGetLineIndentation();
  -- Get the indentation for a new line for this environment.

group: InternalGetMethods;

  page	  *epGetPage();

  fileMgr *epGetFileMgr();

  envProcessor *epGetPreviousEnv();

  char *epGetClassName();

group: SetMethods;

  void	   epSetPage(page *newPage);

  void	   epSetFileMgr(fileMgr *newFileMgr);

group: SystemMethodOverrides;

   override somInit;

   override somUninit;

   override somDumpSelfInt;
