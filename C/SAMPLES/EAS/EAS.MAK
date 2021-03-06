#===================================================================
#
#   EAS.MAK - EAS Application Make file
#   (C) Copyright IBM Corporation 1992.
#
#===================================================================

#-------------------------------------------------------------------
#   IBMSAMP.INC - sets up for IBM Compiler
#-------------------------------------------------------------------
include ..\ibmsamp.inc

HEADERS = eas.h

#===================================================================
#
#   A list of all of the object files
#
#===================================================================
ALL_OBJS = eas.obj easea.obj easfile.obj easinit.obj eashelp.obj

ALL_IPF = eas.ipf

#-------------------------------------------------------------------
#   This section lists all files to be built by the make.  The
#   makefile builds the executible as well as its associated help
#   file.
#-------------------------------------------------------------------
all: eas.exe eas.hlp

#-------------------------------------------------------------------
#   This section creates the command file used by the linker.  This
#   command file is recreated automatically every time you change
#   the object file list, linker flags, or library list.
#-------------------------------------------------------------------
eas.lnk: eas.mak
    echo $(ALL_OBJS)             > eas.lnk
    echo eas.exe                >> eas.lnk
    echo eas.map                >> eas.lnk
    echo $(MTLIBS)              >> eas.lnk
    echo eas.def                >> eas.lnk

#-------------------------------------------------------------------
#   Dependencies
#     This section lists all object files needed to be built for the
#     application, along with the files it is dependent upon (e.g.
#     its source and any header files).
#-------------------------------------------------------------------
eas.res: eas.rc $(HEADERS) eas.ico eas.dlg

eas.hlp: $(ALL_IPF)

eas.obj: eas.c $(HEADERS)

easea.obj: easea.c $(HEADERS)

easfile.obj: easfile.c $(HEADERS)

easinit.obj: easinit.c $(HEADERS)

eashelp.obj: eashelp.c $(HEADERS)

eas.exe: $(ALL_OBJS) eas.res eas.def eas.lnk
    $(LINK) @eas.lnk
    rc -p -x eas.res eas.exe

