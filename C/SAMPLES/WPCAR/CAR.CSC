/******************************************************************************
*
*  Module Name: CAR
*
*  OS/2 Work Place Shell Sample Program
*
*  Copyright (C) 1992 IBM Corporation
*
*      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is
*      sample code created by IBM Corporation. This sample code is not
*      part of any standard or IBM product and is provided to you solely
*      for  the purpose of assisting you in the development of your
*      applications.  The code is provided "AS IS", without
*      warranty of any kind.  IBM shall not be liable for any damages
*      arising out of your use of the sample code, even if they have been
*      advised of the possibility of such damages.                                                    *
*
******************************************************************************/

###   Note: The header preceding this comment will be emitted in all files.
###
###         Any comments to go public should be preceded with '--'
###         Any comments to remain private should be preceded with '#'

#******************************************************************************
#   Include the class definition file for the parent class
#******************************************************************************

include <wpdataf.sc>

#******************************************************************************
#   Define the new class
#******************************************************************************

class: Car,
       external stem   = car,
       local,
       external prefix = car_,
       classprefix     = carM_,
       major version   = 1,
       minor version   = 2;

--
-- CLASS: Car
--
-- CLASS HIERARCHY:
--
--     SOMObject
--       ÀÄÄ WPObject
--             ÀÄÄ WPFileSystem
--                   ÀÄÄ WPDataFile
--                         ÀÄÄ  Car
--
-- DESCRIPTION:
--
--    This is the sample car object class.
--
--    An instance of this class can be created as a Workplace object.
--

#******************************************************************************
#   Specify the parent class
#******************************************************************************

parent: WPDataFile;

#******************************************************************************
#   Specify the release order of new methods.  This ensures binary
#   compatability if we change the order of our methods in .c and .csc files.
#******************************************************************************

release order:
              QueryBrakes,
              SetBrakes,
              QueryDuration,
              SetDuration,
              QueryHighTone,
              SetHighTone,
              QueryLowTone,
              SetLowTone,
              QuerySpeed,
              SetSpeed,
              BeepHorn,
              AddDashboardPage,
              AddHornBeepPage,
              clsQueryModuleHandle,
              TrapTest;

#******************************************************************************
#   Passthru PRIVATE definitions to the .ph file
#******************************************************************************

passthru: C.ph;

   /*
    *   The following structures will be used to store window specific data
    *   and a pointer to the object that created the window/dialog.
    *
    *   They're allocated when the Client window is created.  This
    *   allows us to pass the *somSelf pointer and use it in our
    *   window and dialog procedures (the system only passes this
    *   pointer to methods).
    */
   typedef struct _WINDOWDATA
   {
      USHORT   cb;            /* size of this structure */
      Car     *somSelf;       /* pointer to this instance */
      USEITEM  UseItem;       /* global class usage information */
      VIEWITEM ViewItem;      /* global class view information */
      LONG     x;             /* x position of car in open view */
      LONG     y;             /* y position of car in open view */
      LONG     xDir;          /* x direction (CAR_LEFT or CAR_RIGHT) */
      LONG     yDir;          /* y direction (CAR_UP or CAR_DOWN) */
   } WINDOWDATA;
   typedef WINDOWDATA *PWINDOWDATA;

   /*
    *   Window data for the Dashboard dialog (settings page)
    */
   typedef struct _DASHDLGDATA
   {
      USHORT   cb;            /* size of this structure */
      Car    *somSelf;        /* pointer to this instance         */
      BOOL    PrevBrakes;     /* indicates if car is stopped      */
      ULONG   PrevSpeed;      /* Speed car moves across screen    */
   } DASHDLGDATA;
   typedef DASHDLGDATA *PDASHDLGDATA;

   /*
    *   Window data for the Horn dialog (settings page)
    */
   typedef struct _HORNDLGDATA
   {
      USHORT   cb;            /* size of this structure */
      Car    *somSelf;        /* pointer to this instance         */
      ULONG   PrevDuration;   /* Duration of the car's horn beep  */
      ULONG   PrevHighTone;   /* The high note of the car beep    */
      ULONG   PrevLowTone;    /* The low note of the car beep     */
   } HORNDLGDATA;
   typedef HORNDLGDATA *PHORNDLGDATA;

   /*
    *   These defines are used as directional multipliers against x,y position.
    */
   #define CAR_LEFT  -1
   #define CAR_RIGHT  1
   #define CAR_DOWN  -1
   #define CAR_UP     1

   #define ICON_WIDTH   32     /* pels */
   #define ICON_HEIGHT  32     /* pels */

   /*
    *   Private Debug helpers go here.  They can be enabled/disabled by
    *   defining DEBUG as a compiler directive.
    */
   #if defined(DEBUG)

      #define DebugBox(title, text) \
                                    \
                 WinMessageBox(     \
                    HWND_DESKTOP,   \
                    HWND_DESKTOP,   \
                    (PSZ) text,     \
                    (PSZ) title,    \
                    20,             \
                    MB_OK | MB_INFORMATION | MB_MOVEABLE)
   #else
      #define DebugBox(title, text)   /* do nothing if not debugging */
   #endif

endpassthru;   /* C.ph */

#******************************************************************************
#   Passthru IMPLEMENTATION definitions to the .ih file
#******************************************************************************

passthru: C.ih;

   #define INCL_WIN
   #define INCL_DOS
   #define INCL_GPIBITMAPS
   #define INCL_DOSERRORS
   #include <os2.h>

   #define INCL_WPCLASS
   #define INCL_WPFOLDER

   #include <pmwp.h>

   #define ID_TITLE           100
   #define ID_ICON            101

   #define IDD_DASHBOARD      200                  /* settings page (dialog) */
   #define IDD_HORNBEEP       202

   /*
    *   The following user-defined Popup menu items (ID_xxx) should be higher
    *   than WPMENUID_USER.
    *
    *   The ID_OPENMENU will become a submenu of the system's popup open menu
    *   id, WPMENUID_OPEN.
    */
   #define ID_BEEPMENU        (WPMENUID_USER+1) /* menus added to popup menu */
   #define ID_OPENMENU        (WPMENUID_USER+2)
   #define ID_TRAPMENU        (WPMENUID_USER+3)

   #define IDM_OPENCAR        (WPMENUID_USER+4) /* submenus of added menus */
   #define IDM_BEEPHORN       (WPMENUID_USER+5)
   #define IDM_TRAPCAR        (WPMENUID_USER+6)

   #define IDMSG_ACCESS_VIOLATION  100
   #define IDM_MSGBOX              999

   #define ID_FRAME           3000                       /* client window id */
   #define ID_CLIENT          3001                       /* client window id */

   /*
    *   Set unique view ids.
    */
   #define OPEN_CAR           ID_OPENMENU

   #define CAR_TIMER          1001                               /* timer id */

   /*
    *   IDs of dialog items in CAR.RC
    */
   #define ID_UNDO            801
   #define ID_DEFAULT         802
   #define ID_HELP            803
   #define ID_HITONE          804
   #define ID_LOTONE          805
   #define ID_SPEEDSLIDER     806
   #define ID_STOP            807
   #define ID_SPEEDDATA       808
   #define ID_GO              809

   /*
    *  Keys for save-restore methods
    */
   #define IDKEY_HITONE       1
   #define IDKEY_LOTONE       2
   #define IDKEY_DURATION     3
   #define IDKEY_SPEED        4
   #define IDKEY_BRAKEFLAG    5

   /*
    *   Default values of instance data items
    */
   #define DEFAULT_DURATION   300
   #define DEFAULT_HITONE     400
   #define DEFAULT_LOTONE     400
   #define DEFAULT_SPEED      50
   #define DEFAULT_BRAKEFLAG  FALSE

   /*
    *   Help IDs
    *
    *   NOTE:  At this time, no source file is provided to build help for this
    *   sample.  A pre-built help file, CAR.HLP, is provided containing the
    *   following help ids.
    */
   #define ID_HELP_DEFAULT    256
   #define ID_HELP_DASHBOARD  257
   #define ID_HELP_OPENCAR    258
   #define ID_HELP_HORNBEEP   259
   #define ID_HELP_BEEPHORN   260

   /*
    *   Indexes into CARDETAILS information. (arrays)
    */
   #define  INDEX_MAKE         0
   #define  INDEX_MODEL        1
   #define  INDEX_COLOR        2
   #define  INDEX_SALE_DATE    3
   #define  INDEX_PRICE        4

   /*
    *   CARDETAILS:  Structure used for details view
    */
   typedef struct _CARDETAILS
   {
      PSZ     pszMake;     /* Manufacturer      */
      PSZ     pszModel;    /* Model             */
      PSZ     pszColor;    /* Color of car      */
      CDATE   cdateSale;   /* Date of sale      */
      ULONG   ulPrice;     /* Price in dollars  */
   } CARDETAILS;
   typedef CARDETAILS *PCARDETAILS;

endpassthru;   /* .ih */

#******************************************************************************
#   Passthru PUBLIC definitions to the .h file
#******************************************************************************

passthru: C.h, after;


endpassthru;   /* C.h */

#******************************************************************************
#   Define instance data
#******************************************************************************

data:

   BOOL    BrakeFlag;                       /* indicates if car is stopped */
   ULONG   duration;                        /* Duration of the car's horn */
   ULONG   HighTone;                        /* The high note of the beep */
   ULONG   LowTone;                         /* The low note of the beep */
   ULONG   speed;                           /* Speed car moves across screen */

#******************************************************************************
#   Define methods
#******************************************************************************

methods:

BOOL QueryBrakes();
--
-- METHOD: QueryBrakes                                    ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Query state of car's brakes
--
-- RETURN:
--
--   TRUE           Brake is on
--   FALSE          Brake is off
--

VOID SetBrakes(BOOL fBrake);
--
-- METHOD: SetBrakes                                      ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Put on the brakes
--

ULONG QueryDuration();
--
-- METHOD: QueryDuration                                  ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Query Duration of horn beep
--
-- RETURN:
--
--   ULONG          Duration of beep
--

VOID SetDuration(ULONG ulDuration);
--
-- METHOD: SetDuration                                    ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Set Duration of horn beep
--

ULONG QueryHighTone();
--
-- METHOD: QueryHighTone                                  ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Query HighTone of horn
--
-- RETURN:
--
--   ULONG          High frequency of horn
--

VOID SetHighTone(ULONG ulTone) ;
--
-- METHOD: SetHighTone                                    ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Set HighTone of horn
--

ULONG QueryLowTone();
--
-- METHOD: QueryLowTone                                   ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Query LowTone of horn
--
-- RETURN:
--
--   ULONG          High frequency of horn
--

VOID SetLowTone(ULONG ulTone) ;
--
-- METHOD: SetLowTone                                     ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Set LowTone of horn
--

ULONG QuerySpeed();
--
-- METHOD: QuerySpeed                                     ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Query Speed of car
--
-- RETURN:
--
--   ULONG          car speed
--

VOID SetSpeed(ULONG ulSpeed);
--
-- METHOD: SetSpeed                                       ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Set Speed of car
--

BOOL BeepHorn ();
--
-- METHOD: BeepHorn                                       ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Beep the car's horn.
--
-- RETURN:
--
--   TRUE           Successful
--   FALSE          Unsuccessful
--

ULONG AddDashboardPage (HWND hwndNotebook);
--
-- METHOD: AddDashboardPage                               ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   This method adds the dashboard page to the settings notebook.
--
-- RETURN:
--
--   0              Unsuccessful
--   ulPageId       Identifier for the inserted page
--
-- HOW TO OVERRIDE:
--
--   Method should always be overridden in order to replace or remove
--   the dashboard page from an object which is a descendent of Car.
--   In most cases, an override of this method will not call the parent.
--


ULONG AddHornBeepPage (HWND hwndNotebook);
--
-- METHOD: AddHornBeepPage                                ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   This method adds the horn beep page to the settings
--   notebook.
--
-- RETURN:
--
--   0              Unsuccessful
--   ulPageId       Identifier for the inserted page
--
-- HOW TO OVERRIDE:
--
--   Method should always be overridden in order to replace or remove
--   the horn beep page from an object which is a descendent of Car.
--   In most cases, an override of this method will not call the parent.
--


VOID TrapTest ();
--
-- METHOD: AddHornBeepPage                                ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   This method tests the exception handling in this sample.
--
-- RETURN:
--
--   nothing
--
-- HOW TO OVERRIDE:
--
--   n/a
--


#******************************************************************************
#   Specify methods being overridden
#******************************************************************************

-----------------------------------------------------------------------------
--   Methods from the WPObject class
-----------------------------------------------------------------------------

override wpInitData;
--
-- OVERRIDE: wpInitData                                   ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Initialize our state variables. Allocate any extra memory that
--   we might need.
--

override wpUnInitData;
--
-- OVERRIDE: wpUnInitData                                 ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Clear up memory that was allocated on wpInitData.
--

override wpSaveState;
--
-- METHOD: wpSaveState                                    ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Save our state variables (pitch and duration).
--

override wpRestoreState;
--
-- METHOD: wpRestoreState                                 ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Retrieve our saved state variables (pitch and duration).
--

override wpAddSettingsPages;
--
-- METHOD: wpAddSettingsPages                             ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Add our own settings page to let the user alter the pitch
--   and duration of the car's beep.
--

override wpFilterPopupMenu;
--
-- METHOD: wpFilterPopupMenu                              ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Filter out any options from the context that don't apply.
--
-- HOW TO OVERRIDE:
--
--   No restrictions.
--

override wpModifyPopupMenu;
--
-- METHOD: wpModifyPopupMenu                              ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Add our extra option to the context menu to beep the horn
--

override wpMenuItemSelected;
--
-- METHOD: wpMenuItemSelected                             ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Process input from the extra menu option that we added.
--

override wpMenuItemHelpSelected;
--
-- METHOD: wpMenuItemHelpSelected                         ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Process input from the extra menu option that we added.
--

override wpQueryDetailsData;
--
-- METHOD: wpQueryDetailsData                             ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Returns the car specific data for the details view of this object.
--   Sets the pointer (*ppDetailsData) to the beginning of the buffer
--   into which the data is written.
--

override wpOpen;
--
--  METHOD: wpOpen                                         ( ) PRIVATE
--                                                         (X) PUBLIC
--  DESCRIPTION:
--
--    Opens the car window.
--

override wpSetup;
--
-- METHOD: wpSetup                                        ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Specify Setup strings and do some initialization.  This method is
--   invoked once an object is completely created.
--

#******************************************************************************
#   Define class methods
#******************************************************************************

HMODULE  clsQueryModuleHandle (), class;
--
-- METHOD: clsQueryModuleHandle                           ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   This method returns the module handle of this class.  If this is the
--   first invocation, DosQueryModuleHandle is called to save the handle
--   for future invocations.
--
-- RETURN:
--
--   0              Unsuccessful
--   non-zero       module handle
--

#******************************************************************************
#   Specify class methods being overridden
#******************************************************************************

override wpclsInitData, class;
--
-- METHOD: wpclsInitData
--
-- DESCRIPTION:
--
--   Initalize the class data
--

override wpclsUnInitData, class;
--
-- METHOD: wpclsUnInitData
--
-- DESCRIPTION:
--
--   Free any class data
--

override wpclsQueryTitle, class;
--
-- METHOD: wpclsQueryTitle                                ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Return the string "New car".
--

override wpclsQueryIconData, class;
--
-- METHOD: wpclsQueryIconDdata                            ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Return the class icon
--

override wpclsQueryDefaultHelp, class;
--
-- METHOD: wpclsQueryDefaultHelp                          ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Process input from the extra menu option that we added.
--

override wpclsQueryDefaultView, class;
--
-- METHOD: wpclsQueryDefaultView                          ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Returns the default view for a new instance of this object.
--
-- REMARKS:
--
--   Tell the system what our default open view is...
--

override wpclsQueryDetailsInfo, class;
--
-- METHOD: wpclsQueryDetailsInfo                          ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--   Appends the car specific chain of FIELDINFO structures describing the
--   details data of this object to *ppDetailsData (if ppDetailsData
--   is NON-NULL).  In this case it also sets *ppDetailsData to the
--   head of the linked list.
--
--   Adds the number of bytes required by the details data for car to *pSize
--   (if pSize is NON-NULL).
--
-- REMARKS:
--
--   Add details data for this object.
--

    -- From WPFileSystem

override wpclsQueryDetails, class;
--
-- METHOD: wpclsQueryDetails                              ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--    Specify default details to display in details view
--
-- REMARKS:
--
--    A pointer details structure is modified and returned.
--    Note: this is purely virtual at the moment (parent class doesn't
--    do anything).
--

override wpclsQueryInstanceFilter, class;
--
-- METHOD: wpclsQueryInstanceFilter                       ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--    The wpclsQueryInstanceFilter method is called to allow the class
--    object to specify the file title filters for instances of its
--    class.
--
-- REMARKS:
--
--    A pointer to a string containing file title filter(s).  This
--    string can contain several file title filters separated by a
--    comma.  Example: "*.TXT, *.DOC"
--

override wpclsQueryStyle, class;
--
-- METHOD: wpclsQueryStyle                                ( ) PRIVATE
--                                                        (X) PUBLIC
-- DESCRIPTION:
--
--    The wpclsQueryStyle method is called to allow the class object
--    to specify the default object class style for its instances.
--
-- REMARKS:
--
--    This method can be called at any time in order to determine the
--    default style for instances of this class.
--
--    This method should be overridden in order to modify the default
--    object style for instances of this class.
--
