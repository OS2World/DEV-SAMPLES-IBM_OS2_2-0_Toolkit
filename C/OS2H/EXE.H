/*static char *SCCSID = "@(#)exe.h	6.3 92/03/15";*/
/*static char *SCCSID = "@(#)exe.h	6.3 92/03/15";*/
/****************************** Module Header ******************************\
*                                                                          *
* Copyright (c) 1987  - 1992 IBM Corporation                               *
*                                                                          *
* Module Name: EXE.H                                                       *
*                                                                          *
* EXE header format.                                                       *
*                                                                          *
\***************************************************************************/

#ifdef __IBMC__
#pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( suspend )
   #endif
#pragma checkout( resume )
#endif

#ifndef __EXE__
#define __EXE__

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

typedef WORD bbmask;

struct exe {
        WORD eid;                       /* contains EXEID, below */
        WORD elast;                     /* # of bytes in last page */
        WORD epagsiz;                   /* # of pages in whole file */
        WORD erelcnt;                   /* # of relocation entrys */
        WORD ehdrsiz;                   /* size of header, in paragraphs */
        WORD eminfre;                   /* min # of free paragraphs needed */
        WORD emaxfre;                   /* max # of free paragraphs needed */
        WORD eiSS;                      /* initial SS value */
        WORD eiSP;                      /* initial SP value */
        WORD enegsum;                   /* negative sum of entire file */
        WORD eiIP;                      /* initial IP value */
        WORD eiCS;                      /* initial CS value */
        WORD ereloff;                   /* offset in file of relocation table */
        WORD eovlnum;                   /* number of the overlay */

/*      the following fields may not be present.
 *              ereloff = 28            not present
 *                      = 30            exe.ever present and valid
 *                      = 32            exe.ever field contains garbage
 *              ereloff > 32            exe.ever present and valid
 *                                              = 0 if "don't know"
 */

        WORD ever;                      /* version # of producing linker */
        WORD dumy;                      /* unused */

/*      the following fields may not be present - if the exe.ereloff
 *      value encompasses the fields then they are present and valid.
 */

        bbmask  ebb;                    /* behavior bits */
        WORD dumy2[7];                  /* must be 0 until defined */
};


#define EXEID 0x5a4d                    /* magic ID value */

#endif /* __EXE__ */

#ifdef __IBMC__
#pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( resume )
   #endif
#pragma checkout( resume )
#endif
