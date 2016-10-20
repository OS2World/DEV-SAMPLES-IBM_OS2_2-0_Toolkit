/******************************************************************************/
/*                                                                            */
/*                     IBM Sample Virtual Device Driver                       */
/*                                                                            */
/*                 Copyright (c) IBM Corporation 1993                         */
/*                         All Rights Reserved                                */
/*                                                                            */
/*   DISCLAIMER OF WARRANTIES.  The following [enclosed] code is              */
/*   sample code created by IBM Corporation. This sample code is not          */
/*   part of any standard or IBM product and is provided to you solely        */
/*   for  the purpose of assisting you in the development of your             */
/*   applications.  The code is provided "AS IS", without                     */
/*   warranty of any kind.  IBM shall not be liable for any damages           */
/*   arising out of your use of the sample code, even if they have been       */
/*   advised of the possibility of   such damages.                            */
/*                                                                            */
/************************** START OF SPECIFICATIONS ***************************/
/*                                                                            */
/*   SOURCE FILE NAME:  VDFTPDD.C                                             */
/*                                                                            */
/*   DESCRIPTIVE NAME:  Initialize virtual DFT device driver(VDFT)            */
/*                                                                            */
/*   FUNCTION: These routines comprise the Virtual DFT device driver which    */
/*             supports the 3270 DFT adapter card.                            */
/*                                                                            */
/*   NOTES:    These routines work in conjunction with DFT_DDM.ASM ( the      */
/*             DFT physical device driver.                                    */
/*                                                                            */
/*   RESTRICTIONS: None                                                       */
/*                                                                            */
/*   ENTRY POINTS:                                                            */
/*             VDFTPDDProc - VDFT entry point for PDFT                        */
/*                                                                            */
/*   EXTERNAL REFERENCES:                                                     */
/*             VDHSetVIRR  - start simulating Interrupts to the VDM           */
/*                                                                            */
/**************************** END OF SPECIFICATIONS ***************************/

#define INCL_VDH
#define NULL 0

#include <mvdm.h>                       /* VDH services, etc.        */
#include <basemid.h>                    /* message numbers           */
#include <builtin.h>                    /* builtin functions         */
#include "VDFTP.H"                      /* Local Stuff               */

int _dllentry=1;   // We must avoid standard DLL Library inclusion
                   // /gp option was used in compilation
                   // This option is protected DLL


/*                                                                   */
/*                 GLOBAL DATA AREA FOR VDFT                         */
/*                                                                   */

extern HIRQ hirq_DFT;                          // holds handle for EOI hook

extern HVDM HVDM_Owner;                        // hvdm of owner
extern INT   Status_byte;                      // Status Register value

extern BOOL  interruptsnotenabled;             // T = interrupts not enabled in DD
extern BOOL  wait_for_EOI;                     // T = EOI not done yet
extern BOOL  wait_for_status_out;              // T = out to status port not done yet


/* Global Code begins here */

/***************************START OF SPECIFICATIONS ***********************/
/*                                                                        */
/* SUBROUTINE NAME: VDFTPDDProc                                           */
/*                                                                        */
/*DESCRIPTIVE NAME: Routine to service the PDD at interrupt time.         */
/*                                                                        */
/*                                                                        */
/* FUNCTION:  The function of this routine is to service the interrupt    */
/*            when received from the PDD. It verifies this VDD is the     */
/*            owner.  The interrupt will then be passed to the VDM's      */
/*            context, to be serviced next time the VDM gains context     */
/*                                                                        */
/* CONTEXT:  VDM task time                                                */
/*                                                                        */
/* ENTRY POINT: VDFTPDBDestroy                                            */
/*        LINKAGE:   CALL NEAR 32                                         */
/*                                                                        */
/* INPUT:                                                                 */
/*          ulFunc - request function                                     */
/*          f16p1  - parameter 1                                          */
/*          f16p2  - parameter 2                                          */
/*                                                                        */
/* EXIT-NORMAL: return TRUE                                               */
/*                                                                        */
/* EXIT-ERROR: return FALSE - requestor not valid                         */
/*                                                                        */
/* EXIT-NORMAL:  return byte of data from status port for DFT             */
/*                                                                        */
/* EXIT-ERROR:    NONE                                                    */
/*                                                                        */
/* EFFECTS:       NONE                                                    */
/*                                                                        */
/* INTERNAL REFERENCES:                                                   */
/*                                                                        */
/* EXTERNAL REFERENCES:   VDHSetVIRR  - start simulating Interrupts       */
/*                                            to the VDM                  */
/*                                                                        */
/**************************************************************************/

SBOOL VDDENTRY VDFTPDDProc(ULONG ulFunc, F16PVOID f16p1, F16PVOID f16p2)
{
#ifdef  DEBUG
           _interrupt(3);
#endif

    /*---------------------------------------------------------------*/
    /* Make sure a VDM has the port as direct access.  If not,       */
    /* ignore the interrupt.                                         */
    /*---------------------------------------------------------------*/

        if  ( HVDM_Owner )
        {

           Status_byte = __inpb (StatusReg);
           __outpb (StatusReg, Status_byte);

    /*---------------------------------------------------------------*/
    /* Send the interrupt to the VDM's context.                      */
    /*---------------------------------------------------------------*/
           interruptsnotenabled = TRUE;
           wait_for_status_out = TRUE;
           wait_for_EOI = TRUE;
           VDHSetVIRR (HVDM_Owner,hirq_DFT);

           return TRUE;

       }

       return FALSE;

 }

/* Global Code ends here */

