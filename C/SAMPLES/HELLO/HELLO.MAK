#===================================================================
#
#   Hello Make file
#   Copyright 1991 IBM Corporation
#
#===================================================================

include ..\ibmsamp.inc

CC         = icc /c /Ge /Gd- /Se /Re /ss /Gm+

HEADERS = hello.h

#-------------------------------------------------------------------
#   A list of all of the object files
#-------------------------------------------------------------------
ALL_OBJ1 = hello.obj


all: hello.exe


hello.l: hello.mak
    echo $(ALL_OBJ1)            > hello.l
    echo hello.exe           >> hello.l
    echo hello.map           >> hello.l
    echo $(LIBS)                >> hello.l
    echo hello.def           >> hello.l




hello.res: hello.rc hello.ico hello.h

hello.obj: hello.c $(HEADERS)

hello.exe: $(ALL_OBJ1)  hello.def hello.l hello.res
    $(LINK) @hello.l
    rc -p -x hello.res hello.exe
