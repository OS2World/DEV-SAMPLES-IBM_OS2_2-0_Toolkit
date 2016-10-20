/*static char *SCCSID = "@(#)edit.c	6.1 92/02/19";*/
/*************************************************************************
 * File Name     : EDIT.C
 *
 * Description   : This sample program demonstrates how to use the API
 *                 NlsEditShape. This Bidirectional (Bidi) API is an
 *                 Arabic specific one, and it is use to shape
 *                 (according to the value of the CSD byte in the
 *                 Bidi Attributes) one character knowing its surronding
 *                 characters (wich may get changed as well)
 *
 * Concepts      : When using this API in the Edit shape mode (effect =1),
 *                 the current charater is read, as well as the three
 *                 preceeding characters and the two succeeding ones.
 *                 Based on these readings, the shape of the current
 *                 character is determined, also the surrounding characters
 *                 may change in shape to have a homogenous string of
 *                 6 characters. the output is then written to the output
 *                 buffer.
 *                 If the surrounding characters could not be read or
 *                 written by the API, probably because the current
 *                 character is so close to the buffer boundary, the
 *                 the missing characters are assumed to be blanks,
 *                 and shaping contimues. However, if the buffer is
 *                 too small, then the expected output may not be correct,
 *                 that is why a warning error (NO_ERROR_BIDI_RW_INCOMPLETE)
 *                 is returned, but the API does not exit.
 *                 Note that the surrounding characters should have the
 *                 correct shape in order that the current is shaped
 *                 correctly.
 *
 *                 When using this API in the Input shape mode (effect=0),
 *                 the current character is read, as well as its two `
 *                 preceeding characters.Based on this readings and based
 *                 on the value of the CSDState parameter, the current
 *                 character is shaped and its two preceeding characters
 *                 may change.
 *                 To shape an buffer, this API will be called more than
 *                 once to shape each character. On its first invocation,
 *                 the value of CSDState should be Zero. This value will
 *                 change after the API finishes, to the proper value
 *                 needed to shape the next character in the buffer, and
 *                 which will be used by the API the next time it is
 *                 invoked. That is why the value of the CSDState should
 *                 be preserved between calls until shaping the whole
 *                 buffer is complete.
 *
 * API's         : NlsEditShape
 *                 NlsQueryBidiAtt
 *                 NlsSetBidiAtt
 *                 VioWrtCharStr
 *                 VioScrollUp
 *                 VioSetCurType
 *
 * Required files: To build and run this sample code the following files
 *                 are needed:
 *                 - EDIT.C
 *                 - EDIT.DEF
 *                 - EDIT.MAK
 *                 - EDIT.LNK
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
 *                 the screen and then hide the cursor. The character in
 *                 the string to be shaped will be displayed before and
                   after the NlsEditShape is called.
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

   VioWrtCharStr("Press Enter to end the program", 32, 23, 23, 0l);
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
           CHAR cScreen[15];
           }mssg2[3];

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
   strcpy(mssg1[0].cScreen, "The original incorrect string is :");
   strcpy(mssg1[1].cScreen, "Let's insert a space in the middle.");
   strcpy(mssg1[2].cScreen, "Now, to correct the output, we use");
   strcpy(mssg1[3].cScreen, "         NlsEditShape.            ");

   /* In this for loop, we increment the iRow after the display of each
    * string in the structure to jump to another line, keeping the value
    * of the iCol value fixed to have the strings indented */
   for(iI = 0, iRow = 4, iCol = 23; iI < 3; iI++, iRow=iRow+5)
      VioWrtCharStr(mssg1[iI].cScreen, strlen(mssg1[iI].cScreen),
                    iRow, iCol, 0l);
   /* write the last message */
   VioWrtCharStr(mssg1[3].cScreen, strlen(mssg1[3].cScreen),
                 iRow-4, iCol, 0l);


   /* Initialize the second structure with the characters to be displayed */
   strcpy(mssg2[0].cScreen, "öÈÑìÌå¨æÑÈ  ");
   strcpy(mssg2[1].cScreen, "öÈÑì Ìå¨æÑÈ ");

   /* This is the string that is going to be passed to NlsEditShape */
   strcpy(cString,"öÈÑì Ìå¨æÑÈ ");

   for(iI = 0, iRow = 7, iCol = 32; iI <= 1; iI++, iRow = iRow+5)

   VioWrtCharStr(mssg2[iI].cScreen, strlen(mssg2[iI].cScreen), iRow, iCol, 0l);

}
/*************************************************************************
 * Name          : SHAPEANDDISPLAY
 *
 * Description   : This function will show how to use the Bidi API
 *                 NslEditShape, and how to fill the needed structures.
 *                 The function will display the string after it is shaped.
 *
 * API's         : NlsEditShape
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
  ULONG ulBidiAttr;
  ULONG ulEffect=1L;


  /* Defining the input/output structure*/
  CSDRec  PCSDSourceAndTarget;

  ULONG  ulCsdState=0;
  ULONG  ulIncrement =1L;

  ulBidiAttr =  BD_LEVEL
              | BD_LEVEL
              | BDORIENT_LTR
              | BDNUM_PASSTHRU
              | BDCSD_AUTOMATIC;

  /* This value is reserved to be always 16 */
  PCSDSourceAndTarget.RecLength = 16L;

  /* Here we point to the character were we want to shape, in
   * our case is the character that is newly introduced in
   * the string .. i.e the blank.  */
  PCSDSourceAndTarget.BufferIndex = 4L;

  /* The length of the whole buffer */
  PCSDSourceAndTarget.BufferLength = strlen(cString);

  /* assigne the address of the string */
  PCSDSourceAndTarget.Buffer = (PCHAR)cString;

  RC = NlsEditShape(ulBidiAttr,
                    ulEffect,
                    &PCSDSourceAndTarget,
                    &PCSDSourceAndTarget,
                    &ulCsdState,
                    ulIncrement);

  if(RC != 0)
  {
    printf ("RC1 =%ld\n",RC);
    exit(1);
  }

    VioWrtCharStr(cString, strlen(cString), 18, 32, 0l);
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

