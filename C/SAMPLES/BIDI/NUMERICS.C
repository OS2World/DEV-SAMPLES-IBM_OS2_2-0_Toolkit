/*static char *SCCSID = "@(#)numerics.c	6.1 92/02/19";*/
/*************************************************************************
 * File Name     : NUMERICS
 *
 * Description   : This sample program demonstrates how to use the
 *                 Bidirectional (Bidi) API NlsConvertBidiNumerics.
 *                 This is an Arabic specific API and it is used to
 *                 to convert the Arabic numerals to Hindu shapes
 *                 for presentation purposes, or vice versa for
 *                 storage purposes.
 *
 * Concepts      : It is advisable that the Numeral should be left as true
 *                 ones (0x30-0x39), for storage and processing.
 *
 * API's         : NlsConvertBidiNumerics
 *
 * Required files: To build and run this sample code the following files
 *                 are needed:
 *                 - NUMERICS.c
 *                 - NUMERICS.DEF
 *                 - NUMERICS.MAK
 *                 - NUMERICS.LNK
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
#define INCL_DOSERRORS
#define INCL_BDCALLS    /* This is to include the Bidi headers */

#include <os2.h>
#include <stdio.h>

/*************************************************************************
 * Name          : Main
 *
 * Description   : This is the main part of the program, it calls the
 *                 Bidi API to convert all the Arabic numerals in a
 *                 String to Hindu numerals, according to the value
 *                 of the numerics byte in the Bidi attributes passed.
 *
 * API's         : NlsConvertBidiNumerics
 *
 * Parameters    : This program does not take any command line parameters
 *
 * Returns       : None
 *
 ************************************************************************/
INT main(SHORT sArgc,CHAR **ppArgv)
{
  static CHAR cNumSourceArray[]={'1','2','3','4','5','\0'};
  char cNumTargetArray [6];

  /* using the OR operator,we construct the value of the Bidi attributes,
   * the value of the numerics byte indicates conversion to Hindi */
  /* Note that the numeral conversion is not dependant on the
   * value of the orientation byte or on the value of the shaping byte
   * in the Bidi attributes */

  ULONG ulBidiAtt = BD_LEVEL
                   | BD_SUPPORT
                   | BDORIENT_RTL
                   | BDNUM_HINDU
                   | BDCSD_AUTOMATIC ;

  APIRET RC=0;
  ULONG ulEffect = 0l;
  ULONG ulIncrement = 1l;
  ULONG ulLength = 5l;
  cNumTargetArray[5]='\0';

  /* Print the string before it is converted */
  printf ("%s\n", cNumSourceArray);

  /* this API will convert all the arabic numerics in a string to hindi  */
  RC = NlsConvertBidiNumerics (ulBidiAtt,
                               ulEffect,
                               cNumSourceArray,
                               cNumTargetArray,
                               ulLength,
                               ulIncrement);
  if (RC!=0)
  {
    printf ("RC=%d\n", RC);
  }

  /* Print the string after the conversion */
  printf ("%s\n", cNumTargetArray);


  printf ("\n\n\n\n Press Enter to end the program \n");


  /* Wait for Enter to End the program */
  getchar();

  return (0);
} /* end of main */
