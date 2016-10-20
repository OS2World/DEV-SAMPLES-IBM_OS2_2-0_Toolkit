/***    VLPT.H
 *
 *
 *      MVDM Virtual Printer Exported Definitions
 ****************************************************************************
 *                                                                          *
 *                                                                          *
 *                 Copyright (c) IBM Corporation  1993                      *
 *                           All Rights Reserved                            *
 *                                                                          *
 ****************************************************************************
 *
 *      For include file hierarchy, see MVDM.H
 *
 *
 *
 */

#pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( suspend )
   #endif
#pragma checkout( resume )

#ifndef __VLPT__
#define __VLPT__


/***    VLPT constants
 */


/***    VLPT data types
 */


/***    VLPT function prototypes
 */
VOID VDHENTRY VDHPrintClose(HVDM);

#endif /* __VLPT__ */

#pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( resume )
   #endif
#pragma checkout( resume )
