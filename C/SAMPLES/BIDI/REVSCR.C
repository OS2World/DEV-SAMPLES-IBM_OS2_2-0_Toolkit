/*static char *SCCSID = "@(#)revscr.c	6.1 92/02/19";*/
/*************************************************************************
 * File Name     : REVSCR.C
 *
 * Description   : This sample program demonstrates how to use the
 *                 Bidirectional (Bidi) API NlsQueryBidiAttr and
 *                 NlsSetBidiAttr to change the screen and keyboard
 *                 attributes of a session.
 *
 * API's         : NlsSetBidiAttr
 *                 NlsQuerytBidiAttr
 *                 VioWrtCharStr
 *                 VioScrollUp
 *                 VioSetCurPos
 *
 * Required files: To build and run this sample code the following files
 *                 are needed:
 *                 - REVSCR.C
 *                 - REVSCR.DEF
 *                 - REVSCR.MAK
 *                 - REVSCR.LNK
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
/* Including the system return codes, will include
 *the bidi return error codes as well */
#define INCL_DOSERRORS
/* This to include the Bidi header file */
#define INCL_BDCALLS

#include <os2.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

/* declairation of the functions used */
VOID GetAttr(VOID);
VOID SetAttr(VOID);
VOID Toggle(VOID);
VOID Initialize(VOID);

#define ROW 15
#define COL 5

/* define the structures that are going to be used to Set and Query
 * the screen and keyboard attributes   */
BDKVCB bdkvcbRetAttr, bdkvcbSaveAttr;


/*************************************************************************
 * Name          : Main
 *
 * Description   : This is the main part of the program, it first clear
 *                 the screen and then queries the screen and keyboard
 *                 attributes, change it, and set it, so that the screen
 *                 orientation becomes RLT.
 *
 * API's         : NlsSetBidiAttr
 *                 VioScrollUp
 *                 VioSetCurPos
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/
INT main(SHORT sArgc,CHAR **ppArgv)
{
   INT iCh,
       iRow ;

   iRow = ROW;

   /* clear the screen */
   VioScrollUp(0, 0, 24, 79, -1," \x07", 0);

   /* Query the screen Bidi attributes */
   GetAttr();

   /* Toggle the orientation and the language layer */
   Toggle();

   /* Set the new screen and keyboard attributes */
   SetAttr();

   /* Set the cursor position
    * Note: When running the program, watch where the cursor got set,
    * and remember that the cursor setting was done after we changed
    * the screen orientation */

   VioSetCurPos(iRow, COL, 0);

   /* Display some text to the screen */
   Initialize();

   /* Wait for Enter to end the program */
   getchar ();

   /* Clear the screen */
   VioScrollUp(0, 0, 24, 79, -1," \x07", 0);

   /* Reset the screen orientation and the language layer */
   NlsSetBidiAtt( 0L, (PSETINFO)&bdkvcbSaveAttr);

   return (1);
} /* end of main */

/*************************************************************************
 * Name          : GetAttr
 *
 * Description   : This function issues the NlsQueryBidiAttr to query the
 *                 the screen and keyboard attributes
 *
 * API's         : NlsQueryBidiAttr
 *
 * Parameters    : (VOID)
 *
 * Returns       : None
 *
 ************************************************************************/
VOID GetAttr(VOID)
{
   APIRET RC;                         /* used for error checking */

   /* The length here is 16 to query the Bidi attributes
    *  and the Bidi flags */
   bdkvcbRetAttr.BDLength = 16;

   RC = NlsQueryBidiAtt( 0L,(PRETINFO)&bdkvcbRetAttr);
   if(RC != 0)
   {
      printf("\n\nError in query bidi attr num %d\n",RC);
      exit(1);
   }
}
/*************************************************************************
 * Name          : SetAttr
 *
 * Description   : This function issues the NlsSetBidiAttr to set the
 *                 the screen and keyboard attributes
 *
 * API's         : NlsQueryBidiAttr
 *
 * Parameters    : (VOID)
 *
 * Returns       : None
 *
 ************************************************************************/
VOID SetAttr(VOID)
{
  APIRET RC;

   /* The length here is 16 to set the Bidi attributes
    *  and the Bidi flags */
   bdkvcbRetAttr.BDLength= 16;

   RC = NlsSetBidiAtt( 0L, (PSETINFO)&bdkvcbRetAttr);
   if( RC != 0)
   {
       printf("\n\nError in set Bidi attributes: %d\n",RC);
       exit(1);
   }
}
/*************************************************************************
 * Name          : Toggle
 *
 * Description   : This function uses the Bidi defined values in the
 *                 header file BDCALLS.H to change the attributes, by
 *                 the mean of the operator OR.
 *                 It also saves the original settings before it does
 *                 change it.
 *
 * API's         : None
 *
 * Parameters    : (VOID)
 *
 * Returns       : None
 *
 ************************************************************************/
VOID Toggle(VOID)
{
   /* save the original Bidi attributes settings */
   bdkvcbSaveAttr = bdkvcbRetAttr;

   bdkvcbRetAttr.BDAtts = bdkvcbRetAttr.BDAtts | BDORIENT_RTL;
                              /* here we toggle the orientation,             */
                              /* if left to right, make it right to left     */
                              /* and vise versa                              */

   bdkvcbRetAttr.BDFlags = bdkvcbRetAttr.BDAtts | BDFLAG_LAYER;

}
/*************************************************************************
 * Name          : Initialize
 *
 * Description   : This function is used to display some messages on the
 *                 screen
 *
 * API's         : VioWrtCharStr
 *
 * Parameters    : (VOID)
 *
 * Returns       : None
 *
 ************************************************************************/
VOID Initialize(VOID)
{
   int iI, iCol, iRow, iLength;
   struct {
         char cScreen[45];
         }mssg[5];
   strcpy(mssg[0].cScreen, "neercs eht ,ttAidiBteSslN gnillac retfA");
   strcpy(mssg[1].cScreen, "   reyal egaugnal eht dna ,LTR won si  ");
   strcpy(mssg[2].cScreen, "           lanoitaN won si             ");
   strcpy(mssg[3].cScreen, "  ... sretcarahc emos epyt ot yrT      ");
   strcpy(mssg[4].cScreen, "    margorp eht dne ot retnE sserP     ");
   iLength = strlen(mssg[0].cScreen);
   iCol = 23;
   iRow = 2;
   for( iI = 0; iI < 3; iI++, iRow++)
       VioWrtCharStr(mssg[iI].cScreen, iLength, iRow, iCol, 0l);

       VioWrtCharStr(mssg[3].cScreen, iLength, 8, iCol, 0l);
       VioWrtCharStr(mssg[4].cScreen, iLength, 23, iCol, 0l);
}
