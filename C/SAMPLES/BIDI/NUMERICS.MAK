# This is the make file to create the NUMERICS.EXE sample

include ..\ibmsamp.inc

all : numerics.exe

numerics.lnk: numerics.mak
    echo numerics.obj              > numerics.lnk
    echo numerics.exe           >> numerics.lnk
    echo numerics.map           >> numerics.lnk
    echo $(MTLIBS)              >> numerics.lnk
    echo numerics.def           >> numerics.lnk

numerics.obj : numerics.c

numerics.exe: numerics.obj numerics.lnk
    $(LINK) @numerics.lnk

