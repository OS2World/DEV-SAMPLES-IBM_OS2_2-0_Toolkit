
# This file was generated by the SOM Compiler.
# FileName: wpfsys.sc.
# Generated using:
#     SOM Precompiler spc: 1.22
#     SOM Emitter emitcsc: 1.10

/*
 *  Module Header
 * 
 *  Module Name: WPFSYS
 * 
 *  OS/2 Presentation Manager Workplace class definitions
 * 
 *  Copyright (c) International Business Machines Corporation 1991, 1992
 * 
 */

#include "wpobject.sc"

class: WPFileSystem, 
    external stem = wpfs, local, external prefix = fs_, 
    classprefix = fsM_, major version = 1, minor version = 2, 
    file stem = wpfsys;


parent class: WPObject;


release order:
    wpSetRealName, withdrawn_wpQueryRealName, wpSetType, 
    wpQueryType, wpSetAttr, wpQueryAttr, 
    wpQueryFilename, wpAddFile1Page, wpAddFile2Page, 
    wpAddFile3Page, wpAddFileMenuPage, wpQueryCreation, 
    wpQueryLastAccess, wpQueryLastWrite, wpQueryFileSize, 
    wpQueryEASize, wpSetDateInfo, wpSetFileSizeInfo, 
    wpclsQueryInstanceType, wpclsQueryInstanceFilter, wpRefresh, 
    wpPrintPlainTextFile, wpSetRefreshFlags, wpQueryRefreshFlags, 
    wpQueryDriveData, wpSetTitleAndRenameFile, wpConfirmRenameFileWithExt, 
    wpConfirmKeepAssoc, wpAddUserMenuItem, wpQueryDisk, 
    wpclsQueryObjectFromPath, wpQueryDateInfo, wpSetNewRealName, 
    wpAdoptNewRealName, wpQueryRealName, wpVerifyUpdateAccess, 
    wpAddUserItemsToPopupMenu;

methods:


    BOOL    wpSetRealName(PSZ pszName);

    BOOL    wpSetType(PSZ pszTypes,
		PFEA2LIST pfeal);

    PSZ    wpQueryType();

    BOOL    wpSetAttr(ULONG attrFile);

    ULONG    wpQueryAttr();

    ULONG    wpAddFile1Page(HWND hwndNotebook);

    ULONG    wpAddFile2Page(HWND hwndNotebook);

    ULONG    wpAddFile3Page(HWND hwndNotebook);

    ULONG    wpAddFileMenuPage(HWND hwndNotebook);

    ULONG    wpQueryCreation(FDATE *fdate,
		FTIME *ftime);

    ULONG    wpQueryLastAccess(FDATE *fdate,
		FTIME *ftime);

    ULONG    wpQueryLastWrite(FDATE *fdate,
		FTIME *ftime);

    ULONG    wpQueryFileSize();

    ULONG    wpQueryEASize();

    ULONG    wpSetDateInfo(FILEFINDBUF4 *pstFileFindBuf);

    ULONG    wpSetFileSizeInfo(ULONG cbFileSize,
		ULONG cbEASize);

    BOOL    wpRefresh(ULONG ulView,
		PVOID pReserved);

    ULONG    wpQueryRefreshFlags();

    BOOL    wpSetRefreshFlags(ULONG ulRefreshFlags);

    BOOL    wpPrintPlainTextFile(PPRINTDEST pPrintDest);

    BOOL    wpSetTitleAndRenameFile(PSZ pszNewTitle,
		ULONG fConfirmations);

    ULONG    wpConfirmRenameFileWithExt();

    ULONG    wpVerifyUpdateAccess();

    BOOL    wpAddUserItemsToPopupMenu(HWND hwndMenu,
		HWND hwndCnr,
		ULONG iPosition);

    override wpUnInitData;

    -- From WPObject

    override wpQueryHandle;

    -- From WPObject

    override wpSaveImmediate;

    -- From WPObject

    override wpFilterPopupMenu;

    -- From WPObject

    override wpSetTitle;

    -- From WPObject

    override wpViewObject;

    -- From WPObject

    override wpSwitchTo;

    -- From WPObject

    override wpAddSettingsPages;

    -- From WPObject

    override wpCopyObject;

    -- From WPObject

    override wpCreateFromTemplate;

    -- From WPObject

    override wpMoveObject;

    -- From WPObject

    override wpQueryIconData;

    -- From WPObject

    override wpSetIconData;

    -- From WPObject

    override wpQueryDetailsData;

    -- From WPObject

    override wpModifyPopupMenu;

    -- From WPObject

    override wpSaveState;

    -- From WPObject

    override wpRestoreState;

    -- From WPObject

    override wpMenuItemSelected;

    -- From WPObject

    override wpOpen;

    -- From WPObject

    override wpDraggedOverObject;

    -- From WPObject

    override wpDroppedOnObject;

    -- From WPObject

    override wpFormatDragItem;

    -- From WPObject

    override wpQueryNameClashOptions;

    -- From WPObject

    override wpAppendObject;

    -- From WPObject

    override wpReplaceObject;

    -- From WPObject

    override wpQueryStyle;

    -- From WPObject

    override wpSetStyle;

    -- From WPObject

    WPObject *   wpclsQueryObjectFromPath(PSZ pszFQPath), class;

    PSZ    wpclsQueryInstanceType(), class;

    PSZ    wpclsQueryInstanceFilter(), class;

    BOOL    wpQueryRealName(PSZ pszFilename,
		PULONG pcb,
		BOOL fQualified);

    override wpclsInitData, class;

    -- From WPObject

    override wpclsQueryTitle, class;

    -- From WPObject

    override wpclsQueryDetailsInfo, class;

    -- From WPObject

    override wpclsQuerySearchInfo, class;

    -- From WPObject

    override wpDoesObjectMatch;

    -- From WPObject

    override wpclsQueryExtendedCriteria, class;

    -- From WPObject

