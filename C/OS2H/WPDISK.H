
/*
 * This file was generated by the SOM Compiler.
 * FileName: wpdisk.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

/*
 * 
 *  Module Header
 * 
 *  Module Name: WPDISK
 * 
 *  OS/2 Presentation Manager Workplace class definitions
 * 
 *  Copyright (c) International Business Machines Corporation 1991, 1992
 * 
 */


#ifndef wpdisk_h
#define wpdisk_h


/*
 * Passthru lines: File: "C.h", "before"
 */
#ifndef WPRootFolder
    #define WPRootFolder SOMAny
    #endif

    #define OPEN_AUTO            120

#include <som.h>

/*
 * Define the class name as an object type
 */
#ifndef WPDisk
#define WPDisk SOMAny
#endif
#include "wpabs.h"

#define WPDisk_MajorVersion 1
#define WPDisk_MinorVersion 2

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define WPDiskNewClass wpdskc
#pragma linkage(wpdskc, system)
#define WPDiskClassData wpdskd
#define WPDiskCClassData wpdskx
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define WPDisk_classObj WPDiskClassData.classObject
#define _WPDisk WPDisk_classObj

/*
 * New and Renew macros for WPDisk
 */
#define _WPDiskNew() (_somNew(WPDiskClassData.classObject))
#define WPDiskNew() \
	( WPDiskClassData.classObject \
		? _WPDiskNew() \
		: ( WPDiskNewClass(WPDisk_MajorVersion, WPDisk_MinorVersion), _WPDiskNew() ) )
#define WPDiskRenew(buf) \
	( _somRenew(WPDiskClassData.classObject, buf) )

/*
 * Override method: wpSetup
 */
#define WPDisk_wpSetup(somSelf,pszSetupString) \
	WPObject_wpSetup(somSelf,pszSetupString)

/*
 * Override method: wpSaveState
 */
#define WPDisk_wpSaveState(somSelf) \
	WPObject_wpSaveState(somSelf)

/*
 * Override method: wpRestoreState
 */
#define WPDisk_wpRestoreState(somSelf,ulReserved) \
	WPObject_wpRestoreState(somSelf,ulReserved)

/*
 * Override method: wpAddSettingsPages
 */
#define WPDisk_wpAddSettingsPages(somSelf,hwndNotebook) \
	WPObject_wpAddSettingsPages(somSelf,hwndNotebook)

/*
 * Override method: wpFilterPopupMenu
 */
#define WPDisk_wpFilterPopupMenu(somSelf,ulFlags,hwndCnr,fMultiSelect) \
	WPObject_wpFilterPopupMenu(somSelf,ulFlags,hwndCnr,fMultiSelect)

/*
 * Override method: wpModifyPopupMenu
 */
#define WPDisk_wpModifyPopupMenu(somSelf,hwndMenu,hwndCnr,iPosition) \
	WPObject_wpModifyPopupMenu(somSelf,hwndMenu,hwndCnr,iPosition)

/*
 * Override method: wpMenuItemHelpSelected
 */
#define WPDisk_wpMenuItemHelpSelected(somSelf,MenuId) \
	WPObject_wpMenuItemHelpSelected(somSelf,MenuId)

/*
 * Override method: wpMenuItemSelected
 */
#define WPDisk_wpMenuItemSelected(somSelf,hwndFrame,ulMenuId) \
	WPObject_wpMenuItemSelected(somSelf,hwndFrame,ulMenuId)

/*
 * Override method: wpSetTitle
 */
#define WPDisk_wpSetTitle(somSelf,pszNewTitle) \
	WPObject_wpSetTitle(somSelf,pszNewTitle)

/*
 * Override method: wpOpen
 */
#define WPDisk_wpOpen(somSelf,hwndCnr,ulView,param) \
	WPObject_wpOpen(somSelf,hwndCnr,ulView,param)

/*
 * Override method: wpQueryDefaultHelp
 */
#define WPDisk_wpQueryDefaultHelp(somSelf,pHelpPanelId,HelpLibrary) \
	WPObject_wpQueryDefaultHelp(somSelf,pHelpPanelId,HelpLibrary)

/*
 * Override method: wpDragOver
 */
#define WPDisk_wpDragOver(somSelf,hwndCnr,pdrgInfo) \
	WPObject_wpDragOver(somSelf,hwndCnr,pdrgInfo)

/*
 * Override method: wpDrop
 */
#define WPDisk_wpDrop(somSelf,hwndCnr,pdrgInfo,pdrgItem) \
	WPObject_wpDrop(somSelf,hwndCnr,pdrgInfo,pdrgItem)

/*
 * Override method: wpQueryIconData
 */
#define WPDisk_wpQueryIconData(somSelf,pIconInfo) \
	WPObject_wpQueryIconData(somSelf,pIconInfo)

/*
 * Override method: wpSetIconData
 */
#define WPDisk_wpSetIconData(somSelf,pIconInfo) \
	WPObject_wpSetIconData(somSelf,pIconInfo)

/*
 * Override method: wpViewObject
 */
#define WPDisk_wpViewObject(somSelf,hwndCnr,ulView,param) \
	WPObject_wpViewObject(somSelf,hwndCnr,ulView,param)

/*
 * New Method: wpAddDiskDetailsPage
 */
typedef ULONG    SOMLINK somTP_WPDisk_wpAddDiskDetailsPage(WPDisk *somSelf,
		HWND hwndNotebook);
#pragma linkage(somTP_WPDisk_wpAddDiskDetailsPage, system)
typedef somTP_WPDisk_wpAddDiskDetailsPage *somTD_WPDisk_wpAddDiskDetailsPage;
#define somMD_WPDisk_wpAddDiskDetailsPage "----"
#define WPDisk_wpAddDiskDetailsPage(somSelf,hwndNotebook) \
    (SOM_Resolve(somSelf, WPDisk, wpAddDiskDetailsPage) \
	(somSelf,hwndNotebook))
#define _wpAddDiskDetailsPage WPDisk_wpAddDiskDetailsPage

/*
 * New Method: wpQueryDriveLockStatus
 */
typedef ULONG    SOMLINK somTP_WPDisk_wpQueryDriveLockStatus(WPDisk *somSelf,
		PULONG pulLockStatus,
		PULONG pulLockCount);
#pragma linkage(somTP_WPDisk_wpQueryDriveLockStatus, system)
typedef somTP_WPDisk_wpQueryDriveLockStatus *somTD_WPDisk_wpQueryDriveLockStatus;
#define somMD_WPDisk_wpQueryDriveLockStatus "----"
#define WPDisk_wpQueryDriveLockStatus(somSelf,pulLockStatus,pulLockCount) \
    (SOM_Resolve(somSelf, WPDisk, wpQueryDriveLockStatus) \
	(somSelf,pulLockStatus,pulLockCount))
#define _wpQueryDriveLockStatus WPDisk_wpQueryDriveLockStatus

/*
 * New Method: wpEjectDisk
 */
typedef ULONG    SOMLINK somTP_WPDisk_wpEjectDisk(WPDisk *somSelf);
#pragma linkage(somTP_WPDisk_wpEjectDisk, system)
typedef somTP_WPDisk_wpEjectDisk *somTD_WPDisk_wpEjectDisk;
#define somMD_WPDisk_wpEjectDisk "----"
#define WPDisk_wpEjectDisk(somSelf) \
    (SOM_Resolve(somSelf, WPDisk, wpEjectDisk) \
	(somSelf))
#define _wpEjectDisk WPDisk_wpEjectDisk

/*
 * New Method: wpLockDrive
 */
typedef ULONG    SOMLINK somTP_WPDisk_wpLockDrive(WPDisk *somSelf,
		BOOL fLock);
#pragma linkage(somTP_WPDisk_wpLockDrive, system)
typedef somTP_WPDisk_wpLockDrive *somTD_WPDisk_wpLockDrive;
#define somMD_WPDisk_wpLockDrive "----"
#define WPDisk_wpLockDrive(somSelf,fLock) \
    (SOM_Resolve(somSelf, WPDisk, wpLockDrive) \
	(somSelf,fLock))
#define _wpLockDrive WPDisk_wpLockDrive

/*
 * New Method: wpQueryLogicalDrive
 */
typedef ULONG    SOMLINK somTP_WPDisk_wpQueryLogicalDrive(WPDisk *somSelf);
#pragma linkage(somTP_WPDisk_wpQueryLogicalDrive, system)
typedef somTP_WPDisk_wpQueryLogicalDrive *somTD_WPDisk_wpQueryLogicalDrive;
#define somMD_WPDisk_wpQueryLogicalDrive "----"
#define WPDisk_wpQueryLogicalDrive(somSelf) \
    (SOM_Resolve(somSelf, WPDisk, wpQueryLogicalDrive) \
	(somSelf))
#define _wpQueryLogicalDrive WPDisk_wpQueryLogicalDrive

/*
 * New Method: wpQueryRootFolder
 */
typedef WPRootFolder *   SOMLINK somTP_WPDisk_wpQueryRootFolder(WPDisk *somSelf);
#pragma linkage(somTP_WPDisk_wpQueryRootFolder, system)
typedef somTP_WPDisk_wpQueryRootFolder *somTD_WPDisk_wpQueryRootFolder;
#define somMD_WPDisk_wpQueryRootFolder "----"
#define WPDisk_wpQueryRootFolder(somSelf) \
    (SOM_Resolve(somSelf, WPDisk, wpQueryRootFolder) \
	(somSelf))
#define _wpQueryRootFolder WPDisk_wpQueryRootFolder

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK WPDiskNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(WPDiskNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct WPDiskClassDataStructure {
	SOMAny *classObject;
	somMToken wpAddDiskDetailsPage;
	somMToken wpSetCorrectDiskIcon;
	somMToken wpQueryLogicalDrive;
	somMToken wpSetLogicalDrive;
	somMToken wpQueryRootFolder;
	somMToken wpSetDiskInfo;
	somMToken wpTouchDisk;
	somMToken wpQueryDiskInfo;
	somMToken wpQueryDriveLockStatus;
	somMToken wpEjectDisk;
	somMToken wpLockDrive;
} WPDiskClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct WPDiskCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} WPDiskCClassData;

#endif       /* wpdisk_h */

/*
 * This file was generated by the SOM Compiler.
 * FileName: wpdisk.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

#ifndef wpdisk_mh
#define wpdisk_mh


/*
 * Define the class name as an object type
 */
#ifndef M_WPDisk
#define M_WPDisk SOMAny
#endif

#define M_WPDisk_MajorVersion 1
#define M_WPDisk_MinorVersion 2

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define M_WPDiskNewClass wpdskc
#pragma linkage(wpdskc, system)
#define M_WPDiskClassData wpdskd
#define M_WPDiskCClassData wpdskx
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define M_WPDisk_classObj M_WPDiskClassData.classObject
#define _M_WPDisk M_WPDisk_classObj

/*
 * New and Renew macros for M_WPDisk
 */
#define _M_WPDiskNew() (_somNew(M_WPDiskClassData.classObject))
#define M_WPDiskNew() \
	( M_WPDiskClassData.classObject \
		? _M_WPDiskNew() \
		: ( M_WPDiskNewClass(M_WPDisk_MajorVersion, M_WPDisk_MinorVersion), _M_WPDiskNew() ) )
#define M_WPDiskRenew(buf) \
	( _somRenew(M_WPDiskClassData.classObject, buf) )

/*
 * Override method: wpclsQueryDefaultHelp
 */
#define M_WPDisk_wpclsQueryDefaultHelp(somSelf,pHelpPanelId,pszHelpLibrary) \
	M_WPObject_wpclsQueryDefaultHelp(somSelf,pHelpPanelId,pszHelpLibrary)

/*
 * Override method: wpclsQueryIconData
 */
#define M_WPDisk_wpclsQueryIconData(somSelf,pIconInfo) \
	M_WPObject_wpclsQueryIconData(somSelf,pIconInfo)

/*
 * Override method: wpclsQueryStyle
 */
#define M_WPDisk_wpclsQueryStyle(somSelf) \
	M_WPObject_wpclsQueryStyle(somSelf)

/*
 * Override method: wpclsQueryTitle
 */
#define M_WPDisk_wpclsQueryTitle(somSelf) \
	M_WPObject_wpclsQueryTitle(somSelf)

/*
 * Override method: wpclsQueryDefaultView
 */
#define M_WPDisk_wpclsQueryDefaultView(somSelf) \
	M_WPObject_wpclsQueryDefaultView(somSelf)

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK M_WPDiskNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(M_WPDiskNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct M_WPDiskClassDataStructure {
	SOMAny *classObject;
} M_WPDiskClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct M_WPDiskCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} M_WPDiskCClassData;

#endif       /* wpdisk_h */
