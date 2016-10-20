#===================================================================
#
#   SEMAPH.MAK - Semaph Application Make file
#   (C) Copyright IBM Corporation 1992.
#
#===================================================================
include ..\ibmsamp.inc

HEADERS = semaph.h

#===================================================================
#
#   A list of all of the object files
#
#===================================================================
ALL_OBJS = sem_main.obj sem_user.obj sem_init.obj sem_pnt.obj \
           semaph.obj sem_help.obj sem_dlg.obj
ALL_IPF =  semaph.ipf

#-------------------------------------------------------------------
#   This section lists all files to be built by the make.  The
#   makefile builds the executible as well as its associated help
#   file.
#-------------------------------------------------------------------
all: semaph.exe semaph.hlp

#-------------------------------------------------------------------
#   This section creates the command file used by the linker.  This
#   command file is recreated automatically every time you change
#   the object file list, linker flags, or library list.
#-------------------------------------------------------------------
semaph.lnk: semaph.mak
    echo $(ALL_OBJS)           > semaph.lnk
    echo semaph.exe           >> semaph.lnk
    echo semaph.map           >> semaph.lnk
    echo $(MTLIBS)            >> semaph.lnk
    echo semaph.def           >> semaph.lnk

#-------------------------------------------------------------------
#
#   Dependencies
#     This section lists all object files needed to be built for the
#     application, along with the files it is dependent upon (e.g.
#     its source and any header files).
#
#-------------------------------------------------------------------
semaph.res: semaph.rc $(HEADERS) semaph.dlg semaph.ico

semaph.hlp : $(ALL_IPF)

sem_main.obj: sem_main.c $(HEADERS)

sem_edit.obj: sem_edit.c $(HEADERS)

sem_user.obj: sem_user.c $(HEADERS)

semaph.obj: semaph.c $(HEADERS)

sem_help.obj: sem_help.c $(HEADERS)

sem_init.obj: sem_init.c $(HEADERS)

sem_pnt.obj: sem_pnt.c $(HEADERS)

sem_dlg.obj: sem_dlg.c $(HEADERS)

semaph.exe: $(ALL_OBJS) semaph.def semaph.lnk semaph.res
    $(LINK) @semaph.lnk
    rc -p -x semaph.res semaph.exe
