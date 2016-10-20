/*static char *SCCSID = "@(#)invstr.c	6.1 92/02/19";*/
/*************************************************************************
 * File Name     : INVSTR.C
 *
 * Description   : This sample program demonstrates how to use the API
 *                 NlsInverseString. This Bidirectional (Bidi) API is used
 *                 to invert a string from Right To Left, to Left To Right
 *                 and vice versa.
 *
 * Concepts      : Inversion of strings is usually required when converting
 *                 logically ordered characters to visual ordering,
 *                 depending on the orientation of the presentation device
 *                 (screen, printer..)
 *                 Example:
 *                    static CHAR [] ={'f','i','l','e'};
 *                 This string will be in a readable format if it is
 *                 displayed on a LTR screen, however in order to display
 *                 and read it on a RTL screen we should invert it.
 *
 * API's         : NlsInverseString
 *                 VioWrtCharStr
 *                 VioScrollUp
 *                 VioWrtCellStr
 *                 VioSetCurType
 *
 * Required files: To build and run this sample code the following files
 *                 are needed:
 *                 - INVSTR.C
 *                 - INVSTR.DEF
 *                 - INVSTR.MAK
 *                 - INVSTR.LNK
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
#define INCL_DOSERRORS
#define INCL_BDCALLS    /* This is to include the Bidi headers */

#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define HIDE -1                        /* PARAMATER TO HIDE THE SCREEN*/
#define RESTORE 0                      /* paramater to restore the screen */

VOID SetCur(INT);


char string[35] = {'S', 0x78, 't', 0x1e, 'r', 0x49, 'i' ,0x71, 'n',0x4f, 'g',
                  0x2a, ' ',0x0f, 't',0x5f, 'o',0x78, ' ', 0x0f, 'I', 0x5d, 'n',
                  0x70, 'v', 0x5e, 'e', 0x06, 'r', 0x6e, 't', 0x78, '\0'
                   };
                /* this is the string to reverse, each character is followed */
                /* by its attributes.                                        */
                /* In fact this simulates the case of reversing a screen     */
                /* buffer.                                                   */

/*************************************************************************
 * Name          : Main
 *
 * Description   : This is the main part of the program, it first clear
 *                 the screen and then hide the cursor. The string to be
 *                 inverted will be displayed before and after the
 *                 NlsinvsrseString is called.
 *                 Here we will show how to use the API, and what are
 *                 the parameters needed.
 *
 * API's         : NlsInverseString
 *                 VioWrtCharStr
 *                 VioScrollUp
 *                 VioWrtCellStr
 *
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/

INT main(SHORT sArgc,CHAR **ppArgv)
{
   APIRET RC;

   /* Use the VioScrollUp API to clear the screen */
   VioScrollUp(0, 0, 24, 79, -1," \x07", 0);

   /* Call the SetCur() procedure to hide the Cursor */
   SetCur(HIDE);

   RC = VioWrtCharStr("Here is the string we want to invert:",38, 4, 10, 0l);

   /* Write to the Screen the String needed to be inverted */
   RC = VioWrtCellStr(string, strlen(string),7, 10, 0);

   /* Call the NlsInverseString to invert cells of lenght 2 in the string,
    * here the source can equal to target but they should not overlap  */
   RC = NlsInverseString( string, string, strlen(string), 2);

   if (RC != 0)
   {
      printf("\nError in calling the API, RC=%ld\n",RC);
      return(1);
   }

   RC = VioWrtCharStr("Now after calling the API NlsInveseString,",
                       44, 10, 10, 0l);
   RC = VioWrtCharStr("we will get the following inverted string:",
                       43, 11, 10, 0l);

   /* Write the string after inversion on the screen */
   RC = VioWrtCellStr(string, strlen(string),14, 10, 0);

   RC=VioWrtCharStr("Note that each character is still keeping its attribute !",
                     60, 17, 10, 0l);

   RC = VioWrtCharStr("Press Enter to exit the program",32, 23, 20, 0l);

   /* Wait for the Enter Key to end the program */
   getchar();

   /* Clear the screnn */
   RC = VioScrollUp(0, 0, 24, 79, -1," \x07", 0);

   /* Restor the cursor position */
   SetCur(RESTORE);

   return(0);

} /* End of Main */

/*************************************************************************
 * Name          : SETCUR
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
VOID SetCur(INT flag)
{
   HVIO HVIOhandle = 0;
   VIOCURSORINFO cursor;

   cursor.yStart  = 3;
   cursor.cEnd    = 5;
   cursor.cx      = 0;
   cursor.attr    = flag;

   VioSetCurType(&cursor, HVIOhandle);

} /* End of SetCurr */

