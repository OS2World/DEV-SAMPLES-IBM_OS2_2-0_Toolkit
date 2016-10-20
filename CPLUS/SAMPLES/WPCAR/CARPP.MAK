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

#!include ..\ibmsamp.inc

LFLAGS   = /NOE /NOD /ALIGN:16 /EXEPACK /M /BASE:0x10000
LINK    = LINK386  $(LFLAGS)
LIBS    = DDE4MBS + OS2386
STLIBS  = DDE4SBS + OS2386
MTLIBS  = DDE4MBS + os2386
DLLLIBS = DDE4NBS + os2386
VLIBS   = DDE4SBS + vdh + os2386


#****************************************************************************
#  Dot directive definition area (usually just suffixes)
#****************************************************************************

.SUFFIXES:
.SUFFIXES: .cpp .obj .dll .csc .sc .xh .xih .xph .psc .rc .res .def

#****************************************************************************
#  Environment Setup for the component(s).
#****************************************************************************

SOMTEMP = .\somtemp
SCPATH  = ..\..\..\sc
HPATH   = ..\..\os2h
LIBPATH = ..\..\..\os2lib

!if [set SMINCLUDE=.;$(HPATH);$(SCPATH);] || \
    [set SMTMP=$(SOMTEMP)] || \
    [set SMEMIT=xih;xh;psc;sc;xc;def]
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

CPP     = icc /Ge-
LINK    = LINK386
LDFLAGS = /noi /map /nol /nod /exepack /packcode /packdata /align:16
DLLLIBS = $(DLLLIBS) som.lib

#****************************************************************************
# Set up Macros that will contain all the different dependencies for the
# executables and dlls etc. that are generated.
#****************************************************************************

OBJS = carpp.obj horn.obj brake.obj rpm.obj

#****************************************************************************
#   Setup the inference rules for compiling source code to
#   object code.
#****************************************************************************

.cpp.obj:
        $(CPP) -I$(HPATH) -c $<

# Remove pound signs to have CSC recompile
.csc.xih:
        sc -v -r  $*.csc

all: carpp.dll

#
# Specific Process Tag
#

horn.obj: $$(@B).cpp $$(@B).h carpp.xih

brake.obj: $$(@B).cpp $$(@B).h carpp.xih

rpm.obj: $$(@B).cpp $$(@B).h carpp.xih

carpp.xih:   $$(@B).csc $(HPATH)\wpdataf.xh

carpp.def:   $$(@B).csc

carpp.obj: $$(@B).cpp $$(@B).xih $$(@B).xh  $$(@B).sc $(HPATH)\wpdataf.xh horn.h brake.h rpm.h

carpp.dll: $$(@B).def $(OBJS) carpp.res
         $(LINK) $(LDFLAGS) $(OBJS),$@,,$(DLLLIBS),$*;
         rc -p -x $*.res $*.dll
         mapsym carpp.map

carpp.res: $$(@B).rc $$(@B).xih
         rc -r $*.rc $*.res
