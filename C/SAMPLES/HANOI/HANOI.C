/*==============================================================*\
 *  HANOI.C - Sample PM application
 *
 *
 *      Copyright  1991  IBM Corp.                                         *
 *                                                                         *
 *      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        *
 *      sample code created by IBM Corporation. This sample code is not    *
 *      part of any standard or IBM product and is provided to you solely  *
 *      for  the purpose of assisting you in the development of your       *  
 *      applications.  The code is provided "AS IS", without               *
 *      warranty of any kind.  IBM shall not be liable for any damages     *
 *      arising out of your use of the sample code, even if they have been *
 *      advised of the possibility of   such damages.                      *                               *
 *--------------------------------------------------------------
 *
 *  This program implements a tower of hanoi program.  This
 *  sample app was written to demonstrate the use of a multi-
 *  threaded program.  The main thread handles the PM interface,
 *  the second thread is started to do the recursive execution
 *  of the hanoi algorithm.
 *
 *--------------------------------------------------------------
 *
 *  This source file contains the following functions:
 *      main(argc, *argv[]) - main routine
 *      MainWndProc(hwnd, msg, mp1, mp2) - main window procedure
 *      MainPaint(hwnd) - WM_PAINT processing of main
 *      MainCommand(mp1, mp2) - WM_COMMAND processing of main
 *      CalcThread() - Sets up and terminates the secondary thread
 *      DrawDisk(hps, cPole, bLevel, fDraw) - Draws or erases a disk
 *                                            from poles
 *      MoveDisk(hps, bFrom, bTo) - Moves a disk from one pole to another
 *      Hanoi(bHeight, bFrom, bTo, bTemp) - Recursive routine for tower
 *                                          of hanoi
 *      EnableMenuItem(hwnd, sMenuItem, fEnable) - Activates/deactivates
 *                                                 a menu choice
 *      EntryFldDlgProc(hwnd, msg, mp1, mp2) - Handles the set number of
 *                                             disks dialog box
 *      SetupTowers() - Sets up the global tower data
 *      FixSysMenu(hwndDlg) - Remove Restore, Size, Min, & Max from
 *                            system menu
 *      AboutDlgProc(hwnd, msg, mp1, mp2) - processing about dlg box
 *      ObjectWndProc(hwnd, msg, mp1, mp2)
 *      MessageBox(hwndOwner, IdMsg, fsStyle, fBeep) - processing all
 *                                                 message calling
 *      Init(VOID) - iniitializing the process
 *      ExitProc(VOID) - terminating the process
 *      CreateBackgroundThread(VOID) - process the background thread creating
 *      BackgroundThread(ulThreadParam) - handle the background thread process
 *      DestroyBackgroundThread(VOID) - destroy background thread process
 *      InitHelp(VOID) - initialize the help process
 *      HelpHelpForHelp(mp2) - processing the help for help message
 *      HelpExtended(mp2) - processing the help for extended message
 *      HelpKeys(mp2) - processing the help menu of keys
 *      HelpIndex(mp2) - processing the help index message
 *      HelpAbout(mp2) - processing the about dlg box message
 *      DisplayHelpPanel(idPanel) - processing the help pannel display
 *      DestroyHelpInstance(VOID) - destroy the help instance
 *      PostBkThreadMsg(msg, mp1, mp2) - handle the background thread meg.
 *
\*==============================================================*/
/*--------------------------------------------------------------*\
 *  Include files, macros, defined constants, and externs
\*--------------------------------------------------------------*/
#define INCL_WIN
#define INCL_HELP
#define INCL_WINHEAP
#define INCL_WINDIALOGS
#define INCL_WINWINDOWMGR
#define INCL_GPIPRIMITIVES
#define INCL_GPIBITMAPS
#define INCL_GPILCIDS
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES

#include <os2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hanoi.h"

/*--------------------------------------------------------------*\
 *  Global variables
\*--------------------------------------------------------------*/
CHAR   szClientClass[] = "Hanoi";
BYTE   abTowers[3][MAXDISKCNT];    /* Used to hold disk numbers on each post */
BYTE   abTowersNdx[3];             /* Current number of disks on each post */
BYTE   cTowerSize = DEFAULTSIZE;   /* Holds the total number of disks */
USHORT ausPolePos[3]= {POSTOFFSET, /* Holds offset drawing information */
                       POSTOFFSET + POSTSPACE,
                       POSTOFFSET + 2*POSTSPACE };
ULONG  ulIterations;
TID    tidCalcThread = 0L;                        /* Secondary thread ID */
BOOL   fContinueCalc;
HWND   hwndMainFrame=0L,              /* Handle to the main frame window */
       hwndMain;                     /* Handle to the main client window */
CHAR   szAppName[MAXNAMEL];        /* Buffer for application name string */
HAB    hab;                              /* Anchor block for the process */
HMQ    hmq;                      /* Handle to the process' message queue */
CHAR   szUntitled[MESSAGELEN];           /* buffer for "Untitled" string */
static BOOL fThreadCreated = FALSE;
static HEV hevThreadInit;         /* semaphore for thread initialization */
static HAB habBkThread;
static HMQ hmqBkThread;
static TID tidBkThread;
static HWND hwndObject;
static CHAR szObjectClass[MAXNAMEL];
BOOL   fHelpEnabled;             /* flag to determine if help is enabled */
static CHAR szLibName[HELPLIBRARYNAMELEN];
static CHAR szWindowTitle[HELPLIBRARYNAMELEN];
static HWND hwndHelpInstance;
BOOL   fViewOn=TRUE;                           /* flag to view on or off */
CHAR   *pszDisk       ="Disk Information";
CHAR   *pszDisksMoved ="Disks Moved:";

/*--------------------------------------------------------------*\
 *  Entry point declarations                                    *
\*--------------------------------------------------------------*/
MRESULT EXPENTRY MainWndProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY EntryFldDlgProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY AboutDlgProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY ObjectWndProc(HWND, ULONG, MPARAM, MPARAM);
LONG    MessageBox(HWND, LONG, LONG, BOOL);
VOID APIENTRY ExitProc(VOID);
BOOL Init(VOID);
VOID MainPaint(HWND);
LONG MainCommand(HWND, MPARAM, MPARAM);
VOID CalcThread(VOID);
VOID DrawDisk(HPS,BYTE,BYTE,BYTE);
VOID MoveDisk(HPS,BYTE,BYTE);
VOID Hanoi(BYTE, BYTE, BYTE, BYTE);
VOID EnableMenuItem(HWND, LONG, BOOL);
VOID SetupTowers(VOID);
VOID FixSysMenu(HWND);

BOOL CreateBackgroundThread(VOID);
VOID BackgroundThread(ULONG);
BOOL PostBkThreadMsg(ULONG, MPARAM, MPARAM);
VOID DestroyBackgroundThread(VOID);

VOID InitHelp(VOID);
VOID HelpHelpForHelp(MPARAM);
VOID HelpExtended(MPARAM);
VOID HelpKeys(MPARAM);
VOID HelpIndex(MPARAM);
VOID HelpAbout(MPARAM);
VOID DisplayHelpPanel(LONG);
VOID DestroyHelpInstance(VOID);

/****************************************************************\
 *  Main routine
 *--------------------------------------------------------------
 *
 *  Name:    main(argc, *argv[])
 *
 *  Purpose: Initializes the PM environment, calls the initialization
 *           routine, creates main window, and polls the message queue
 *
 *  Usage:
 *
 *  Method:  - obtains anchor block handle and creates message
 *             queue
 *           - calls the initialization routine
 *           - creates the main frame window which creates the
 *             main client window
 *           - polls the message queue via Get/Dispatch Msg loop
 *           - upon exiting the loop, performs exit housekeeping
 *             and then exits
 *
 *  Returns: 0 - if successful execution completed
 *           1 - if error
 *
\****************************************************************/
INT main(LONG argc, CHAR *argv[])
{
   QMSG     qmsg;                      /* Message structure */
   ULONG    flCtlData;                 /* Frame control data */
   LONG     sHold;

   /* If command line arg, use as the initial number of disks */
   if(argc > 1)  
   {
      sHold = (LONG)atoi(argv[1]);
      if(sHold>0 && sHold<=MAXDISKCNT)
      cTowerSize = (BYTE) sHold;
   }

   SetupTowers();

   hab = WinInitialize(0L);

   if(!hab)
   {
       DosBeep(BEEP_WARN_FREQ, BEEP_WARN_DUR);
       return(RETURN_ERROR);
   }

   hmq = WinCreateMsgQueue(hab, 0L);

   if(!hmq)
   {
       DosBeep(BEEP_WARN_FREQ, BEEP_WARN_DUR);
       WinTerminate(hab);
       return(RETURN_ERROR);
   }

   if(!Init())
   {
        MessageBox(HWND_DESKTOP,
                   IDMSG_INITFAILED,
                   MB_OK | MB_ERROR,
                   TRUE);

        return(RETURN_ERROR);
   }
   /* Create the main window */
   flCtlData = FCF_STANDARD;

   hwndMainFrame = WinCreateStdWindow(HWND_DESKTOP,
                                      WS_VISIBLE,
                                      &flCtlData,
                                      szAppName,
                                      NULL,
                                      WS_VISIBLE,
                                      (HMODULE)NULL,
                                      ID_RESOURCE,
                                      (PHWND)&hwndMain);
   if(hwndMainFrame == NULLHANDLE)
   {
       MessageBox(HWND_DESKTOP,
                  IDMSG_MAINWINCREATEFAILED,
                  MB_OK | MB_ERROR,
                  TRUE);

       return(RETURN_ERROR);
   }
   InitHelp();
   /* Get/Dispatch Message loop */
   while(WinGetMsg(hab, (PQMSG)&qmsg, 0L, 0L, 0L))
       WinDispatchMsg(hab, (PQMSG)&qmsg);

   /* Destroy the help instance */
   DestroyHelpInstance();

#ifdef BACKGROUND_THREAD
   DestroyBackgroundThread();
#endif

   /* Perform exit housekeeping */
   ExitProc();

   return(RETURN_SUCCESS);

}   /* main() */

/****************************************************************\
 *  Initialization routine
 *--------------------------------------------------------------
 *
 *  Name:    Init(VOID)
 *
 *  Purpose: Performs initialization functions required before the main
 *           window can be created.
 *
 *  Usage:   Called once before the main window is created.
 *
 *  Method   - registers all window classes
 *           - performs any command line processing
 *
 *
 *  Returns: TRUE - initialization is successful
 *           FALSE - initialization failed
\****************************************************************/
BOOL Init(VOID)
{
    /* load application name from resource file */
    if(!WinLoadString(hab, 0L, IDS_APPNAME, MAXNAMEL, szAppName))
        return FALSE;

    /* load "untitled" string */
    if(!WinLoadString(hab, 0L, IDS_UNTITLED, MESSAGELEN, szUntitled))
        return FALSE;

    /* register the main client window class */
    if(!WinRegisterClass(hab,
                         (PSZ)szAppName,
                         (PFNWP)MainWndProc,
                         CS_SIZEREDRAW | CS_CLIPCHILDREN,
                         0L))
    {
        return FALSE;
    }

    /* If you wish to create a thread for background processing, define
     *  the BACKGROUND_THREAD constant used by the following routine.
     * The routines for the background thread are included in this source
     *  file.
     */

#ifdef BACKGROUND_THREAD
    if(!CreateBackgroundThread())
        return FALSE;
#endif

    return TRUE;

}   /* Init() */

/****************************************************************\
 *  Exit housekeeping procedure
 *--------------------------------------------------------------
 *
 *  Name:    ExitProc()
 *
 *  Purpose: Cleans up certain resources when the application terminates
 *
 *  Usage:   Routine is called by main just before the application exits
 *
 *  Method:  Global resources, such as the main window and message queue,
 *           are destroyed and any system resources used are freed.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID APIENTRY ExitProc() 
{
    /* Destroy the secondary thread if it exists */
    if (tidCalcThread)
    {
       fContinueCalc = FALSE;                    /* Notify thread to quit */
       DosWaitThread(&tidCalcThread, DCWW_WAIT); /* Wait until complete */
    }

    /* destroy the main window if it exists */
    if(WinIsWindow(hab, hwndMainFrame))  
       WinDestroyWindow(hwndMainFrame);
    
    /*--------------------------------------------------*\
     *      Any other system resources used
     *      (e.g. memory or files) should be freed here
    \*--------------------------------------------------*/
    WinDestroyMsgQueue(hmq);

    WinTerminate(hab);

    return;

}   /* ExitProc() */

/****************************************************************\
 *  Main client window procedure
 *--------------------------------------------------------------
 *
 *  Name:    MainWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
 *
 *  Purpose: Handles all the messages associated with the main window
 *           and calls the appropriate handling procedures.
 *
 *  Usage:   Called for each message placed in the window's message queue
 *
 *  Method:  Called only by main().  Note that when WM_PAINT executes,
 *           the secondary thread may change data during the update
 *           which may cause a problem.  However, this is NOT a write
 *           conflict, as only 1 thread does the writing.
 *
 *  Returns: Return values are determined by each message
 *
\****************************************************************/
MRESULT EXPENTRY MainWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   CHAR   szMsg[MSGBUFSIZE];           /* Sprintf buffer */
   MRESULT sRC;

   switch(msg)
   {
      case WM_PAINT:
         MainPaint(hwnd);
         break;

      case WM_COMMAND:
         MainCommand(hwnd, mp1, mp2);
         break;
      
      case IDM_DONE:
         EnableMenuItem(hwnd,IDM_START,TRUE);  /* Reenable Start & set  */
         EnableMenuItem(hwnd,IDM_SET,TRUE);
         EnableMenuItem(hwnd,IDM_STOP,FALSE);  /* Disable stop          */
                                               /* Print msg             */
         sprintf(szMsg,"%lu disks were moved.",ulIterations);  
         WinMessageBox(HWND_DESKTOP, hwnd, szMsg, "Done!", 0L,
                       MB_OK | MB_MOVEABLE | MB_INFORMATION);
         SetupTowers();                        /* Reset towers          */
         WinInvalidateRect(hwnd,NULL,FALSE);   /* Force a screen redraw */
         break;

      case HM_QUERY_KEYS_HELP:
         return ( (MRESULT)PANEL_KEYSHELP);

      default:
         sRC = WinDefWindowProc(hwnd, msg, mp1, mp2);
         return sRC;
   }
   /* all window procedures should return 0 as a default */
   return (MRESULT)0L;

}   /* MainWndProc() */

/****************************************************************\
 *  Main client painting routine
 *--------------------------------------------------------------
 *
 *  Name:    MainPaint(HWND hwnd)
 *
 *  Purpose: Paints the main client window.
 *
 *  Usage:   Routine is called whenver the client window
 *           procedure receives a WM_PAINT message
 *
 *
 *  Method:  -begins painting by calling WinBeginPaint and retrieving
 *            the HPS for the window
 *           -performs any painting desired
 *           -ends painting by calling WinEndPaint
 *
 *  Returns: 0 - if successful execution completed
 *           1 - if error
 *
\****************************************************************/
VOID MainPaint(HWND hwnd)
{
   HPS    hps;                         /* Handle for painting           */
   RECTL  rclUpdate, rect;             /* Rectangle struct for painting */
   POINTL ptl;                         /* Point struct for painting     */
   BYTE   cPole,bCnt,cnt;              /* Utility variables             */
   CHAR   szBuffer[BUFF_SIZE];
   LONG   lVert,bHeight;
   FONTMETRICS FontMetrics;

   hps = WinBeginPaint(hwnd, 0L, (PRECTL)&rclUpdate);

   /* Fill update rectangle with window color */
   WinFillRect(hps, (PRECTL)&rclUpdate, SYSCLR_WINDOW);
   WinQueryWindowRect(hwndMain, (PRECTL)&rect);
   /*
    *get the character set size
    */
   GpiQueryFontMetrics(hps,sizeof(FontMetrics),&FontMetrics);
   ptl.x = (rect.xRight - ( strlen(pszDisk) * FontMetrics.lAveCharWidth)) / 2;
   ptl.y = rect.yTop   -  ( (VERT_POS - 2)  * FontMetrics.lEmHeight);
   if(fViewOn) /*view disk information*/
   {
      memset(szBuffer, 0L, sizeof(szBuffer));
      strcpy(szBuffer,pszDisk);
      GpiCharStringAt(hps, &ptl, strlen(szBuffer), szBuffer);
   }
   /*
    *center the base in the middle
    *of our screen
    */
   DrawRect( (rect.xRight - BASELEN) /2,
             (rect.yTop - BASETHICK)  /2,
             (rect.xRight + BASELEN) /2,
             (rect.yTop + BASETHICK)  /2,
              CLR_DARKGREEN );

   /* Draw the 3 posts */
   lVert   = (rect.yTop - BASETHICK)/2 +BASETHICK ;
   bHeight  = lVert + (cTowerSize *DISKSPACE + POSTEXTRAHT) ;
   for(cnt=0;cnt<3;cnt++)
   {
      ausPolePos[cnt] =
         ((rect.xRight - BASELEN) /2)+ ((BASELEN -(POSTHALF+POSTWIDTH))/2   * cnt);
      DrawRect(ausPolePos[cnt],
               bHeight,
               ausPolePos[cnt]+(POSTHALF+POSTWIDTH),
               lVert,
               CLR_DARKGREEN);
   }

   /* Place the appropriate disks on each pole */
   for(cPole=0;cPole<3;cPole++)
   {
      for(bCnt=0;bCnt<abTowersNdx[cPole];bCnt++)
      {
         DrawDisk(hps,cPole,bCnt,fDRAW);
      }
   }
   WinEndPaint(hps);
   return;

}   /* MainPaint() */

/****************************************************************\
 *  Main window WM_COMMAND processing procedure
 *--------------------------------------------------------------
 *
 *  Name:    MainCommand(HWND hwnd, MPARAM mp1, MPARAM mp2)
 *
 *  Purpose: Calls the appropriate procedures that deal with the
 *           selected menu item.
 *
 *  Usage:   Routine is called whenever a WM_COMMAND message is posted
 *           to the main window.
 *
 *  Method:  a switch statement branches on the id of the menu item
 *           that posted the message and the appropriate action for
 *           that item is taken.  Any menu ids that are not part of
 *           the standard menu set are passed onto the user defined
 *           WM_COMMAND processing procedure.
 *
 *  Returns: Return values are determined by each message
 *
\****************************************************************/
LONG MainCommand(HWND hwnd, MPARAM mp1, MPARAM mp2)
{
   switch(SHORT1FROMMP(mp1))
   {
      case IDM_START:
                              /* Set continuation fContinueCalc */
         fContinueCalc = TRUE;
         ulIterations = 0L;            /* Zero iteration counter */
         if (DosCreateThread (&tidCalcThread, (PFNTHREAD)CalcThread,
                                   0L, 0L, STACK))
            DosBeep (440, 175);
         else               /* Disallow menu items that could change data */
         {                          /* while the second thread is running */
            EnableMenuItem(hwnd, IDM_START, FALSE); /* Disable Start item */
            EnableMenuItem(hwnd, IDM_SET, FALSE);   /* Disable Set item */
            EnableMenuItem(hwnd, IDM_STOP, TRUE);   /* Enable Stop item */
         }
         break;

      case IDM_STOP:
         fContinueCalc = FALSE;       /* Notify thread to quit */
         break;

      case IDM_SET:                /* Pop up the query/set box */
         if(WinDlgBox(HWND_DESKTOP, hwnd,
                   (PFNWP)EntryFldDlgProc, (HMODULE)0L,IDD_SETCOUNT,0L))
         {
            SetupTowers();                     /* Reset towers */
            WinInvalidateRect(hwnd,NULL,FALSE);
         }
         break;

      case IDM_ON:
         fViewOn = TRUE;
         WinInvalidateRect(hwnd,NULL,FALSE);
         break;

      case IDM_OFF:
         fViewOn = FALSE;
         WinInvalidateRect(hwnd,NULL,FALSE);
         break;


      case IDM_HELPHELPFORHELP:
         HelpHelpForHelp(mp2);
         break;

      case IDM_HELPEXTENDED:
         HelpExtended(mp2);
         break;

      case IDM_HELPKEYS:
         HelpKeys(mp2);
         break;

      case HM_QUERY_KEYS_HELP:
         return (PANEL_KEYSHELP);

      case IDM_HELPINDEX:
         HelpIndex(mp2);
         break;

      case IDM_HELPPRODUCTINFO:
         HelpAbout(mp2);
         break;
   }
   return 0;
}

/****************************************************************\
 *  Creates the Background thread
 *--------------------------------------------------------------
 *
 *  Name:    CreateBackgroundThread(VOID)
 *
 *  Purpose: Routine creates the background thread
 *
 *  Usage:   Routine is called at initialization time to create a
 *           background processing thread.
 *
 *  Method:  The routine calls DosCreateThread with the Background
 *           thread routine.
 *
 *  Returns: TRUE if thread is created successfully.
 *           FALSE if not or if the thread was already created
 *
\****************************************************************/
BOOL CreateBackgroundThread(VOID)
{
    LONG sRet;

    /*------------------------------------------------------------------*
     *  Note: C-runtime considerations:
     *  If you use non-reentrant C runtime functions in the second thread,
     *  then you will need to use _beginthread and _endthread instead of
     *  DosCreateThread and DosExit.
     *------------------------------------------------------------------*/
    if(!fThreadCreated)
    {
        DosCreateEventSem((PSZ)NULL, &hevThreadInit, 0L, FALSE);
        sRet = DosCreateThread(&tidBkThread,
                                      (PFNTHREAD)BackgroundThread,
                                      0L,
                                      0L,
                                      THREADSTACKSIZE);
    }
    else
    {
        return FALSE;
    }

                  /* wait until the thread has finished initialization */
    if(DosWaitEventSem(hevThreadInit, SEM_TIMEOUT))
        return FALSE;

    return((BOOL)(sRet == 0));

}   /* CreateBackgroundThread() */

/****************************************************************\
 *  Destroys the Background thread
 *--------------------------------------------------------------
 *
 *  Name:    DestroyBackgroundThread(VOID)
 *
 *  Purpose: Routine destroys the background thread
 *
 *  Usage:   Routine is called at exit time to destroy the background
 *           processing thread.
 *
 *  Method:  The routine posts a WM_CLOSE message to the object window
 *           to end its message loop.  It then waits to make sure that
 *           the thread has been terminated before it returns.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID DestroyBackgroundThread(VOID)
{
   PostBkThreadMsg(WM_CLOSE, NULL, NULL);

   DosWaitThread(&tidBkThread, 0L);
   return;
}                                  /* DestroyBackgroundThread() */

/****************************************************************\
 *  DrawDisk procedure
 *--------------------------------------------------------------
 *
 *  Name:    DrawDisk(HPS hps, BYTE cPole, BYTE bLevel, BYTE fDraw)
 *
 *  Purpose: This routine takes a PS handle, the hanoi spindle and
 *           disk level and draws an appropriately sized disk.
 *
 *  Usage:   Routine is called whenever the disk need to display.
 *
 *  Method:  Does not grab exclusive access to the screen before
 *           drawing which may cause a problem.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID DrawDisk(HPS hps, BYTE cPole, BYTE bLevel, BYTE fDraw)
{
   USHORT usXstart,usYstart,usWidth;
   POINTL ptl;
   RECTL  rect;             /* Rectangle struct for painting */

   /* Calculate Bottom of disk */
   WinQueryWindowRect(hwndMain,&rect);
   usYstart = (rect.yTop + BASETHICK) /2 + (DISKSPACE * bLevel);


   /* Calculate the disk's width */
   usWidth = (MAXDISKWIDTH-MINDISKWIDTH) * abTowers[cPole][bLevel]
              /cTowerSize + MINDISKWIDTH;
   /* Center disk on pole */
   usXstart = (ausPolePos[cPole] - usWidth/2 ) + DISKTHICK;

   if(fDraw == fDRAW)             /* If we are to draw the disk */
   {
      DrawRect(usXstart,usYstart,usXstart+usWidth,
               usYstart+DISKTHICK-1,CLR_RED);
   }
   else       /* We are to erase the disk, then redraw the pole */
   {
      DrawRect(usXstart,usYstart,usXstart+usWidth,
               usYstart+DISKTHICK-1,CLR_WHITE);
#if 0
      DrawRect(ausPolePos[cPole]-POSTHALF,
               usYstart,
               ausPolePos[cPole]-POSTHALF+POSTWIDTH,
               usYstart+DISKTHICK-1,
               CLR_DARKGREEN);
#endif
      DrawRect(ausPolePos[cPole],
               usYstart,
               ausPolePos[cPole]+POSTHALF+POSTWIDTH,
               usYstart+DISKTHICK-1,
               CLR_DARKGREEN);
   }
   return;
}

/****************************************************************\
 *  CalcThread procedure
 *--------------------------------------------------------------
 *
 * Name:    CalcThread(VOID)
 *
 * Purpose: Calls the recursive Hanoi with initial setting of 0,2,1
 *          meaning from pole 0, to pole 2, using pole 1 as a temporary.
 *          Hanoi returns when finished, or the user says stop.
 *          This proc then sets a critical section so the posted
 *          message won't be handled until the thread is terminated.
 *
 * Usage:   Routine is called whenever a IDM_START message is posted to
 *          the main window.
 *
 * Method:   
 *
 * Returns: VOID
 *
\****************************************************************/
VOID CalcThread(VOID)
{
   HAB    habb;                  /* Anchor block for the process */

   habb = WinInitialize(0L);     /* Called to increase Ring 2 stack size */
   Hanoi(cTowerSize,0,2,1);      /* Execute the recursive routine */
   WinTerminate(habb);

   DosEnterCritSec(); /* Set Crit so the IDM_DONE isn't processed */
                      /* until this thread has completely terminated  */
   WinPostMsg(hwndMain,IDM_DONE,NULL,NULL);

   DosExitCritSec();             /* Restore normal thread dispatching */

   DosExit (EXIT_THREAD, 0L);    /* Terminate thread */
   return;
}

/****************************************************************\
 *  EnableMenuItem procedure
 *--------------------------------------------------------------
 *
 * Name:    EnableMenuItem(HWND hwnd, LONG sMenuItem, BOOL fEnable)
 *
 * Purpose: This routine handles enabling/disabling of menu items.  This
 *          is done by getting Parent and Menu hwnd handles then sending
 *          the appropriate message.
 *
 * Usage:   Routine is called to enable or disable one item from menu.
 *
 * Method:
 *
 * Returns: VOID
 *
\****************************************************************/
VOID EnableMenuItem(HWND hwnd, LONG sMenuItem, BOOL fEnable)
{
   HWND hwndParent = WinQueryWindow(hwnd, QW_PARENT);
   HWND hwndMenu   = WinWindowFromID(hwndParent, FID_MENU);

   WinSendMsg(hwndMenu, MM_SETITEMATTR,
              MPFROM2SHORT(sMenuItem, TRUE),
              MPFROM2SHORT(MIA_DISABLED, fEnable ? 0 : MIA_DISABLED));
   return;
}

/****************************************************************\
 *  Hanoi recursion procedure
 *--------------------------------------------------------------
 *
 *  Name:    Hanoi(BYTE bHeight, BYTE bFrom, BYTE bTo, BYTE bTemp)
 *
 *  Purpose: This routine implements a recursive hanoi program that
 *           works as follows:  By recursion, move all the disks,
 *           except for the bottom disk to the temporary stack.
 *           Then move the bottom disk to the target spindle.
 *           Now recursively move the stack on the temporary spindle
 *           to the target spindle.  The limiting case is when Hanoi()
 *           is called with a bHeight of 0 in which case the depth
 *           recursion is terminated.
 *
 *  Usage:
 *
 *  Method:  This routine checks the ->fContinueCalc flag, which is
 *           set by the main thread when the user selects stop, to
 *           see if the user wishes to abort the algorithm.  If so,
 *           it backs out and exits.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID Hanoi(BYTE bHeight, BYTE bFrom, BYTE bTo, BYTE bTemp)
             /* bHeight - The number of disks in the from stack to move */
             /* bFrom   - The from spindle number, 0-2 */
             /* bTo     - The to spindle number, 0-2 */
             /* bTemp   - The temporary spindle number */
{
   HPS    hps;                           /* Handle for painting */
   RECTL  rect;                /* Rectangle struct for painting */
   CHAR   szBuffer[BUFF_SIZE];
   LONG   lIncrement = 1;
   POINTL ptl;
   USHORT usCenter;
   FONTMETRICS FontMetrics;

   if(bHeight<=0 || !fContinueCalc)       /* Exit up if no more */
      return;                    /* disks or the user said Stop */

   Hanoi((BYTE)(bHeight-1),         /* Move all but bottom disk */
         (BYTE)bFrom,
         (BYTE)bTemp,
         (BYTE)bTo);

   if(!fContinueCalc)                   /* If user said to stop */
      return;
   /* Display bFrom -> bTo */
   hps = WinGetPS(hwndMain);
   MoveDisk(hps,bFrom,bTo);             /* Move the bottom disk */
   if (fViewOn)
   {
      WinQueryWindowRect(hwndMain, (PRECTL)&rect);
      GpiQueryFontMetrics(hps,sizeof(FontMetrics),&FontMetrics);
      /*
       *set  center
       */
      usCenter =  (rect.xRight/2);
      /*
       *left hand side of text to blank out
       */
      rect.xLeft = ptl.x =( usCenter +( ( strlen(pszDisksMoved) ) / 2) * FontMetrics.lAveCharWidth);

      /*
       *bottom
       */
      rect.yBottom = ptl.y = rect.yTop - (VERT_POS * FontMetrics.lEmHeight);
      /*
       *top
       */
      rect.yTop    = rect.yTop -   ((VERT_POS - 1)  * FontMetrics.lEmHeight);


      rect.yBottom = ptl.y;
      /*
       *clear off the previous  numbers
       *by drawing a  opaque rectangle
       */
      memset(szBuffer,' ', sizeof(szBuffer) );

      GpiCharStringPosAt(hps,
                         &ptl,
                         &rect,
                         (ULONG)CHS_OPAQUE,
                         DELETE_WIDTH,
                         szBuffer,
                         &lIncrement);

      GpiCharStringAt(hps, &ptl, strlen(szBuffer), szBuffer);
      strcpy(szBuffer,pszDisksMoved);
      /*
       *display the number of disks moved
       */
      /*
       *left hand side of text to draw
       */
      ptl.x = usCenter - (( (strlen(pszDisksMoved) + MAX_DIGITS)/ 2)* FontMetrics.lAveCharWidth);
      GpiCharStringAt(hps, &ptl, strlen(szBuffer), szBuffer);
      sprintf(szBuffer,"%05lu",
                       ulIterations+ 1 );

      ptl.x = usCenter + ( ((strlen(pszDisksMoved ) /2) + 1) * FontMetrics.lAveCharWidth);
      GpiCharStringAt(hps, &ptl, strlen(szBuffer), szBuffer);
   }
   WinReleasePS(hps);
   ulIterations++;
   /* Move disks over */
   Hanoi((BYTE)(bHeight-1),(BYTE)bTemp,(BYTE)bTo,(BYTE)bFrom);
   return;
}

/****************************************************************\
 *  SetupTowers procedure
 *--------------------------------------------------------------
 *
 *  Name:    SetupTowers(VOID)
 *
 *  Purpose: This routine initializes the global arrays that represent
 *           the hanoi stacks.  This involves placing all the disks on
 *           the first peg, emptying the other 2 pegs and setting the
 *           associated counts.
 *
 *  Usage:   Routine is called when program started or restarted.
 *
 *  Method:  Calling uses the global variable cTowerSize to determine
 *           how many disks there are.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID SetupTowers(VOID)
{
   USHORT cnt;

   for(cnt=0; cnt<cTowerSize; cnt++)     /* Setup the intial post with disks */
      abTowers[0][cnt] = cTowerSize - (BYTE)cnt - (BYTE)1;

   abTowersNdx[0] = (BYTE)cTowerSize;    /* Set disk count for initial post */
   abTowersNdx[1] = abTowersNdx[2] = (BYTE)0;     /* Zero other post counts */
   return;
}

/****************************************************************\
 *  MoveDisk procedure
 *--------------------------------------------------------------
 *
 *  Name:    MoveDisk(HPS hps, BYTE bFrom, BYTE bTo)
 *
 *  Purpose: This routine moves the top disk from the bFrom spindle
 *           to the top of the bTo spindle.
 *
 *  Usage:
 *
 *  Method:  Does error checking for trying to move a disk from a
 *           spindle that does not have any disks on it.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID MoveDisk(HPS hps, BYTE bFrom, BYTE bTo)
                        /* hps - Handle for painting */
                        /* bFrom - The from spindle number, 0-2 */
                        /* bTo - The to spindle number, 0-2 */
{
   CHAR bTOSndx;                        /* Top of stack index */
   BYTE bDiskNum;                       /* Disk number to move */

   bTOSndx = abTowersNdx[bFrom]-(CHAR) 1;

   DrawDisk(hps,bFrom,bTOSndx,fERASE);  /* Remove disk off from stack */

   bDiskNum = abTowers[bFrom][bTOSndx]; /* Get move disk number */
   abTowersNdx[bFrom]--;                /* Decrease count on from spindle */

   /* Offset to place the disk at Place on stack in memory */
   bTOSndx = abTowersNdx[bTo]++;
   abTowers[bTo][bTOSndx] = bDiskNum;
                                        /* Draw disk on the to stack */
   DrawDisk(hps,bTo,bTOSndx,fDRAW);
   return;
}

/****************************************************************\
 *  EntryFldDlgProc procedure
 *--------------------------------------------------------------
 *
 *  Name:   EntryFldDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
 *
 *
 * Purpose: Handles all the messages associated with the set entry field
 *          and calls the appropriate handling procedures.  The purpose
 *          of this dialog box is to get a new number of disks for the
 *          hanoi routine.
 *
 * Usage:
 *
 * Method:  If the value entered is valid, global cTowerSize is changed
 *          to the new value, and TRUE is returned.
 *
 * Returns: Terminates with a TRUE if a new valid Tower Size has been entered.
 *
\****************************************************************/
MRESULT EXPENTRY EntryFldDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   SHORT sNewSize=0;                   /* Holds new number of disks */
   MRESULT sRC;

   switch(msg)
   {
      case WM_INITDLG:
         FixSysMenu(hwnd);

         WinSendDlgItemMsg(hwnd, IDD_ENTRYFLD, EM_SETTEXTLIMIT,
                           MPFROM2SHORT(2,0),NULL);  /* Limit len */
         WinSetDlgItemShort(hwnd, IDD_ENTRYFLD, cTowerSize,TRUE);
         return (MRESULT)0L;           /* Allow normal focus setting */

      case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
            case DID_OK:
               WinQueryDlgItemShort(hwnd, IDD_ENTRYFLD, &sNewSize, TRUE);
               if(sNewSize>0 && sNewSize<=MAXDISKCNT) /* Set new Tower size */
               {
                  cTowerSize = (BYTE) sNewSize;
                  WinDismissDlg(hwnd,TRUE);
               }
               else                    /* Invalid value */
                  MessageBox(hwndMainFrame,
                             IDMSG_DISKNUMBERERROR,
                             MB_OK | MB_ICONEXCLAMATION,
                             TRUE);
               return (MRESULT)0L;

            case DID_CANCEL:
               WinDismissDlg(hwnd,FALSE);
               return (MRESULT)0L;

            default:
               sRC = WinDefDlgProc(hwnd, msg, mp1, mp2);
               return sRC;
         }
         break;

      default:
         sRC = WinDefDlgProc(hwnd, msg, mp1, mp2);
         return sRC;
   }
   return (MRESULT)0L;
}

/****************************************************************\
 *  Dialog procedure for the About dialog box
 *--------------------------------------------------------------
 *
 *  Name:    AboutDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
 *
 *  Purpose: Handles all the messages associated with the About Box
 *
 *  Usage:   Called for each message sent to the About Box dialog box.
 *
 *  Method:  The about box only has a button control so this routine
 *           only processes WM_COMMAND messages. Any WM_COMMAND
 *           posted must have come from the Ok button so we dismiss
 *           the dialog upon receiving it.
 *
 *  Returns: Dependent upon message sent
 *
\****************************************************************/
MRESULT EXPENTRY AboutDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   MRESULT sRC;

   switch(msg)
   {
      case WM_INITDLG:
         FixSysMenu(hwnd);
         return (MRESULT)0L;

      case WM_COMMAND:
         WinDismissDlg(hwnd, TRUE);
         return (MRESULT)0L;

      default:
         sRC = WinDefDlgProc(hwnd, msg, mp1, mp2);
         return sRC;
   }
   return (MRESULT)0L;
}

/****************************************************************\
 *  FixSysMenu procedure
 *--------------------------------------------------------------
 *
 *  Name:    FixSysMenu(HWND hwndDlg)
 *
 *  Purpose: This routine removes the Restore, Size, Minimize, and
 *           Maximize options from the system menu of a dialog.
 *
 *  Usage
 *
 *  Method:  Called during the WM_INITDLG of a dialog procedure.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID FixSysMenu(HWND hwndDlg)
{
   HWND hwndMenu;                      /* Handle to system menu */

   hwndMenu = WinWindowFromID(hwndDlg, FID_SYSMENU);

   WinSendMsg(hwndMenu,  /* Delete Restore from the system menu */
              MM_DELETEITEM,
              MPFROM2SHORT(SC_RESTORE, TRUE),
              MPFROMP(NULL));

   WinSendMsg(hwndMenu,     /* Delete Size from the system menu */
              MM_DELETEITEM,
              MPFROM2SHORT(SC_SIZE, TRUE),
              MPFROMP(NULL));

   WinSendMsg(hwndMenu, /* Delete Minimize from the system menu */
              MM_DELETEITEM,
              MPFROM2SHORT(SC_MINIMIZE, TRUE),
              MPFROMP(NULL));

   WinSendMsg(hwndMenu, /* Delete Maximize from the system menu */
              MM_DELETEITEM,
              MPFROM2SHORT(SC_MAXIMIZE, TRUE),
              MPFROMP(NULL));
   return;
}

/****************************************************************\
 *  Message Box procedure
 *--------------------------------------------------------------
 *
 *  Name:    MessageBox(HWND hwndOwner, LONG IdMsg, LONG fsStyle, BOOL fBeep)
 *
 *  Purpose: Displays the message box with the message given in idMsg
 *           retrieved from the message table and using the style
 *           flags in fsStyle
 *
 *  Usage:   Called whenever a MessageBox is to be displayed
 *
 *  Method:  - Message string is loaded from the process' message table
 *           - Alarm beep is sounded if desired
 *           - Message box with the message is displayed
 *           - WinMessageBox return value is returned
 *
 *  Returns: Return value from WinMessageBox()
 *
\****************************************************************/
LONG MessageBox(HWND hwndOwner, LONG IdMsg, LONG fsStyle, BOOL fBeep)
           /* hwndOwner - Handle of the message box's owner */
           /* idMsg - ID if the message in the message table */
           /* fsStyle - Style of the message box */
           /* fBeep - If TRUE, beep before message box is displayed */
{
    CHAR szText[MESSAGELEN];
    LONG sRC;

    if(!WinLoadMessage(hab,
                      (HMODULE)NULL,
                      IdMsg,
                      MESSAGELEN,
                      (PSZ)szText))
    {
        WinAlarm(HWND_DESKTOP, WA_ERROR);
        return RETURN_ERROR;
    }

    if(fBeep)
        WinAlarm(HWND_DESKTOP, WA_ERROR);

    sRC = WinMessageBox(HWND_DESKTOP,
                        hwndOwner,
                        szText,
                        (PSZ)NULL,
                        IDD_MSGBOX,
                        fsStyle);
    return sRC;

}   /* MessageBox() */

/****************************************************************\
 *  Routine for initializing the help manager
 *--------------------------------------------------------------
 *
 *  Name:    InitHelp(VOID)
 *
 *  Purpose: Initializes the IPF help facility
 *
 *  Usage:   Called once during initialization of the program
 *
 *  Method:  Initializes the HELPINIT structure and creates the help
 *           instance. If successful, the help instance is associated
 *           with the main window
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID InitHelp(VOID)
{
   HELPINIT hini;

   /* If we return because of an error, Help will be disabled */
   fHelpEnabled = FALSE;
                             /* Initialize help init structure */
   hini.cb = sizeof(HELPINIT);
   hini.ulReturnCode = 0;
                             /* If tutorial added, add name here */
   hini.pszTutorialName = (PSZ)NULL;

   hini.phtHelpTable = (PHELPTABLE)MAKELONG(HANOI_HELP_TABLE, 0xFFFF);
   hini.hmodHelpTableModule = 0;
   hini.hmodAccelActionBarModule = 0;
   hini.idAccelTable = 0;
   hini.idActionBar = 0;

   if(!WinLoadString(hab,
                     0,
                     IDS_HELPWINDOWTITLE,
                     HELPLIBRARYNAMELEN,
                     (PSZ)szWindowTitle))
   {
       MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
                             MB_OK | MB_ERROR, FALSE);
       return;
   }
   hini.pszHelpWindowTitle = (PSZ)szWindowTitle;

                             /* If debugging, show panel ids, else don't */
#ifdef DEBUG
   hini.fShowPanelId = CMIC_SHOW_PANEL_ID;
#else
   hini.fShowPanelId = CMIC_HIDE_PANEL_ID;
#endif

   if(!WinLoadString(hab,
                     0,
                     IDS_HELPLIBRARYNAME,
                     HELPLIBRARYNAMELEN,
                     (PSZ)szLibName))
   {
       MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
                             MB_OK | MB_ERROR, FALSE);
       return;
   }
   hini.pszHelpLibraryName = (PSZ)szLibName;
                                       /* Creating help instance */
   hwndHelpInstance = WinCreateHelpInstance(hab, &hini);

   if(hwndHelpInstance == 0L || hini.ulReturnCode)
   {
       MessageBox(hwndMainFrame, IDMSG_HELPLOADERROR, MB_OK | MB_ERROR, TRUE);
       return;
   }
                             /* Associate help instance with main frame */
   if(!WinAssociateHelpInstance(hwndHelpInstance, hwndMainFrame))
   {
       MessageBox(hwndMainFrame, IDMSG_HELPLOADERROR,
                                 MB_OK | MB_ERROR, TRUE);
       return;
   }

   /* Help manager is successfully initialized so set flag to TRUE */
   fHelpEnabled = TRUE;
   return;

}   /* InitHelp() */

/****************************************************************\
 *  Processes the Help for Help command from the menu bar
 *--------------------------------------------------------------
 *
 *  Name:    HelpHelpForHelp(MPARAM mp2)
 *
 *  Purpose: Processes the WM_COMMAND message posted by the Help for
 *           Help item of the Help menu
 *
 *  Usage:   Called from MainCommand when the Help for Help menu item
 *           is selected
 *
 *  Method:  Sends an HM_DISPLAY_HELP message to the help instance so
 *           that the default Help For Help is displayed.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID HelpHelpForHelp(MPARAM mp2)
{
           /* This just displays the system help for help panel */
   if(fHelpEnabled)
     if((LONG)WinSendMsg(hwndHelpInstance, HM_DISPLAY_HELP,
                                        (MPARAM)0L, (MPARAM)0L))
           MessageBox(hwndMain,
                      IDMSG_HELPDISPLAYERROR,
                      MB_OK | MB_ERROR,
                      FALSE);

   /* This routine currently doesn't use the mp2 parameter but
    *  it is referenced here to prevent an 'Unreferenced Parameter'
    *  warning at compile time.
    */

   return;

}   /* HelpHelpForHelp() */

/****************************************************************\
 *  Processes the Extended Help command from the menu bar
 *--------------------------------------------------------------
 *
 *  Name:    HelpExtended(MPARAM mp2)
 *
 *  Purpose: Processes the WM_COMMAND message posted by the Extended
 *           Help item of the Help menu.
 *
 *  Usage:   Called from MainCommand when the Extended Help menu item
 *           is selected.
 *
 *  Method:  Sends an HM_EXT_HELP message to the help instance so that
 *           the default Extended Help is displayed.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID HelpExtended(MPARAM mp2)
{
           /* This just displays the system extended help panel */
   if(fHelpEnabled)
        if((LONG)WinSendMsg(hwndHelpInstance, HM_EXT_HELP,
                                               (MPARAM)0L,(MPARAM)0L))
            MessageBox(hwndMain,
                       IDMSG_HELPDISPLAYERROR,
                       MB_OK | MB_ERROR,
                       FALSE);

    /* This routine currently doesn't use the mp2 parameter but
     *  it is referenced here to prevent an 'Unreferenced Parameter'
     *  warning at compile time.
     */

   return;

}   /* HelpExtended() */

/****************************************************************\
 *  Processes the Keys Help command from the menu bar
 *--------------------------------------------------------------
 *
 *  Name:    HelpKeys(MPARAM mp2)
 *
 *  Purpose: Processes the WM_COMMAND message posted by the Keys Help
 *           item of the Help menu.
 *
 *  Usage:   Called from MainCommand when the Keys Help menu item is
 *           selected
 *
 *  Method:  Sends an HM_KEYS_HELP message to the help instance so that
 *           the default Keys Help is displayed.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID HelpKeys(MPARAM mp2)
{
               /* This just displays the system keys help panel */
    if(fHelpEnabled)
        if((LONG)WinSendMsg(hwndHelpInstance, HM_KEYS_HELP,
                                             (MPARAM)0L,(MPARAM)0L))
            MessageBox(hwndMain,
                       IDMSG_HELPDISPLAYERROR,
                       MB_OK | MB_ERROR,
                       FALSE);

    /* This routine currently doesn't use the mp2 parameter but
     *  it is referenced here to prevent an 'Unreferenced Parameter'
     *  warning at compile time.
     */

    return;

}   /* HelpKeys() */

/****************************************************************\
 *  Processes the Index Help command from the menu bar
 *--------------------------------------------------------------
 *
 *  Name:    HelpIndex(MPARAM mp2)
 *
 *  Purpose: Processes the WM_COMMAND message posted by the Index Help
 *           item of the Help menu
 *
 *  Usage:   Called from MainCommand when the Index Help menu item
 *           is selected
 *
 *  Method:  Sends an HM_INDEX_HELP message to the help instance so
 *           that the default Index Help is displayed.
 *
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID HelpIndex(MPARAM mp2)
{
              /* This just displays the system help index panel */
    if(fHelpEnabled)
        if((LONG)WinSendMsg(hwndHelpInstance, HM_HELP_INDEX,
                                             (MPARAM)0L,(MPARAM)0L))
            MessageBox(hwndMain,
                       IDMSG_HELPDISPLAYERROR,
                       MB_OK | MB_ERROR,
                       FALSE);

    /* This routine currently doesn't use the mp2 parameter but
     *  it is referenced here to prevent an 'Unreferenced Parameter'
     *  warning at compile time.   
     */

    return;

}   /* HelpIndex() */

/****************************************************************\
 *  Processes the About command from the Help menu
 *--------------------------------------------------------------
 *
 *  Name:    HelpAbout(MPARAM mp2)
 *
 *  Purpose: Processes the WM_COMMAND message posted by the About item
 *           of the Help menu
 *
 *  Usage:   Called from MainCommand when the About menu item is selected
 *
 *  Method:  Calls WinDlgBox to display the about box dialog.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID HelpAbout(MPARAM mp2)
{
                                 /* Display the AboutBox dialog */
    WinDlgBox(HWND_DESKTOP,
              hwndMain,
              (PFNWP)AboutDlgProc,
              0,
              IDD_PRODUCTINFO,
              (PVOID)NULL);

    /* This routine currently doesn't use the mp2 parameter but
     *  it is referenced here to prevent an 'Unreferenced Parameter
     *  warning at compile time.
     */

    return;

}   /* HelpAbout() */

/****************************************************************\
 *  Displays the help panel indicated
 *--------------------------------------------------------------
 *
 *  Name:    DisplayHelpPanel(LONG idPanel)
 *
 *  Purpose: Displays the help panel whose id is given
 *
 *  Usage:   Called whenever a help panel is desired to be displayed,
 *           usually from the WM_HELP processing of the dialog boxes
 *
 *  Method:  Sends HM_DISPLAY_HELP message to the help instance
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID DisplayHelpPanel(LONG idPanel)
                        /* ID of the help panel to be displayed */
{
    if(fHelpEnabled)
        if((LONG)WinSendMsg(hwndHelpInstance,
                      HM_DISPLAY_HELP,
                      MPFROMLONG(MAKELONG(idPanel, NULL)),
                      MPFROMSHORT(HM_RESOURCEID)))

            MessageBox(hwndMainFrame,
                       IDMSG_HELPDISPLAYERROR,
                       MB_OK | MB_ERROR,
                       TRUE);
    return;

}   /* DisplayHelpPanel() */

/****************************************************************\
 *  Destroys the help instance
 *--------------------------------------------------------------
 *
 *  Name:    DestroyHelpInstance(VOID)
 *
 *  Purpose: Destroys the help instance for the application
 *
 *  Usage:   Called after exit from message loop
 *
 *  Method:  Calls WinDestroyHelpInstance() to destroy the help instance
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID DestroyHelpInstance(VOID)
{
    if(hwndHelpInstance != 0L)
    {
        WinDestroyHelpInstance(hwndHelpInstance);
    }
    return;

}   /* DestroyHelpInstance() */

/****************************************************************\
 *  Posts a message to the Background thread
 *--------------------------------------------------------------
 *
 *  Name:    PostBkThreadMsg(ULONG msg, MPARAM mp1, MPARAM mp2)
 *
 *  Purpose: Routine posts a message to the object window of the
 *           background thread.
 *
 *  Usage:   Routine is called whenever a message is to be posted to
 *           the background processing thread.
 *
 *  Method:  The routine posts the message to the object window of the
 *           thread.
 *
 *  Returns:  the return value from WinPostMsg().
 *
\****************************************************************/
BOOL PostBkThreadMsg(ULONG msg, MPARAM mp1, MPARAM mp2)
{
   BOOL sRC;

   sRC = WinPostMsg(hwndObject, msg, mp1, mp2);
   return sRC;

}   /* PostBkThreadMsg() */

/****************************************************************\
 *  Background thread routine
 *--------------------------------------------------------------
 *
 *  Name:    BackgroundThread(ULONG ulThreadParam)
 *
 *  Purpose: Routine is a background thread used for tasks to be
 *           completed in the background.
 *
 *  Usage:   Routine is called at initialization time to create a
 *           background processing thread.
 *
 *  Method:  The routine initializes itself as a PM thread and creates
 *           a message queue.  It then creates an object window through
 *           which it will receive and send messages.  It then polls
 *           through a message loop, processing any messages it receives
 *           in the object window's window procedure. When the loop
 *           ends, it terminates.
 *
 *  Returns: VOID
 *
\****************************************************************/
VOID BackgroundThread(ULONG ulThreadParam)
                     /* Parameter passed into DosCreateThread() */
{
    QMSG qmsg;
                             /* Create message queue for thread */
    habBkThread = WinInitialize(0L);

    do
    {

         if(habBkThread == 0L)
         {
             WinPostMsg(hwndMain, TM_THREADINITFAILED, NULL, NULL);
             DosExit(EXIT_THREAD,(ULONG)NULL);
         }
         hmqBkThread = WinCreateMsgQueue(habBkThread, 0L);
         if(hmqBkThread == 0L)
         {
             WinPostMsg(hwndMain, TM_THREADINITFAILED, NULL, NULL);
             WinTerminate(habBkThread);
             DosExit(EXIT_THREAD, (ULONG)NULL);
         }

         /* Load the string for the object
          *  window class and register the class
          */

         if(!WinLoadString(habBkThread,
                           0,
                           IDS_OBJECTCLASS,
                           MAXNAMEL,
                           (PSZ)szObjectClass))
         {
             WinPostMsg(hwndMain, TM_THREADINITFAILED, NULL, NULL);
             break;
         }
         /* Register the main client window class */
         if(!WinRegisterClass(habBkThread,
                             (PSZ)szObjectClass,
                             (PFNWP)ObjectWndProc,
                             0L,
                             0L))
         {
             WinPostMsg(hwndMain, TM_THREADINITFAILED, NULL, NULL);
             break;
         }
         /* Create the object window */
         hwndObject = WinCreateWindow(HWND_OBJECT,
                                      szObjectClass,
                                      NULL,
                                      0L,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0L,
                                      HWND_TOP,
                                      OBJECTID,
                                      NULL,
                                      NULL);

         if(hwndObject == 0L)
         {
             WinPostMsg(hwndMain, TM_THREADINITFAILED, NULL, NULL);
             break;
         }

         /* Set thread created flag so another
          *thread of this type cannot be created
          */

         fThreadCreated = TRUE;

                                   /* Clear initialization semaphore */
         DosPostEventSem(hevThreadInit);


                                                     /* Message loop */
         while(WinGetMsg(hmqBkThread, (PQMSG)&qmsg, 0L, 0L, 0L))
             WinDispatchMsg(hmqBkThread, (PQMSG)&qmsg);

    }ONCE;

    /* Destroy object window, clean up message queue and terminate */
    if(WinIsWindow(habBkThread, hwndObject))
        WinDestroyWindow(hwndObject);

    WinDestroyMsgQueue(hmqBkThread);
    WinTerminate(habBkThread);

    /* If termination is due to an error initializing the thread, then clear
       the initialization semaphore so that the main thread can continue. */

    if(!fThreadCreated)
        DosPostEventSem(hevThreadInit);
    DosExit(EXIT_THREAD, 0L);
                 /* The thread parameter is not currently used */
    return;

}   /* BackgroundThread() */

/****************************************************************\
 *  Dialog procedure for the Object window
 *--------------------------------------------------------------
 *
 *  Name:    ObjectWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
 *
 *  Purpose: Processes all messages sent to the Object window
 *
 *  Usage:   Called for each message sent to the Object window.
 *
 *  Method:  The Object window processes the messages that tell the
 *           background thread what action to take. Since the object
 *           window is not visible, it will not process any of the
 *           standard window messages.
 *
 *  Returns: Dependent upon message sent
 *
\****************************************************************/
MRESULT EXPENTRY ObjectWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   MRESULT  sRC;

   switch(msg)  {
      /*-------------------------------------------------------*\
       *  Include any user defined messages to determine which
       *  action the background thread should take
      \*-------------------------------------------------------*/
   default:
      sRC = WinDefWindowProc(hwnd, msg, mp1, mp2);
      return sRC;
    }

    /* This routine currently doesn't use the hwnd, mp1, mp2 parameter
     *  but it is referenced here to prevent an 'Unreferenced Parameter'
     *  warning at compile time. 
     */

    return (MRESULT)0L;

}   /* ObjectWndProc() */
