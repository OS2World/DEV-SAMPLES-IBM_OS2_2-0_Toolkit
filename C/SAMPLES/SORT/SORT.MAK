#===================================================================
#
#   SORT.MAK - Sort Application Make file
#   (C) Copyright IBM Corporation 1992.
#
#===================================================================

#-------------------------------------------------------------------
#   IBMSAMP.INC - sets up for IBM Compiler
#-------------------------------------------------------------------
include ..\ibmsamp.inc

HEADERS = sort.h

#-------------------------------------------------------------------
#
#   A list of all of the object files
#
#-------------------------------------------------------------------
ALL_OBJS = sort.obj
ALL_IPF = sort.ipf

#-------------------------------------------------------------------
#   This section lists all files to be built by the make.  The
#   makefile builds the executible as well as its associated help
#   file.
#-------------------------------------------------------------------
all: sort.exe sort.hlp

#-------------------------------------------------------------------
#   This section creates the command file used by the linker.  This
#   command file is recreated automatically every time you change
#   the object file list, linker flags, or library list.
#-------------------------------------------------------------------
sort.lnk: sort.mak
    echo $(ALL_OBJS)              > sort.lnk
    echo sort.exe                >> sort.lnk
    echo sort.map                >> sort.lnk
    echo $(MTLIBS)               >> sort.lnk
    echo sort.def                >> sort.lnk

#-------------------------------------------------------------------
#   Dependencies
#     This section lists all object files needed to be built for the
#     application, along with the files it is dependent upon (e.g.
#     its source and any header files).
#-------------------------------------------------------------------
sort.res: sort.rc $(HEADERS) sort.ico sort.dlg

sort.hlp: $(ALL_IPF)

sort.obj: sort.c $(HEADERS)

sort.exe: $(ALL_OBJS) sort.res sort.def sort.lnk
    $(LINK) @sort.lnk
    rc -p -x sort.res sort.exe

