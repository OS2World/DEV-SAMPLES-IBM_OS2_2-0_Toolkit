#===================================================================
#
# Makefile for IPF Sample
# Created by IBM Corporation 1991
#
#===================================================================

#===================================================================
#
# Common definitions for the IBM compiler environment
#
#===================================================================

.SUFFIXES:
.SUFFIXES: .c .bmp .def .dll .h .ico .ipf .obj .rc .res

#===================================================================
#
# Default compilation macros for sample programs
#
# Compile switches that are enabled
# /c      compile without linking
# /Ge-    build a DLL file, not an .EXE
# /Gd-    statically link the run-time library
# /Re     generate executable code to run in a run-time environment
# /ss     allow use of double slashes (//) for comments
# /Ms     use SYSTEM linkage for functions and not OPTILINK
# /Gm-    link with single-threading libraries
# /W3     set the warning level to three
#
#===================================================================

CC      = icc /c /Ge- /Gd- /Se /Re /ss /Ms /Gm- /W3

LFLAGS  = /NOE /NOD /NOI /M
LINK    = link386 $(LFLAGS)

#===================================================================
#
# Libraries
#
# DDE4NBS  - Single tasking, standard library, static binding
# DDE4NBSO - Single tasking, standard library, dynamic binding
# DDE4NBSI - Single tasking, standard library, import dynamic binding
# DDE4SBS  - Single tasking, standard library
# DDE4SBM  - Single tasking, migration library
# DDE4MBS  - Multi tasking, standard library
# DDE4MBM  - Multi tasking, migration library
#
#===================================================================

LIBS    = DDE4MBS + OS2386
STLIBS  = DDE4SBS + OS2386
MTLIBS  = DDE4MBS + OS2386
DLLLIBS = DDE4NBS + DDE4NBSO + OS2386
VLIBS   = DDE4SBS + VDH + OS2386

#===================================================================
#
# Rules for generating object, linker response and definition files
#
#===================================================================

.c.obj:
    $(CC) -Fo $*.obj $*.c

.rc.res:
        rc -r $*.rc

.ipf.inf:
        ipfc /inf $*.ipf

#===================================================================

all: ipf.dll ipf.inf

#
# Create .DLL file
#

ipf.dll: ipf.def ipf.obj ipf.res
         $(LINK) ipf.obj, ipf, ipf, $(DLLLIBS), ipf.def
         rc -p -x ipf.res ipf.dll

#
# Create .RES file
#

ipf.res: ipf.rc ipf.ico ipf.h \
         frame1.bmp frame2.bmp frame3.bmp frame4.bmp frame5.bmp

#
# Create .OBJ file
#

ipf.obj: ipf.c ipf.h

#
# Create .INF file
#

ipf.inf: ipf.ipf

