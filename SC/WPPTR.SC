
# This file was generated by the SOM Compiler.
# FileName: wpptr.sc.
# Generated using:
#     SOM Precompiler spc: 1.22
#     SOM Emitter emitcsc: 1.10

/*
 *  Module Header
 * 
 *  Module Name: WPPTR
 * 
 *  OS/2 Presentation Manager Workplace class definitions
 * 
 *  Copyright (c) International Business Machines Corporation 1991, 1992
 * 
 */

#include "wpdataf.sc"

class: WPPointer, 
    external stem = wpptr, local, external prefix = ptr_, 
    classprefix = ptrM_, major version = 1, minor version = 2, 
    file stem = wpptr;


parent class: WPDataFile;

methods:


    override wpSetup;

    -- From WPObject

    override wpclsQueryInstanceFilter, class;

    -- From WPFileSystem

    override wpclsQueryInstanceType, class;

    -- From WPFileSystem

    override wpclsInitData, class;

    -- From WPObject

    override wpclsQueryTitle, class;

    -- From WPObject

    override wpclsQueryDefaultHelp, class;

    -- From WPObject

