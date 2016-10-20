# This is the make file to create the SHAPE.EXE sample

include ..\ibmsamp.inc

all : shape.exe

shape.lnk: shape.mak
    echo shape.obj              > shape.lnk
    echo shape.exe           >> shape.lnk
    echo shape.map           >> shape.lnk
    echo $(MTLIBS)              >> shape.lnk
    echo shape.def           >> shape.lnk

shape.obj : shape.c

shape.exe: shape.obj shape.lnk
    $(LINK) @shape.lnk


