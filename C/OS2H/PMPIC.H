/****************************** Module Header ******************************\
*
* Module Name: PMPIC.H
*
* OS/2 Presentation Manager Picture functions include file.
*
* Copyright (c) International Business Machines Corporation 1981, 1988-1992
*
* ===========================================================================
*
* Comments at the end of each typedef line give the name tags used in
* the assembler include version of this file.
*
* The assembler include version of this file excludes lines between XLATOFF
* and XLATON comments.
*
\***************************************************************************/

/* XLATOFF */
#ifdef __IBMC__
   #pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( suspend )
   #endif
   #pragma checkout( resume )
#endif
/* XLATON */

#define PIC_INCLUDED




/*** type of picture to print **********************************************/
#define PIP_MF       1L
#define PIP_PIF      2L

/*** type of conversion required *******************************************/
#define PIC_PIFTOMET 0L
#define PIC_SSTOFONT 2L

BOOL APIENTRY PicPrint(HAB hab,
                       PSZ pszFilename,
                       LONG lType,
                       PSZ pszParams);

BOOL APIENTRY PicIchg(HAB hab,
                      PSZ pszFilename1,
                      PSZ pszFilename2,
                      LONG lType);


/* XLATOFF */
#ifdef __IBMC__
   #pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( resume )
   #endif
   #pragma checkout( resume )
#endif
/* XLATON */

/**************************** end of file **********************************/
