#===================================================================
#
#   Graphic Sample Make file
#   Created 1991 IBM Corporation
#
#===================================================================

include ..\ibmsamp.inc

HEADERS = graphic.h

#-------------------------------------------------------------------
#   A list of all of the object files
#-------------------------------------------------------------------
ALL_OBJ1 = graphic.obj file.obj

#-------------------------------------------------------------------
#   This section lists all files to be built by the make.  The
#   makefile builds the executible as well as its associated help
#   file.
#-------------------------------------------------------------------
all: graphic.exe graphic.hlp

#-------------------------------------------------------------------
#   This section creates the command file used by the linker.  This
#   command file is recreated automatically every time you change
#   the object file list, linker flags, or library list.
#-------------------------------------------------------------------
graphic.lnk: graphic.mak
    echo $(ALL_OBJ1)            > graphic.lnk
    echo graphic.exe            >> graphic.lnk
    echo graphic.map /map /cod           >> graphic.lnk
    echo $(LIBS)                >> graphic.lnk
    echo graphic.def            >> graphic.lnk

#===================================================================
#
# Dependencies
#
#   This section lists all object files needed to be built for the
#   application, along with the files it is dependent upon (e.g. its
#   source and any header files).
#
#===================================================================

graphic.res: graphic.rc graphic.ico graphic.h

graphic.obj: graphic.c $(HEADERS)

file.obj: file.c $(HEADERS)


#-------------------------------------------------------------------
#   This section creates the help manager file.
#-------------------------------------------------------------------
graphic.hlp: graphic.ipf

#-------------------------------------------------------------------
#   This section links the object modules into the finished program
#   using the linker command file created earlier.  At the end, the
#   resource file is bound to the application.
#-------------------------------------------------------------------
graphic.exe: $(ALL_OBJ1) graphic.def graphic.lnk graphic.res
    $(LINK) @graphic.lnk
    rc -p -x graphic.res graphic.exe
