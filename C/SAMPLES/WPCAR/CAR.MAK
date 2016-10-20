#****************************************************************************
#
#  Work Place Shell Sample makefile
#
#  Copyright (C) 1992 IBM Corporation
#
#      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is
#      sample code created by IBM Corporation. This sample code is not
#      part of any standard or IBM product and is provided to you solely
#      for  the purpose of assisting you in the development of your
#      applications.  The code is provided "AS IS", without
#      warranty of any kind.  IBM shall not be liable for any damages
#      arising out of your use of the sample code, even if they have been
#      advised of the possibility of such damages.                                                    *
#
#****************************************************************************

!include ..\ibmsamp.inc

#****************************************************************************
#  Dot directive definition area (usually just suffixes)
#****************************************************************************

.SUFFIXES:
.SUFFIXES: .c .obj .dll .csc .sc .h .ih .ph .psc .rc .res

#****************************************************************************
#  Environment Setup for the component(s).
#****************************************************************************

SOMTEMP = .\somtemp
SCPATH  = ..\..\..\sc
HPATH   = ..\..\os2h
LIBPATH = ..\..\..\os2lib

!if [set SMINCLUDE=.;$(SCPATH);] || \
    [set SMTMP=$(SOMTEMP)] || \
    [set SMEMIT=ih;h;ph;psc;sc;c]
!endif

!if [cd $(SOMTEMP)]
!  if [md $(SOMTEMP)]
!    error error creating $(SOMTEMP) directory
!  endif
!else
!  if [cd ..]
!    error - Couldn't cd .. from $(SOMTEMP) directory
!  endif
!endif

#
# Compiler/tools Macros
#

CC      = $(CC) /Ge-
LINK    = LINK386
LDFLAGS = /noi /map /nol /nod /exepack /packcode /packdata /align:16
DLLLIBS = $(DLLLIBS) som.lib

#****************************************************************************
# Set up Macros that will contain all the different dependencies for the
# executables and dlls etc. that are generated.
#****************************************************************************

OBJS = car.obj

#****************************************************************************
#   Setup the inference rules for compiling source code to
#   object code.
#****************************************************************************

.c.obj:
        $(CC) -I$(HPATH) -c $<

.csc.ih:
        sc -v -r $*.csc

all: car.dll

#
# Specific Process Tag
#

car.ih:   $$(@B).csc $(HPATH)\wpdataf.h

car.obj: $$(@B).c $$(@B).ih $$(@B).h  $$(@B).sc $(HPATH)\wpdataf.h

car.dll: $$(@B).def $(OBJS) car.res
         $(LINK) $(LDFLAGS) $(OBJS),$@,,$(DLLLIBS),$*;
         rc -p -x $*.res $*.dll
         mapsym car.map

car.res: $$(@B).rc $$(@B).ih
         rc -r $*.rc $*.res
