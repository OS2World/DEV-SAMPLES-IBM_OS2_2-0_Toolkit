#===================================================================
#
#   Copyright 1992 IBM Corporation
#
#===================================================================

#
#

#===================================================================
#
#   Sample application makefile, common definitions for the IBM C
#   Set II compiler environment
#
#===================================================================
.SUFFIXES:
.SUFFIXES: .rc .res .obj .lst .c .asm .hlp .itl .ipf
#===================================================================
# Default compilation macros for sample programs
#
# Compile switches  that are enabled
# /c      compile don't link
# /ss     allow  "//" for comment lines
# /Ms     use the system calling convention and not _optlink as the default
# /Gd-    disable optimization
# /Se     allow C Set/2  extensions
#
#

CC         = icc

GCFLAGS =
OFLAGS  = /O- /Rn /Gr+ /Fa /Ls+
CFLAGS  = /G3 /Sp1 /W3 /Ss+ /DM_I386 $(CINC) /Q /C $(GCFLAGS) $(FLAGS)
SUPPRESSDLLLIBRARY = /gp
LFLAGS   = /NOI /NOE /NOD /MAP:0 /EXEPACK /ALIGN:16
LINK    = LINK386  $(LFLAGS)
VLIBS   = DDE4NBS + vdh + os2386

.c.lst:
    $(CC) -Fc$*.lst -Fo$*.obj $*.c

.c.obj:
    $(CC) $(OFLAGS) $(CFLAGS) $(CINC) $< ;

#===================================================================
#
#   A list of all of the object files
#
#===================================================================

COBJ = vdft.obj  vdftpdd.obj





#-------------------------------------------------------------------
#   This section lists all files to be built by the make.  The
#   makefile builds the executible as well as its associated help
#   file.
#-------------------------------------------------------------------
all: vdft.sys



#-------------------------------------------------------------------
#   This section creates the command file used by the linker.  This
#   command file is recreated automatically every time you change
#   the object file list, linker flags, or library list.
#-------------------------------------------------------------------
vdd.lnk: vdd.mak
     echo $(COBJ)                >  vdd.lnk
     echo vdft.sys               >> vdd.lnk
     echo vdft.map               >> vdd.lnk
     echo $(VLIBS)               >> vdd.lnk
     echo vdd.def                >> vdd.lnk




#===================================================================
#
# Dependencies
#
#   This section lists all object files needed to be built for the
#   application, along with the files it is dependent upon (e.g. its
#   source and any header files).
#
#===================================================================


vdft.obj:    vdft.c


vdftpdd.obj:      vdftpdd.c
        $(CC) $(OFLAGS) $(CFLAGS) $(SUPPRESSDLLLIBRARY) $(CINC) $*.c

vdft.sys:   $(COBJ) vdd.def vdd.lnk
    $(LINK) $(LFLAGS) @vdd.lnk
    mapsym  vdft.map


