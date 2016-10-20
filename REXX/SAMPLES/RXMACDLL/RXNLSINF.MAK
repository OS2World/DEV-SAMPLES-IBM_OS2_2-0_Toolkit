# NMAKE-compatible MAKE file for the REXX sample program macro.dll.
# This uses the IBM C Set/2 compiler and LINK386.

rxnlsinf.dll:     rxnlsinf.obj rxnlsinf.def
         link386 rxnlsinf.obj,rxnlsinf.dll,,REXX,rxnlsinf.def

rxnlsinf.obj:     rxnlsinf.c
         icc -c -Ge- rxnlsinf.c
