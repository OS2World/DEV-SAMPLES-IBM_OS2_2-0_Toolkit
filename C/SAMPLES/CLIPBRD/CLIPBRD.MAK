#===================================================================
#
#   Clipbrd Make file
#   Copyright 1991 IBM Corporation
#
#===================================================================
include ..\ibmsamp.inc

HEADERS = clipbrd.h

#-------------------------------------------------------------------
#   A list of all of the object files
#-------------------------------------------------------------------
ALL_OBJ1 = clipbrd.obj


all: clipbrd.exe


clipbrd.l: clipbrd.mak
    echo $(ALL_OBJ1)            > clipbrd.l
    echo clipbrd.exe           >> clipbrd.l
    echo clipbrd.map           >> clipbrd.l
    echo $(LIBS)                >> clipbrd.l
    echo clipbrd.def           >> clipbrd.l


clipbrd.res: clipbrd.rc clipbrd.ico clipbrd.h clipbrd.bmp
        copy ..\prodinfo.bmp
        rc -r clipbrd.rc
        del prodinfo.bmp

clipbrd.obj: clipbrd.c $(HEADERS)

clipbrd.exe: $(ALL_OBJ1)  clipbrd.def clipbrd.l clipbrd.res
    $(LINK) @clipbrd.l
    rc -p -x clipbrd.res clipbrd.exe
