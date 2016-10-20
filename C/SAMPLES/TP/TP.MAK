#   @(#)tp.mak 1.2 1/22/92 16:12:26 [1/26/92] (c)IBM Corp.  1992
# Makefile for Tp (text processing) program
# Created by IBM Corporation, 1991
#

include ..\ibmsamp.inc

OBJS	= bt.obj helper.obj word.obj link.obj ll.obj fm.obj tpword.obj \
	  textline.obj colblk.obj page.obj ep.obj suep.obj footer.obj \
	  header.obj txtep.obj ipep.obj blep.obj main.obj
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

all: tp.exe

bt.ih: bt.csc
bt.obj: bt.c bt.ih

helper.obj: helper.c helper.h

word.ih: word.csc bt.ih
word.obj: word.c word.ih

link.ih: link.csc bt.ih
link.obj: link.c link.ih

ll.ih: ll.csc bt.ih
ll.obj: ll.c ll.ih

fm.ih: fm.csc
fm.obj: fm.c fm.ih

tpword.ih: tpword.csc word.ih
tpword.obj: tpword.c tpword.ih

textline.ih: textline.csc ll.ih
textline.obj: textline.c textline.ih

colblk.ih: colblk.csc ll.ih
colblk.obj: colblk.c colblk.ih

page.ih: page.csc
page.obj: page.c page.ih

ep.ih: ep.csc
ep.obj: ep.c tpword.ih page.ih txtep.ih header.ih footer.ih ipep.ih blep.ih ep.ih

suep.ih: suep.csc ep.ih
suep.obj: suep.c suep.ih

footer.ih: footer.csc ep.ih
footer.obj: footer.c footer.ih page.ih tpword.ih

header.ih: header.csc ep.ih
header.obj: header.c header.ih

txtep.ih: txtep.csc ep.ih
txtep.obj: txtep.c txtep.ih

ipep.ih: ipep.csc txtep.ih
ipep.obj: ipep.c ipep.ih

blep.ih: blep.csc txtep.ih
blep.obj: blep.c blep.ih

main.obj: main.c suep.ih

tp.exe: $(OBJS)
	$(LINK) /PM:VIO /NOI $(OBJS), tp, tp, $(LIBS), nul

clean:
	del *.obj *.ih *.ph *.h *.sc *.exe *.map
