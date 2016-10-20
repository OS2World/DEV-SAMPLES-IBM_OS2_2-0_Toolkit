#===================================================================
#
#   Template Make file
#   Copyright 1991 IBM Corporation
#
#===================================================================

include ..\ibmsamp.inc

HEADERS = main.h xtrn.h

LIBS    = DDE4NBS + os2386
#-------------------------------------------------------------------
#   A list of all of the object files
#-------------------------------------------------------------------
ALL_OBJ1 = main.obj user.obj init.obj pnt.obj dlg.obj help.obj
ALL_OBJ2 = file.obj edit.obj thrd.obj



#-------------------------------------------------------------------
#   A list of all of the Help text files
#-------------------------------------------------------------------
ALL_IPF = template.ipf file.ipf edit.ipf help.ipf dlg.ipf menu.ipf



#-------------------------------------------------------------------
#   This section lists all files to be built by the make.  The
#   makefile builds the executible as well as its associated help
#   file.
#-------------------------------------------------------------------
all: template.exe template.hlp


#-------------------------------------------------------------------
#   This section creates the command file used by the linker.  This
#   command file is recreated automatically every time you change
#   the object file list, linker flags, or library list.
#-------------------------------------------------------------------
template.lnk: template.mak
    echo $(ALL_OBJ1) +           > template.lnk
    echo $(ALL_OBJ2)            >> template.lnk
    echo template.exe           >> template.lnk
    echo template.map           >> template.lnk
    echo $(LIBS)                >> template.lnk
    echo template.def           >> template.lnk



#===================================================================
#
# Dependencies
#
#   This section lists all object files needed to be built for the
#   application, along with the files it is dependent upon (e.g. its
#   source and any header files).
#
#===================================================================

main.res: main.rc main.ico main.h dlg.h template.dlg help.rc help.h
    copy ..\prodinfo.bmp
    $(RC) -r main.rc main.res
    del prodinfo.bmp

main.obj: main.c $(HEADERS)

file.obj: file.c $(HEADERS)

edit.obj: edit.c $(HEADERS)

user.obj: user.c $(HEADERS)

init.obj: init.c $(HEADERS)

pnt.obj: pnt.c $(HEADERS)

dlg.obj: dlg.c $(HEADERS)

help.obj: help.c $(HEADERS) help.h

thrd.obj: thrd.c $(HEADERS)



#-------------------------------------------------------------------
#   This section creates the help manager file.  The IPF compiler
#   creates a file called main.hlp which is renamed to template.hlp.
#-------------------------------------------------------------------
template.hlp: $(ALL_IPF)

#-------------------------------------------------------------------
#   This section links the object modules into the finished program
#   using the linker command file created earlier.  At the end, the
#   resource file is bound to the application.
#-------------------------------------------------------------------
template.exe: $(ALL_OBJ1) $(ALL_OBJ2) template.def template.lnk main.res
    $(LINK) @template.lnk
    rc -p -x main.res template.exe
