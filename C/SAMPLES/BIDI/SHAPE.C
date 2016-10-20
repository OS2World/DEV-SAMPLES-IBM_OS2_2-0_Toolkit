/*static char *SCCSID = "@(#)shape.c	6.1 92/02/19";*/
/*************************************************************************
 * File Name     : SHAPE.C
 *
 * Description   : This sample program demonstrates how to use the
 *                 Bidirectional (Bidi) API NlsShapeBidiString.
 *                 This an Arabic specific API and is used to Shape a
 *                 string according to the value of the CSD byte in
 *                 the Bidi attributes given to the API.
 *
 * Concepts      : The orientation byte in the Bidi attributes should
 *                 describe the way the input string was logically sotred,
 *                 i.e RTL or LTR. This is mandatory because the Character
 *                 Shape Determination is dependant on the string
 *                 orientation. If a wrong orientation was specified, a
 *                 wrong output is expected
 *
 * API's         : NlsSetBidiAtt
 *                 NlsQueryBidiAtt
 *                 NlsShapeBidiString
 *                 VioWrtCharStr
 *                 VioScrollUp
 *                 VioSetCurType
 *
 * Required files: To build and run this sample code the following files
 *                 are needed:
 *                 - SHAPE.C
 *                 - SHAPE.DEF
 *                 - SHAPE.MAK
 *                 - SHAPE.LNK
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

#include <string.h>
#include <os2.h>
#include <conio.h>

VOID Initialize(VOID);
VOID ShapeAndDisplay(VOID);
VOID SetCur(INT);

/* Define a variable to save the session Bidi Attributes in it */
ULONG ulOriginalBidiAttr;

/* Define the area where we will get the result
 * of what we want to query from the session   */
BDKVCB bdkvcbSetAttr;

/* Define the parameter to Hide and Restore the cursor */
#define HIDE   -1
#define RESTORE 0

/* Define the buffer for the string to be displayed */
CHAR cString[50];

/*************************************************************************
 * Name          : Main
 *
 * Description   : This is the main part of the program, it first clear
 *                 the screen and then hide the cursor. The string to be
 *                 shaped will be displayed before and after the API
 *                 NlsShapeBidiString is called, with different modes of
 *                 shaping.
 *
 * API's         : NlsSetBidiAtt
 *                 VioScrollUp
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

   /* Call the API to shape the string and wirte it to the screen */
   ShapeAndDisplay();

   /* Wait for Enter key to end the program */

   VioWrtCharStr("Press Enter to end the program", 32, 23, 28, 0l);
   getchar();

   /* Restore the session Bidi attributes  */
   bdkvcbSetAttr.BDAtts = ulOriginalBidiAttr ;

   RC = NlsSetBidiAtt( 0L, (PSETINFO)&bdkvcbSetAttr);
   if( RC != 0)
   {
     printf("\n\nCannot set the session Bidi Attributes RC=%ld\n",RC);
     exit(1);
   }

   /* clear the screen before exit */
   VioScrollUp(0, 0, 24, 79, -1," \x07", 0);

   /* restore the cursor position */
   SetCur(RESTORE);

   return (0);
}
/*************************************************************************
 * Name          : INITIALIZE
 *
 * Description   : This function does save the current Bidi attributes of
 *                 the session in a global variable, and set session with
 *                 its own Bidi attributes to protect the displayed shaped
 *                 string from been processed again according to the session
 *                 Bidi attributes.
 *                 Then the function displays some static text and also the
 *                 String to be shaped before any shaping processing.
 *
 * API's         : NlsQueryBidiAtt
 *                 NlsSetBidiAtt
 *                 VioWrtCharStr
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
          CHAR cScreen[40];
          }mssg1[4];

   struct {
           CHAR cScreen[12];
           }mssg2[8];

   /* First we need to set the session Bidi attributes to have the
    * shaping mode as Passthru. This will let the Bidi support
    * to display the characters on the screen as they are.
    * i.e without any additional shape processing.
    * This way, when the application does its own shaping processing
    * the output characters to the screen will not be corrupted. */

   /* The length here is 8 to query only on the Bidi attribute   */

   bdkvcbSetAttr.BDLength = 8;

   RC = NlsQueryBidiAtt( 0L,(PRETINFO)&bdkvcbSetAttr);

   if(RC != 0)
   {
      printf("\n\nError in query the Bidi Attributes RC=%ld\n",RC);
      exit(1);
   }

   /* Now we save the initial value of the Bidi attributes so that
    * so that we set back the session with it before the program terminates*/

   ulOriginalBidiAttr = bdkvcbSetAttr.BDAtts;

  /* Here we set the shaping byte value to passthru */

   bdkvcbSetAttr.BDAtts = BD_LEVEL |
                          BD_SUPPORT |
                          BDORIENT_LTR |
                          BDNUM_PASSTHRU |
                          BDCSD_PASSTHRU;

  /* Now let's set the session Bidi attributes with the new value  */

   RC = NlsSetBidiAtt( 0L, (PSETINFO)&bdkvcbSetAttr);
   if( RC != 0)
   {
       printf("\n\nCannot set the session Bidi Attributes RC=%ld\n",RC);
       exit(1);
   }

   /* Initialize the structures with the characters to be displayed */
   strcpy(mssg1[0].cScreen, "Calling NlsShapeBidiString you can");
   strcpy(mssg1[1].cScreen, "  Change the following String to  ");
   strcpy(mssg1[2].cScreen, "    any of the different Arabic   ");
   strcpy(mssg1[3].cScreen, "             Shapes               ");

   /* In this for loop, we increment the iRow after the display of each
    * string in the structure to jump to another line, keeping the value
    * of the iCol value fixed to have the strings indented */
   for(iI = 0, iRow = 2, iCol = 23; iI < 4; iI++, iRow++)

   VioWrtCharStr(mssg1[iI].cScreen, strlen(mssg1[iI].cScreen), iRow, iCol, 0l);


   /* Initialize the second structure with the characters to be displayed */
   strcpy(mssg2[0].cScreen, "String    :");
   strcpy(mssg2[1].cScreen, "Base      :");
   strcpy(mssg2[2].cScreen, "Initial   :");
   strcpy(mssg2[3].cScreen, "Middle    :");
   strcpy(mssg2[4].cScreen, "Final     :");
   strcpy(mssg2[5].cScreen, "Isolated  :");
   strcpy(mssg2[6].cScreen, "Shaped LTR:");
   strcpy(mssg2[7].cScreen, "Shaped RTL:");


   VioWrtCharStr(mssg2[0].cScreen, strlen(mssg2[0].cScreen), 8, 5, 0l);

   for(iI = 1, iRow = 11, iCol = 5; iI <= 7; iI++, iRow++)

   VioWrtCharStr(mssg2[iI].cScreen, strlen(mssg2[iI].cScreen), iRow, iCol, 0l);

   /* Display the string before it is shaped.
    * Note that this is a Left To Right string, because the logical
    * order of the characters stored is from the end of the buffer
    * to the begining, i.e from high to low memory */

   strcpy(cString,"Éáûª¯ïäÇ Éê©ÑÙäÇ ºèÑ®äÇ äÇüÔÃ åÏÎÊ¼ê ­ïÇòÑÈä ä¨Ëï");
   VioWrtCharStr(cString, strlen(cString), 8, 18, 0l);
}
/*************************************************************************
 * Name          : SHAPEANDDISPLAY
 *
 * Description   : This function will show how to use the Bidi API
 *                 NslShapeBidiString, and what are the different shaping
 *                 modes available and how to pass them to the API.
 *                 The function will display the string after each call to
 *                 NslShapeBidiString, according to different shaping
 *                 attributes.
 *
 * API's         : NlsShapeBidiString
 *                 VioWrtCharStr
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/
VOID ShapeAndDisplay(VOID)
{
   APIRET RC;
   INT   iRow, iCol;
   ULONG ulBidiAttr,ulBidiAttrIso;
   ULONG ulEffect ;
   CHAR  cTarget[50];
   ULONG ulLength;
   ULONG ulIncrement ;

   /* The Effect paramter is reserved to be zero */
   ulEffect = 0;

   ulLength = strlen(cString);

   /* The string contains successive characters, i.e the cell here is
    * only one character, i.e Increment =1 */
   ulIncrement = 1;

   iCol = 18;

   /* using the OR operator, we set the bits in the Bidi attributes
    * to describe the orientation of the buffer and the shaping mode
    * that we want as output */

   ulBidiAttr= BD_LEVEL |
               BD_SUPPORT |
               BDORIENT_LTR |
               BDNUM_PASSTHRU |
               BDCSD_BASE ;

    /* In this for loop, we depend on the fact that if we increment
     * the Bidi attributes by 1, starting from the value of the
     * BASE shapes, we get another shaping attribute, until we reach
     * the ISOLATED shapes mode, which is the value in ulBidiAttrIso.
     * We also increment the iRow value by one, to get a new line to
     * display each mode  */

   ulBidiAttrIso = ulBidiAttr | BDCSD_ISOLATED;

   for(iRow=11; ulBidiAttr <= ulBidiAttrIso ; ulBidiAttr++, iRow++)

   {
       RC=NlsShapeBidiString(ulBidiAttr,ulEffect, cString,
                             cTarget, ulLength, ulIncrement);

       /* If there is an error returned */
       if(RC != 0)
       {
       printf ("RC1 =%ld\n",RC);
           exit(1);
       }

       /* terminate the string with a NULL */
       cTarget[strlen(cString)] = '\0';

       /* display it on the screen */
       VioWrtCharStr(cTarget, strlen(cTarget), iRow, iCol, 0l);
    }

   /* Now let's put the shaping mode to be Automatic character determination
    * (shaping) ON, keeping the orientation to be Left To Right. */

   ulBidiAttr= BD_LEVEL |
               BD_SUPPORT |
               BDORIENT_LTR |
               BDNUM_PASSTHRU |
               BDCSD_AUTOMATIC;

    RC=NlsShapeBidiString(ulBidiAttr ,ulEffect,cString,
                          cTarget, ulLength, ulIncrement);

    if(RC != 0)
    {
       printf ("RC2 =%ld\n",RC);
       exit(1);
    }

    cTarget[strlen(cTarget)] = '\0';
    VioWrtCharStr(cTarget, strlen(cTarget), iRow, iCol, 0l);

   /* Just for the sake of demonstration, let's intentionally set the
    * the orientation bit to Right To Left, which is the wrong orientation
    * of the original string, keeping the shaping mode unchanged */

   ulBidiAttr= ulBidiAttr | BDORIENT_RTL;

    RC=NlsShapeBidiString(ulBidiAttr ,ulEffect,cString,
                          cTarget, ulLength, ulIncrement);

    if(RC != 0)
    {
       printf ("RC3 =%ld\n",RC);
       exit(1);
    }
    cTarget[strlen(cTarget)] = '\0';

    VioWrtCharStr(cTarget, strlen(cTarget), iRow+1, iCol, 0l);
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

