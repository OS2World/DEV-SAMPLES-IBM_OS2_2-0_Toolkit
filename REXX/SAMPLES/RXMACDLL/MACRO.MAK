# NMAKE-compatible MAKE file for the REXX sample program macro.dll.
# This uses the IBM C Set/2 compiler and LINK386.

macro.dll:     macro.obj macro.def
         link386 macro.obj,macro.dll,,REXX,macro.def

macro.obj:     macro.c
         icc -c -Ge- macro.c

