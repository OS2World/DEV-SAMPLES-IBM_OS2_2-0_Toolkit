# NMAKE-compatible MAKE file for the REXX sample program REXXUTIL.DLL.
# This uses the IBM C Set/2 compiler and LINK386.

rexxutil.dll:     rexxutil.obj  rexxutil.def
         LINK386 rexxutil.obj,rexxutil.dll,,REXX,rexxutil.def;

rexxutil.obj:     rexxutil.c
         icc -c -Ge- rexxutil.c


