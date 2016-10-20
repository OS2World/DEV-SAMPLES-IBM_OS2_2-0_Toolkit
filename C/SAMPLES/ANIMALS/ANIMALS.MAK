#   @(#)animals.mak 1.2 2/3/92 20:40:13 [2/3/92] (c)IBM Corp.  1992
# Makefile for Animals program
# Created by IBM Corporation, 1992
#
include ..\ibmsamp.inc

OBJS	= animal.obj animeta.obj dogmeta.obj dog.obj ldog.obj bdog.obj main.obj
LIBS	= som + $(STLIBS)
SCPATH	= ..\..\..\sc

!if [set SMINCLUDE=.;$(SCPATH);] || \
    [set SMEMIT=h;ih;ph;sc] || \
    [set SMTMP=%TMP%]
!endif

.SUFFIXES: .c .csc .ih

.c.obj:
    $(CC) -I. $*.c

.csc.ih:
	sc $*

all: animals.exe

# Dependencies
#

main.obj: main.c animal.ih dog.ih ldog.ih bdog.ih

animeta.ih: animeta.csc
animeta.obj: animeta.c animeta.ih

dogmeta.ih: dogmeta.csc animeta.ih
dogmeta.obj: dogmeta.c dogmeta.ih dog.ih

animal.ih: animal.csc animeta.ih
animal.obj: animal.c animal.ih

dog.ih: dog.csc animal.ih dogmeta.ih
dog.obj: dog.c dog.ih

ldog.ih: ldog.csc dog.ih
ldog.obj: ldog.c ldog.ih

bdog.ih: bdog.csc dog.ih
bdog.obj: bdog.c bdog.ih

animals.exe: $(OBJS)
	$(LINK) /PM:VIO /NOI $(OBJS), animals, animals, $(LIBS), nul

clean:
	del *.obj *.ih *.ph *.h *.sc *.exe *.map
