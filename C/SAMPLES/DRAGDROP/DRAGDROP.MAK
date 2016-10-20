# Makefile for DRAGDROP.EXE
# Copyright 1991 IBM Corporation
#

include ..\ibmsamp.inc

all:    DRAGDROP.EXE            DRAGDROP.HLP

OBJS    =       dragdrop.obj dragdrag.obj dragheap.obj draghelp.obj

# Resources
#
dragdrop.res:      dragdrop.rc dragdrop.ico dragdrop.ptr dragdrop.h \
                                dragdrop.dlg draghelp.rc draghelp.h
        copy ..\prodinfo.bmp
        rc -r dragdrop.rc
        del prodinfo.bmp

# C files
#
dragdrop.obj:      dragdrop.c dragdrop.h

draghelp.obj:      draghelp.c dragdrop.h draghelp.h

dragheap.obj:      dragheap.c dragdrop.h

dragdrag.obj:      dragdrag.c dragdrop.h

# Main files:  DRAGDROP.EXE
#
dragdrop.exe:      dragdrop.mak dragdrop.def $(OBJS) dragdrop.res
    $(LINK) $(OBJS), dragdrop, dragdrop, $(LIBS), dragdrop.def
    rc -p -x dragdrop.res dragdrop.exe

dragdrop.hlp:   dragdrop.ipf dragfile.ipf draghelp.ipf dragdlg.ipf \
                dragmenu.ipf dragwnd.ipf

