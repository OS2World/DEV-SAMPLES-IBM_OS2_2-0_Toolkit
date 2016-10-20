# This is the make file tor create the SETPRINT.EXE sample

include ..\ibmsamp.inc

all : setprint.exe

setprint.lnk: setprint.mak
    echo setprint.obj              > setprint.lnk
    echo setprint.exe           >> setprint.lnk
    echo setprint.map           >> setprint.lnk
    echo $(MTLIBS)              >> setprint.lnk
    echo setprint.def           >> setprint.lnk

setprint.obj : setprint.c

setprint.exe: setprint.obj setprint.lnk
    $(LINK) @setprint.lnk


