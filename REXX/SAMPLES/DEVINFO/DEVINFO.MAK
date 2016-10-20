# NMAKE-compatible MAKE file for the REXX sample program DEVINFO.DLL.
# This uses the IBM C Set/2 compiler and LINK386.

devinfo.dll: devinfo.def devinfo.obj
  link386 devinfo.obj,devinfo.dll,,REXX,devinfo.def

devinfo.obj:
  ICC -C -Ge-  DEVINFO.C




