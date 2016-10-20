/*static char *SCCSID = "@(#)setprint.c	6.2 92/02/24";*/
/*************************************************************************
 * File Name     : SETPRINT.C
 *
 * Description   : This sample program demonstrates how to use the
 *                 Bidirectional (Bidi) API NlsSetBidiPrint.
 *                 This Bidi API is use to send the Bidi attriubtes
 *                 of the string we want to print, to the Bidi
 *                 printer support. Accordingly, the string will be
 *                 printed following this attributes. This is independant
 *                 from the current printer Bidi attriubes.
 *
 * Considerations: Before using this program, make sure that the Bidi
 *                 printer support is active (RUN= statement in the
 *                 CONFIG.SYS exists) and it is loading the correct CFG
 *                 that match the type of printer connected.
 *                 Also make sure that proper font is been dowloaded to
 *                 the printer.
 *
 * API's         : NlsSetBidiPrint
 *                 VioWrtCharStr
 *                 VioScrollUp
 *                 VioSetCurType
 *
 * Required files: To build and run this sample code the following files
 *                 are needed:
 *                 - SETPRINT.C
 *                 - SETPRINT.DEF
 *                 - SETPRINT.MAK
 *                 - SETPRINT.LNK
 *
 *  Copyright (C) 1991 IBM Corporation
 *
 *      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is
 *      sample code created by IBM Corporation. This sample code is not
 *      part of any standard or IBM product and is provided to you solely
 *      for  the purpose of assisting you in the development of your
 *      applications.  The code is provided "AS IS", without
 *      warranty of any kind.  IBM shall not be liable for any damages
 *      arising out of your use of the sample code, even if they have been
 *      advised of the possibility of such damages.                                                    *
 ************************************************************************/
#define INCL_BASE
/* To include the neccessary header files for Bidi */
#define INCL_DOSERRORS
#define INCL_BDCALLS
#define INCL_DOSFILEMGR
#define PRINTER  "PRN"

#include <string.h>
#include <os2.h>
#include <conio.h>
#include <stdio.h>

VOID Initialize(VOID);
VOID SendAttThenJob(VOID);
VOID SetCur(INT);

/* Define the parameter to Hide and Restore the cursor */
#define HIDE   -1
#define RESTORE 0

/* Define the buffer for the string to be printed */
CHAR cString[30];

/*************************************************************************
 * Name          : Main
 *
 * Description   : This is the main part of the program, it first clears
 *                 the screen and then hides the cursor. The string to be
 *                 printed will be displayed on the screen, and after
 *                 Hitting Enter, it will go to the printer associated
 *                 with its own attributes.
 *
 * API's         : VioScrollUp
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/

INT main(SHORT sArgc,CHAR **ppArgv)
{
   APIRET RC;

   /* clear the screen  */
   VioScrollUp(0, 0, 24, 79, -1," \x07", 0);

   /* hide the cursor */
   SetCur(HIDE);

   /* Write the static text to the screen and the string that
    * is needed to be shaped */
   Initialize();

   VioWrtCharStr("Press Enter to continue or Ctrl-c to Exit", 43, 15, 23, 0l);
   getchar();

   /* Call the API to shape the string and wirte it to the screen */
   SendAttThenJob();

   VioWrtCharStr("Press Enter to end the program", 32, 23, 23, 0l);
   getchar();

   /* clear the screen before exit */
   VioScrollUp(0, 0, 24, 79, -1," \x07", 0);

   /* restore the cursor position */
   SetCur(RESTORE);

   return (0);
}
/*************************************************************************
 * Name          : INITIALIZE
 *
 * Description   : This function displays some static text  on the screen
                   and also the String to print before it is printed.
 *
 * API's         : VioWrtCharStr
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/
VOID Initialize(VOID)
{
   INT iI, iRow, iCol;

   APIRET  RC;

   /* define structures to be array of strings to contain the static
    * text to be wirtten on the screen  */
   struct {
          CHAR cScreen[45];
          }mssg1[2];

   /* Initialize the structures with the characters to be displayed */
   strcpy(mssg1[0].cScreen, " First, make sure that the Bidi Printer");
   strcpy(mssg1[1].cScreen, "Support is running with the correct CFG..");

   /* In this for loop, we increment the iRow after the display of each
    * string in the structure to jump to another line, keeping the value
    * of the iCol value fixed to have the strings indented */
   for(iI = 0, iRow = 3, iCol = 23; iI < 2; iI++, iRow++)
     VioWrtCharStr(mssg1[iI].cScreen, strlen(mssg1[iI].cScreen),
                   iRow, iCol, 0l);


   strcpy(cString,"This is a text sample");
   VioWrtCharStr(cString, strlen(cString), 8, 23, 0l);

}
/*************************************************************************
 * Name          : SendAttThenJob
 *
 * Description   : This function will show how to use the Bidi API
 *                 NslSetBidiPrint.
 *                 The function will also display the status of the
 *                 string to print.
 *
 * API's         : NlsSetBidiPrint
 *                 VioWrtCharStr
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/
VOID SendAttThenJob(VOID)
{

   APIRET   RC=0;
   HFILE    hfileFileHandle;
   ULONG    ulBidiAttr;
   ULONG    ulLength=8L;
   ULONG    ulAction = 0;
   ULONG    ulBytesWritten;


   ulBidiAttr =  BD_LEVEL
               | BD_SUPPORT
               | BDORIENT_RTL
               | BDNUM_PASSTHRU
               | BDCSD_PASSTHRU;

   RC = DosOpen(PRINTER,
                &hfileFileHandle,
                &ulAction,
                0L,
                FILE_SYSTEM,
                OPEN_ACTION_OPEN_IF_EXISTS,
                OPEN_ACCESS_WRITEONLY |  OPEN_SHARE_DENYREAD,
                (PEAOP2)NULL);
   if (RC)
   {
     printf ("Cannot open the Printet to write RC=%ld\n",RC);
     exit (1);
   }

   RC = NlsSetBidiPrint( ulBidiAttr, ulLength, (HFILE)hfileFileHandle);

   if (RC)
   {
     printf ("Error in sending string's attributes to the printer RC=%ld\n",RC);
     exit (1);
   }
   else
   {
     RC = DosWrite(hfileFileHandle,
                   cString,
                   strlen(cString),
                   &ulBytesWritten);

     if (RC)
     {
       printf ("Error in writting the string to the printer RC=%ld\n",RC);
       exit(1);
     }
     else
     {
       VioWrtCharStr("The string is been sent to the printer", 40, 18, 23, 0l);
     }
   }

   RC = DosClose(hfileFileHandle);
   if (RC)
   {
     printf ("Error in closing the printer device RC=%ld\n",RC);
     exit (1);
   }
}
/*************************************************************************
 * Name          : SET_CUR
 *
 * Description   : This function hides or restores the cursor position.
 *
 * API's         : VioSetCurType
 *
 * Parameters    : (INT flag)
 *                 flag indicates whether we want ot hide or restore
 *                 the cursor.
 *
 * Returns       : None
 *
 ************************************************************************/

VOID SetCur(INT iFlag)
{
   HVIO HVIOhandle = 0;
   VIOCURSORINFO cursor;

   cursor.yStart  = 3;
   cursor.cEnd    = 5;
   cursor.cx      = 0;
   cursor.attr    = iFlag;

   VioSetCurType(&cursor, HVIOhandle);
}

