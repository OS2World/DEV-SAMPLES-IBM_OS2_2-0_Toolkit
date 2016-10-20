# This is the make file to created the REVSCR.EXE sample

include ..\ibmsamp.inc

all : revscr.exe

revscr.lnk: revscr.mak
    echo revscr.obj              > revscr.lnk
    echo revscr.exe           >> revscr.lnk
    echo revscr.map           >> revscr.lnk
    echo $(MTLIBS)              >> revscr.lnk
    echo revscr.def           >> revscr.lnk

revscr.obj : revscr.c

revscr.exe: revscr.obj revscr.lnk
    $(LINK) @revscr.lnk
