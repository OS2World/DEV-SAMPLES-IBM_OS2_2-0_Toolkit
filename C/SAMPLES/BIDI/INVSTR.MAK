# This is the make file to create the INVSTR.EXE sample

include ..\ibmsamp.inc

all : invstr.exe

invstr.lnk: invstr.mak
    echo invstr.obj              > invstr.lnk
    echo invstr.exe           >> invstr.lnk
    echo invstr.map           >> invstr.lnk
    echo $(MTLIBS)              >> invstr.lnk
    echo invstr.def           >> invstr.lnk

invstr.obj : invstr.c

invstr.exe: invstr.obj invstr.lnk
    $(LINK) @invstr.lnk
