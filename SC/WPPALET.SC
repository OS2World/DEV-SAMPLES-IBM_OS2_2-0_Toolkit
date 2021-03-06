
# This file was generated by the SOM Compiler.
# FileName: wppalet.sc.
# Generated using:
#     SOM Precompiler spc: 1.22
#     SOM Emitter emitcsc: 1.10

/*
 *  Module Header
 * 
 *  Module Name: WPPALET
 * 
 *  OS/2 Presentation Manager Workplace class definitions
 * 
 *  Copyright (c) International Business Machines Corporation 1991, 1992
 * 
 */

#include "wpabs.sc"

class: WPPalette, 
    external stem = wppal, local, external prefix = pal_, 
    classprefix = palM_, major version = 1, minor version = 2, 
    file stem = wppalet;


parent class: WPAbstract;


release order:
    wpPaintCell, wpSelectCell, wpSetupCell, 
    wpQueryPaletteInfo, wpSetPaletteInfo, wpEditCell, 
    wpDragCell, withdrawn, wpInitCellStructs, 
    wpRedrawCell, wpPaintPalette, wpMouseAction, 
    wpQueryPaletteHelp, wpShowPalettePointer, wpclsQueryEditString;

methods:


    VOID    wpPaintCell(PCELL pCell,
		HPS hps,
		PRECTL prcl,
		BOOL fHilite);

    BOOL    wpSetupCell(PVOID pCellData,
		ULONG cb,
		ULONG x,
		ULONG y);

    BOOL    wpRedrawCell(PCELL pCell);

    BOOL    wpQueryPaletteInfo(PPALINFO pPalInfo);

    BOOL    wpSetPaletteInfo(PPALINFO pPalInfo);

    BOOL    wpEditCell(PCELL pCell,
		HWND hwndPal);

    BOOL    wpDragCell(PCELL pCell,
		HWND hwndPal,
		PPOINTL ptlDrag);

    PSZ    wpclsQueryEditString(), class;

    ULONG    wpQueryPaletteHelp();

    override wpInitData;

    -- From WPObject

    override wpUnInitData;

    -- From WPObject

    override wpSetup;

    -- From WPObject

    override wpSaveState;

    -- From WPObject

    override wpRestoreState;

    -- From WPObject

    override wpMenuItemSelected;

    -- From WPObject

    override wpModifyPopupMenu;

    -- From WPObject

    override wpFilterPopupMenu;

    -- From WPObject

    override wpOpen;

    -- From WPObject

    override wpMenuItemHelpSelected;

    -- From WPObject

    override wpclsQueryTitle, class;

    -- From WPObject

    override wpclsQueryStyle, class;

    -- From WPObject

    override wpclsQueryDefaultView, class;

    -- From WPObject

    override wpclsQueryDefaultHelp, class;

    -- From WPObject

