
/*
 * This file was generated by the SOM Compiler.
 * FileName: wpptr.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

/*
 * 
 *  Module Header
 * 
 *  Module Name: WPPTR
 * 
 *  OS/2 Presentation Manager Workplace class definitions
 * 
 *  Copyright (c) International Business Machines Corporation 1991, 1992
 * 
 */


#ifndef wpptr_h
#define wpptr_h


#include <som.h>

/*
 * Define the class name as an object type
 */
#ifndef WPPointer
#define WPPointer SOMAny
#endif
#include "wpdataf.h"

#define WPPointer_MajorVersion 1
#define WPPointer_MinorVersion 2

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define WPPointerNewClass wpptrc
#pragma linkage(wpptrc, system)
#define WPPointerClassData wpptrd
#define WPPointerCClassData wpptrx
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define WPPointer_classObj WPPointerClassData.classObject
#define _WPPointer WPPointer_classObj

/*
 * New and Renew macros for WPPointer
 */
#define _WPPointerNew() (_somNew(WPPointerClassData.classObject))
#define WPPointerNew() \
	( WPPointerClassData.classObject \
		? _WPPointerNew() \
		: ( WPPointerNewClass(WPPointer_MajorVersion, WPPointer_MinorVersion), _WPPointerNew() ) )
#define WPPointerRenew(buf) \
	( _somRenew(WPPointerClassData.classObject, buf) )

/*
 * Override method: wpSetup
 */
#define WPPointer_wpSetup(somSelf,pszSetupString) \
	WPObject_wpSetup(somSelf,pszSetupString)

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK WPPointerNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(WPPointerNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct WPPointerClassDataStructure {
	SOMAny *classObject;
} WPPointerClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct WPPointerCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} WPPointerCClassData;

#endif       /* wpptr_h */

/*
 * This file was generated by the SOM Compiler.
 * FileName: wpptr.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

#ifndef wpptr_mh
#define wpptr_mh


/*
 * Define the class name as an object type
 */
#ifndef M_WPPointer
#define M_WPPointer SOMAny
#endif

#define M_WPPointer_MajorVersion 1
#define M_WPPointer_MinorVersion 2

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define M_WPPointerNewClass wpptrc
#pragma linkage(wpptrc, system)
#define M_WPPointerClassData wpptrd
#define M_WPPointerCClassData wpptrx
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define M_WPPointer_classObj M_WPPointerClassData.classObject
#define _M_WPPointer M_WPPointer_classObj

/*
 * New and Renew macros for M_WPPointer
 */
#define _M_WPPointerNew() (_somNew(M_WPPointerClassData.classObject))
#define M_WPPointerNew() \
	( M_WPPointerClassData.classObject \
		? _M_WPPointerNew() \
		: ( M_WPPointerNewClass(M_WPPointer_MajorVersion, M_WPPointer_MinorVersion), _M_WPPointerNew() ) )
#define M_WPPointerRenew(buf) \
	( _somRenew(M_WPPointerClassData.classObject, buf) )

/*
 * Override method: wpclsQueryInstanceFilter
 */
#define M_WPPointer_wpclsQueryInstanceFilter(somSelf) \
	M_WPFileSystem_wpclsQueryInstanceFilter(somSelf)

/*
 * Override method: wpclsQueryInstanceType
 */
#define M_WPPointer_wpclsQueryInstanceType(somSelf) \
	M_WPFileSystem_wpclsQueryInstanceType(somSelf)

/*
 * Override method: wpclsInitData
 */
#define M_WPPointer_wpclsInitData(somSelf) \
	M_WPObject_wpclsInitData(somSelf)

/*
 * Override method: wpclsQueryTitle
 */
#define M_WPPointer_wpclsQueryTitle(somSelf) \
	M_WPObject_wpclsQueryTitle(somSelf)

/*
 * Override method: wpclsQueryDefaultHelp
 */
#define M_WPPointer_wpclsQueryDefaultHelp(somSelf,pHelpPanelId,pszHelpLibrary) \
	M_WPObject_wpclsQueryDefaultHelp(somSelf,pHelpPanelId,pszHelpLibrary)

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK M_WPPointerNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(M_WPPointerNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct M_WPPointerClassDataStructure {
	SOMAny *classObject;
} M_WPPointerClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct M_WPPointerCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} M_WPPointerCClassData;

#endif       /* wpptr_h */
