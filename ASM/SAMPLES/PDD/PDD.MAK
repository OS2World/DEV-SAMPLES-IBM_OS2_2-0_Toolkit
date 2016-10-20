#===================================================================
#
#
#   Copyright 1990,1992 IBM Corporation
#
#===================================================================

#
# Comment out or delete the .inc file you don't want
#
#===================================================================
#
#   A list of all of the object files
#
#===================================================================

AOBJ = pddddm.OBJ pddidc.obj pddinit.obj



#-------------------------------------------------------------------
#   This section lists all files to be built by the make.
#-------------------------------------------------------------------
all: $(AOBJ) pdd.lnk pdd.sys



#-------------------------------------------------------------------
#   This section creates the command file used by the linker.  This
#   command file is recreated automatically every time you change
#   the object file list, linker flags, or library list.
#-------------------------------------------------------------------


#===================================================================
#
# Dependencies
#
#   This section lists all object files needed to be built for the
#   application, along with the files it is dependent upon (e.g. its
#   source and any header files).
#
#===================================================================

pddddm.obj: pddddm.asm

pddidc.obj: pddidc.asm

pddinit.obj: pddinit.asm


pdd.lnk: pdd.mak
        echo $(AOBJ)   >  pdd.lnk
        echo pdd.sys   >> pdd.lnk
        echo pdd.map,os2286, >> pdd.lnk
        echo pdd.def;  >> pdd.lnk




pdd.sys:  $(AOBJ) pdd.def pdd.lnk
          link386  @pdd.lnk

