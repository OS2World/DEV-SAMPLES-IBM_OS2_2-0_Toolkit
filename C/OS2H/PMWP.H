/****************************** Module Header ******************************\
*
* Module Name: PMWP.H
*
* OS/2 Presentation Manager Workplace include file.
*
* Copyright (c) International Business Machines Corporation 1981, 1988-1992
*
* ===========================================================================
*
* The folowing symbols are used in this file for conditional sections.
*
*   #define:                To include:
*
*   INCL_WINWORKPLACE       All of Workplace Shell
*   INCL_WPCLASS            Workplace object class API's
*
* ===========================================================================
*
* Comments at the end of each typedef line give the name tags used in
* the assembler include version of this file.
*
* The assembler include version of this file excludes lines between NOINC
* and INC comments.
*
\***************************************************************************/

#ifdef __IBMC__
   #pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( suspend )
   #endif
   #pragma checkout( resume )
#endif

/* NOINC */
#ifndef PMWP_INCLUDED  /* multiple include protection */
   /* INC */
   #define PMWP_INCLUDED
   
   #ifdef INCL_WINWORKPLACE
      #define INCL_WPCLASS
   #endif
   
   /*** Common types *******************************************************/
   
   typedef LHANDLE HOBJECT;
   
   /*** Object management calls ********************************************/
   #if (defined(INCL_WPCLASS) || !defined(INCL_NOCOMMON))
      /*** Standard object classes *****************************************/
      
      
      #define CCHMAXCLASS              3      /* Length of a classname     */
      
      #define QC_First                 0      /* Codes for OA_QueryContent */
      #define QC_Next                  1
      #define QC_Last                  2
      #define QC_FIRST              QC_First
      #define QC_NEXT               QC_Next
      #define QC_LAST               QC_Last
      
      /*** An object's appearance (icon or bitmap or outline) **************/
      
      typedef struct _OBJECTIMAGE     /* oimg */
      {
         HPOINTER hptrObject;
      } OBJECTIMAGE;
      typedef OBJECTIMAGE *POBJECTIMAGE;
      
      /*** Class info structure returned by WinEnumObjectClasses ***********/
      typedef struct _OBJCLASS         /* ocls */
      {
         struct _OBJCLASS *pNext;         /* Null for the last structure.. */
         PSZ               pszClassName;  /* Class name                    */
         PSZ               pszModName;    /* Module name                   */
      } OBJCLASS;
      typedef OBJCLASS *POBJCLASS;
      
      
      /*** Workplace object management functions ***************************/
      
      BOOL APIENTRY WinRegisterObjectClass(PSZ pszClassName,
                                           PSZ pszModName);
      
      BOOL APIENTRY WinDeregisterObjectClass(PSZ pszClassName);
      
      BOOL APIENTRY WinReplaceObjectClass(PSZ pszOldClassName,
                                          PSZ pszNewClassName,
                                          BOOL fReplace);
      
      BOOL APIENTRY WinEnumObjectClasses(POBJCLASS pObjClass,
                                         PULONG pulSize);
      
      HOBJECT APIENTRY WinCreateObject(PSZ pszClassName,
                                       PSZ pszTitle,
                                       PSZ pszSetupString,
                                       PSZ pszLocation,
                                       ULONG ulFlags );
      #define CO_FAILIFEXISTS     0
      #define CO_REPLACEIFEXISTS  1
      #define CO_UPDATEIFEXISTS   2
      
      BOOL APIENTRY WinSetObjectData(HOBJECT hObject,
                                     PSZ pszSetupString);
      
      BOOL APIENTRY WinDestroyObject(HOBJECT hObject);
      
      HOBJECT APIENTRY WinQueryObject(PSZ pszObjectID);
      
   #endif  /*WPCLASS*/
   
   /*** Error codes ********************************************************/
   #define INCL_WPERRORS
   #include <pmerr.h>
   
   /*** Object settings notebook page insertion structure ******************/
   
   typedef struct _PAGEINFO     /* pginf */
   {
      ULONG   cb;
      HWND    hwndPage;
      PFNWP   pfnwp;
      ULONG   resid;
      PVOID   pCreateParams;
      USHORT  dlgid;
      USHORT  usPageStyleFlags;
      USHORT  usPageInsertFlags;
      USHORT  usSettingsFlags;
      PSZ     pszName;
      USHORT  idDefaultHelpPanel;
      USHORT  usReserved2;
      PSZ     pszHelpLibraryName;
      PUSHORT pHelpSubtable;   /* PHELPSUBTABLE when PMHELP.H is included*/
      HMODULE hmodHelpSubtable;
      ULONG   ulPageInsertId;
   } PAGEINFO;
   typedef PAGEINFO *PPAGEINFO;
   
   #define  SETTINGS_PAGE_NUMBERS     0x01
   
   /*** Utility apis +******************************************************/
   
   #if (!defined(INCL_NOCOMMON))
      typedef struct _ICONPOS     /* icp */
      {
         POINTL  ptlIcon;                    /* Location */
         CHAR    szIdentity[1];              /* Object identity string */
      } ICONPOS;
      typedef ICONPOS *PICONPOS;
      
      /*********************************************************************/
      #ifdef INCL_WINPOINTERS
         BOOL APIENTRY WinSetFileIcon(PSZ pszFileName,
                                      PICONINFO pIcnInfo);
      #endif
      BOOL APIENTRY WinFreeFileIcon(HPOINTER hptr);
      
      HPOINTER APIENTRY WinLoadFileIcon(PSZ pszFileName,
                                        BOOL fPrivate);
      
      BOOL APIENTRY WinStoreWindowPos(PSZ pszAppName,
                                      PSZ pszKeyName,
                                      HWND hwnd);
      
      BOOL APIENTRY WinRestoreWindowPos(PSZ pszAppName,
                                        PSZ pszKeyName,
                                        HWND hwnd);
      
      BOOL APIENTRY WinShutdownSystem(HAB hab,
                                      HMQ hmq);
   #endif
   
   /* NOINC */
#endif /* PMWP_INCLUDED */
/* INC */

#ifdef __IBMC__
   #pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( resume )
   #endif
   #pragma checkout( resume )
#endif

/**************************** end of file **********************************/
