
/*
 * This file was generated by the SOM Compiler.
 * FileName: ..\..\ibmh\wpqdr.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

/*
 * 
 *  Module Header
 * 
 *  Module Name: WPQDR
 * 
 *  OS/2 Presentation Manager Workplace class definitions
 * 
 *  Copyright (c) International Business Machines Corporation 1991, 1992
 * 
 */


#ifndef wpqdr_h
#define wpqdr_h


#include <som.h>

/*
 * Define the class name as an object type
 */
#ifndef WPQdr
#define WPQdr SOMAny
#endif
#include "wptrans.h"

#define WPQdr_MajorVersion 1
#define WPQdr_MinorVersion 1

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define WPQdrNewClass WPqdrc
#pragma linkage(WPqdrc, system)
#define WPQdrClassData WPqdrd
#define WPQdrCClassData WPqdrx
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define WPQdr_classObj WPQdrClassData.classObject
#define _WPQdr WPQdr_classObj

/*
 * New and Renew macros for WPQdr
 */
#define _WPQdrNew() (_somNew(WPQdrClassData.classObject))
#define WPQdrNew() \
	( WPQdrClassData.classObject \
		? _WPQdrNew() \
		: ( WPQdrNewClass(WPQdr_MajorVersion, WPQdr_MinorVersion), _WPQdrNew() ) )
#define WPQdrRenew(buf) \
	( _somRenew(WPQdrClassData.classObject, buf) )

/*
 * Override method: wpInitData
 */
#define WPQdr_wpInitData(somSelf) \
	WPObject_wpInitData(somSelf)

/*
 * Override method: wpUnInitData
 */
#define WPQdr_wpUnInitData(somSelf) \
	WPObject_wpUnInitData(somSelf)

/*
 * Override method: somDumpSelfInt
 */
#define WPQdr_somDumpSelfInt(somSelf,level) \
	SOMObject_somDumpSelfInt(somSelf,level)

/*
 * Override method: wpAddSettingsPages
 */
#define WPQdr_wpAddSettingsPages(somSelf,hwndNotebook) \
	WPObject_wpAddSettingsPages(somSelf,hwndNotebook)

/*
 * Override method: wpQueryTitle
 */
#define WPQdr_wpQueryTitle(somSelf) \
	WPObject_wpQueryTitle(somSelf)

/*
 * Override method: wpQueryIcon
 */
#define WPQdr_wpQueryIcon(somSelf) \
	WPObject_wpQueryIcon(somSelf)

/*
 * Override method: wpFilterPopupMenu
 */
#define WPQdr_wpFilterPopupMenu(somSelf,ulFlags,hwndCnr,fMultiSelect) \
	WPObject_wpFilterPopupMenu(somSelf,ulFlags,hwndCnr,fMultiSelect)

/*
 * Override method: wpFree
 */
#define WPQdr_wpFree(somSelf) \
	WPObject_wpFree(somSelf)

/*
 * Override method: wpModifyPopupMenu
 */
#define WPQdr_wpModifyPopupMenu(somSelf,hwndMenu,hwndCnr,iPosition) \
	WPObject_wpModifyPopupMenu(somSelf,hwndMenu,hwndCnr,iPosition)

/*
 * Override method: wpMenuItemSelected
 */
#define WPQdr_wpMenuItemSelected(somSelf,hwndFrame,ulMenuId) \
	WPObject_wpMenuItemSelected(somSelf,hwndFrame,ulMenuId)

/*
 * Override method: wpMenuItemHelpSelected
 */
#define WPQdr_wpMenuItemHelpSelected(somSelf,MenuId) \
	WPObject_wpMenuItemHelpSelected(somSelf,MenuId)

/*
 * Override method: wpOpen
 */
#define WPQdr_wpOpen(somSelf,hwndCnr,ulView,param) \
	WPObject_wpOpen(somSelf,hwndCnr,ulView,param)

/*
 * Override method: wpDrop
 */
#define WPQdr_wpDrop(somSelf,hwndCnr,pdrgInfo,pdrgItem) \
	WPObject_wpDrop(somSelf,hwndCnr,pdrgInfo,pdrgItem)

/*
 * Override method: wpDragOver
 */
#define WPQdr_wpDragOver(somSelf,hwndCnr,pdrgInfo) \
	WPObject_wpDragOver(somSelf,hwndCnr,pdrgInfo)

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK WPQdrNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(WPQdrNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct WPQdrClassDataStructure {
	SOMAny *classObject;
	somMToken prtGetQDriverInfo;
	somMToken prtSetQDriverInfo;
	somMToken prtSetQdrIcon;
	somMToken prtSetQDriverDiscardhwndDlg;
	somMToken prtSetQDriverInstallhwndDlg;
} WPQdrClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct WPQdrCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} WPQdrCClassData;

#endif       /* wpqdr_h */

/*
 * This file was generated by the SOM Compiler.
 * FileName: ..\..\ibmh\wpqdr.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

#ifndef wpqdr_mh
#define wpqdr_mh


/*
 * Define the class name as an object type
 */
#ifndef M_WPQdr
#define M_WPQdr SOMAny
#endif

#define M_WPQdr_MajorVersion 1
#define M_WPQdr_MinorVersion 1

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define M_WPQdrNewClass WPqdrc
#pragma linkage(WPqdrc, system)
#define M_WPQdrClassData WPqdrd
#define M_WPQdrCClassData WPqdrx
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define M_WPQdr_classObj M_WPQdrClassData.classObject
#define _M_WPQdr M_WPQdr_classObj

/*
 * New and Renew macros for M_WPQdr
 */
#define _M_WPQdrNew() (_somNew(M_WPQdrClassData.classObject))
#define M_WPQdrNew() \
	( M_WPQdrClassData.classObject \
		? _M_WPQdrNew() \
		: ( M_WPQdrNewClass(M_WPQdr_MajorVersion, M_WPQdr_MinorVersion), _M_WPQdrNew() ) )
#define M_WPQdrRenew(buf) \
	( _somRenew(M_WPQdrClassData.classObject, buf) )

/*
 * Override method: wpclsQueryTitle
 */
#define M_WPQdr_wpclsQueryTitle(somSelf) \
	M_WPObject_wpclsQueryTitle(somSelf)

/*
 * Override method: wpclsQueryIcon
 */
#define M_WPQdr_wpclsQueryIcon(somSelf) \
	M_WPObject_wpclsQueryIcon(somSelf)

/*
 * Override method: wpclsQueryDefaultHelp
 */
#define M_WPQdr_wpclsQueryDefaultHelp(somSelf,pHelpPanelId,pszHelpLibrary) \
	M_WPObject_wpclsQueryDefaultHelp(somSelf,pHelpPanelId,pszHelpLibrary)

/*
 * Override method: wpclsQueryDefaultView
 */
#define M_WPQdr_wpclsQueryDefaultView(somSelf) \
	M_WPObject_wpclsQueryDefaultView(somSelf)

/*
 * Override method: wpclsQueryStyle
 */
#define M_WPQdr_wpclsQueryStyle(somSelf) \
	M_WPObject_wpclsQueryStyle(somSelf)

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK M_WPQdrNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(M_WPQdrNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct M_WPQdrClassDataStructure {
	SOMAny *classObject;
} M_WPQdrClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct M_WPQdrCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} M_WPQdrCClassData;

#endif       /* wpqdr_h */
