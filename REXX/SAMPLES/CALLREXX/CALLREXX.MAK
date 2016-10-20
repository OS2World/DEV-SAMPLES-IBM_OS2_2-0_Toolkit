# NMAKE-compatible MAKE file for the REXX sample program CALLREXX.EXE.
# This uses the IBM C Set/2 compiler and LINK386.

callrexx.exe:     callrexx.obj
    LINK386 /PM:VIO callrexx.obj,callrexx.exe,,REXX,,

callrexx.obj:     callrexx.c
    icc -c callrexx.c

