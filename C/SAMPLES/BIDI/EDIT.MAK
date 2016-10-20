# This is the make file to created the EDIT.EXE sample

include ..\ibmsamp.inc

all : edit.exe

edit.lnk: edit.mak
    echo edit.obj              > edit.lnk
    echo edit.exe           >> edit.lnk
    echo edit.map           >> edit.lnk
    echo $(MTLIBS)              >> edit.lnk
    echo edit.def           >> edit.lnk

edit.obj : edit.c

edit.exe: edit.obj edit.lnk
    $(LINK) @edit.lnk


