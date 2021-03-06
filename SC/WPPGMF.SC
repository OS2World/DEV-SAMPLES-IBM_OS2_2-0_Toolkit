
# This file was generated by the SOM Compiler.
# FileName: wppgmf.sc.
# Generated using:
#     SOM Precompiler spc: 1.22
#     SOM Emitter emitcsc: 1.10

/*
 *  Module Header
 * 
 *  Module Name: WPPGMF
 * 
 *  OS/2 Presentation Manager Workplace class definitions
 * 
 *  Copyright (c) International Business Machines Corporation 1991, 1992
 * 
 */

#include "wpdataf.sc"

class: WPProgramFile, 
    external stem = wppgm, local, external prefix = pgm_, 
    classprefix = pgmM_, major version = 1, minor version = 2, 
    file stem = wppgmf;


parent class: WPDataFile;


release order:
    wpAddProgramAssociationPage, wpAddProgramPage, wpAddProgramSessionPage, 
    wpSetProgDetails, wpQueryProgDetails, wpSetProgIcon, 
    wpQueryAssociationFilter, wpQueryAssociationType, wpSetAssociationFilter, 
    wpSetAssociationType;

methods:


    ULONG    wpAddProgramAssociationPage(HWND hwndNotebook), name lookup;

    BOOL    wpQueryProgDetails(PPROGDETAILS pProgDetails,
		PULONG pulSize), name lookup;

    BOOL    wpSetProgDetails(PPROGDETAILS pProgDetails), name lookup;

    ULONG    wpAddProgramPage(HWND hwndNotebook), name lookup;

    ULONG    wpAddProgramSessionPage(HWND hwndNotebook), name lookup;

    PSZ    wpQueryAssociationFilter(), name lookup;

    PSZ    wpQueryAssociationType(), name lookup;

    BOOL    wpSetAssociationFilter(PSZ pszFilter), name lookup;

    BOOL    wpSetAssociationType(PSZ pszType), name lookup;

    override wpSetAssociatedFileIcon;

    -- From WPDataFile

    override wpInitData;

    -- From WPObject

    override wpSaveState;

    -- From WPObject

    override wpRestoreState;

    -- From WPObject

    override wpAddSettingsPages;

    -- From WPObject

    override wpOpen;

    -- From WPObject

    override wpModifyPopupMenu;

    -- From WPObject

    override wpMenuItemSelected;

    -- From WPObject

    override wpMenuItemHelpSelected;

    -- From WPObject

    override wpMoveObject;

    -- From WPObject

    override wpDragOver;

    -- From WPObject

    override wpDrop;

    -- From WPObject

    override wpCopyObject;

    -- From WPObject

    override wpConfirmRenameFileWithExt;

    -- From WPFileSystem

    override wpCreateAnother;

    -- From WPObject

    override wpFilterPopupMenu;

    -- From WPObject

    override wpSetup;

    -- From WPObject

    override wpQueryNameClashOptions;

    -- From WPObject

    override wpclsQueryTitle, class;

    -- From WPObject

    override wpclsQueryIconData, class;

    -- From WPObject

    override wpclsQueryDefaultView, class;

    -- From WPObject

    override wpclsQueryStyle, class;

    -- From WPObject

