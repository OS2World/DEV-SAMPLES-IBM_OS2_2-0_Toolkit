/***    vcmospdd.h
 *
 *
 *
 *      Copyright (c) IBM Corporation 1993
 *
 *      All Rights Reserved
 *
 *      CMOS PDD/VDD shared structures/constants
 *
 */

#pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( suspend )
   #endif
#pragma checkout( resume )

#ifndef __VCMOSPDD__
#define __VCMOSPDD__

// CMOS PDD component definitions

#define CLK_NAME        "CLOCK$"        //registered name for
                                        //  VDD-PDD communication


/***    PDD function commands
 *
 *  Format:
 *      (*fpfnClkVDDProc)(CLKCMD_*, ul1, ul2);
 *
 *  CLKCMD_REGISTER:
 *      ul1 == segment of 16:32 VDD entry point
 *      ul2 ==  offset of 16:32 VDD entry point
 *
 *  CLKCMD_READCMOS:
 *      ul1 == f16pReadReq      //16:16 pointer to read request packet
 *      ul2 == f16pCMOS         //16:16 pointer to output array
 */

#define CLKCMD_REGISTER         PDDCMD_REGISTER     //register VDD
#define CLKCMD_READCMOS         (CLKCMD_REGISTER+1) //read cmos contents

typedef struct readreq_s {
    BYTE        rdrq_CMOSAddr;  //CMOS port number to start reading
    BYTE        rdrq_nbCMOS;    //number of bytes to read
} READREQ;

#endif /* __VCMOSPDD__ */

#pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( resume )
   #endif
#pragma checkout( resume )
