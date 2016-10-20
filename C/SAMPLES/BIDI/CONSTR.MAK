# This is the make file to create CONSTR.EXE sample

include ..\ibmsamp.inc

all : constr.exe

constr.lnk: constr.mak
    echo constr.obj              > constr.lnk
    echo constr.exe           >> constr.lnk
    echo constr.map           >> constr.lnk
    echo $(MTLIBS)              >> constr.lnk
    echo constr.def           >> constr.lnk

constr.obj : constr.c

constr.exe: constr.obj constr.lnk
    $(LINK) @constr.lnk


