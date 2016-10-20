/*static char *SCCSID = "@(#)constr.c	6.1 92/02/19";*/
/*************************************************************************
 * File Name     : CONSTR.C
 *
 * Description   : This sample program demonstrates how to use the API
 *                 NlsConvertBidiString. This Bidirectional (Bidi) API
 *                 is use to convert the bidi string from one set of
 *                 attributes (FromAttr, which describe the Bidi
 *                 attributes of the input buffer) to another set of
 *                 attributes (ToAttr, wich describes the Bidi attibutes
 *                 of the output buffer).
 *
 * Concepts      : When there is a change between the FromAttr and ToAttr
 *                 the API does the necessary to convert the input buffer
 *                 to the ToAttr format, and put it in the output buffer.
 *                 If FromAttr equals to ToAttr, no Bidi conversion will
 *                 take place, and the input Buffer will be copied into
 *                 the output buffer.
 *
 * API's         : NlsSetBidiAtt
 *                 NlsQueryBidiAtt
 *                 NlsConvertBidiString
 *                 VioWrtCharStr
 *                 VioScrollUp
 *                 VioSetCurType
 *
 * Required files: To build and run this sample code the following files
 *                 are needed:
 *                 - constr.C
 *                 - constr.DEF
 *                 - constr.MAK
 *                 - constr.LNK
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
VOID ConvertAndDisplay(VOID);
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
CHAR cString[20];

/*************************************************************************
 * Name          : Main
 *
 * Description   : This is the main part of the program, it first clear
 *                 the screen and then hide the cursor. The string to be
 *                 converted will be displayed before and after the API
 *                 NlsConvertBidiString is called.
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

   /* Call the API to shape the string and write it to the screen */
   ConvertAndDisplay();

   /* Wait for Enter key to end the program */

   VioWrtCharStr("Press Enter to end the program", 32, 23, 26, 0l);
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
 *                 String to be converted before calling the API.
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
          }mssg1[3];

   struct {
           CHAR cScreen[45];
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
   strcpy(mssg1[0].cScreen, "Here we will display the Bidi string,");
   strcpy(mssg1[1].cScreen, " its Bidi attr are RTL, Arabic Num,");
   strcpy(mssg1[2].cScreen, "    and Base shapes characters.   ");

   /* In this for loop, we increment the iRow after the display of each
    * string in the structure to jump to another line, keeping the value
    * of the iCol value fixed to have the strings indented */
   for(iI = 0, iRow = 2, iCol = 23; iI < 3; iI++, iRow++)
     VioWrtCharStr(mssg1[iI].cScreen, strlen(mssg1[iI].cScreen),
                   iRow, iCol, 0l);

   /* Display the string before it is shaped.
    * Note that this is a Right To Left string, because the logical
    * order of the characters stored is from the begining of the Buffer
    * to the end, i.e from low to high memory.
    * Because the screen attributes is LTR, then this RTL string will
    * not be displayed in a readable form, however if we would have
    * set the screen bidi attibutes to RTL before displaying the
    * string, it would be readable.
    * In this example we will keep the screen Bidi attributes to be
    * LTR and we will use the API to convert the string to LTR, so
    * that it can be readable. */

   VioWrtCharStr("NOTE: If the current code page is not 864,   ",
                  47, 7, 21, 0L);
   VioWrtCharStr("the following strings will not be readable.  ",
                 47,  8, 21, 0l);

   strcpy(cString,"ÈÑæÇåÌ ÙÑÈê Ñâå: 1");
   VioWrtCharStr(cString, strlen(cString), 11, 31, 0l);

   /* Initialize the second structure with the characters to be displayed */
   strcpy(mssg2[0].cScreen, "Now lets call the  NlsConvertBdiString, to");
   strcpy(mssg2[1].cScreen, "convert the  above string to be  displayed");
   strcpy(mssg2[2].cScreen, "correctly on the current screen attributes");

   for(iI = 0, iRow = 14, iCol = 21; iI <= 2; iI++, iRow++)
     VioWrtCharStr(mssg2[iI].cScreen, strlen(mssg2[iI].cScreen),
                   iRow, iCol, 0l);

}
/*************************************************************************
 * Name          : ConvertAndDisplay
 *
 * Description   : This function will show how to use the Bidi API
 *                 NslConvertBidiString.
 *                 The function will also displays the string after
 *                 the conversion.
 *
 * API's         : NlsConvertBidiString
 *                 VioWrtCharStr
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/
VOID ConvertAndDisplay(VOID)
{
   APIRET RC;
   INT   iRow, iCol;
   ULONG ulFromAttr,ulToAttr;
   ULONG ulLength;
   ULONG ulIncrement ;
   ULONG ulReserved = 0L;

   ulLength = strlen(cString);

   /* The string contains successive characters, i.e the cell here is
    * only one character, i.e Increment =1 */
   ulIncrement = 1;

   iCol = 31;

   /* using the OR operator, we set the bits in FromAttr, to describe
    * the input string attributes, we know that it is a RTL, contains
    * Arabic numeral, and it is in Base shapes */

   ulFromAttr= BD_LEVEL |
               BD_SUPPORT |
               BDORIENT_RTL |
               BDNUM_ARABIC |
               BDCSD_BASE ;


   /* Now let's compose the ToAttr, we want the output string to be
    * LTR, Hindu numeral, and Shaped (Automatic Shape Determination) */

   ulToAttr= BD_LEVEL |
             BD_SUPPORT |
             BDORIENT_LTR |
             BDNUM_HINDU |
             BDCSD_AUTOMATIC ;


  /* calling the API.. to convert the string */
  RC = NlsConvertBidiString (cString,
                             cString,
                             ulLength,
                             ulIncrement,
                             ulFromAttr,
                             ulToAttr,
                             ulReserved);

  if (RC!=0)
     printf("RC=%ld\n",RC);

  /* NOTE: If the screen attributes were equal Hindi and Automatic, we
   * will obtain the same result on the screen if we called the API
   * NlsInverseString. In that case, the Bidi Screen Handler will
   * do the numeral and the shaping processing.
   * In addition, if the screen attributes (direction) was also RTL,
   * then we do not need to do any processing because the Bidi Screen
   *  Handler will do the string inversion.  */

  /* display the target buffer */
    VioWrtCharStr(cString, strlen(cString), 19, iCol, 0l);

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

