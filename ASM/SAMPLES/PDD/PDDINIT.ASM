;**************************************************************************
;                   IBM Sample Physical Device Driver
;
;                   Copyright  IBM Corp 1992.
;***************************************************************************
;Initial Release -David Kenner.

TITLE   PDD_INIT
NAME    PDD_INIT
PAGE    60,132

      .MODEL  large,os_os2
.286P
;***************************************************************************
;CODING CONVENTIONS
; all psuedo-ops, equates, documentation, publics, and externs are in uppercase.
; all cseg and data names are in lowercase.
;
;  ROUTINES IN THIS MODULE:
;             tcacmd_entry               router routine for vtca calls
;             tcaRegister                registers PDD with VDMM
;
;****************************************************************************
INCL_ERRORS     equ 1;
        .XCREF
        .XLIST
        INCLUDE  pdd.inc                ; TCA MACROS AND DEFINITIONS
        INCLUDE  bseerr.inc             ; ERROR csegS FOR DEVICES
        INCLUDE  basemaca.inc           ; VARIOUS MACRO'S
        INCLUDE  devsym.inc
        INCLUDE  devhlp.inc             ; DEFINITION OF DEVICE HELP CALLS
;       INCLUDE  struc.inc              ; STRUCTURED MACRO SUPPORT
        INCLUDE  infoseg.inc            ; STRUCTURES DEFINING THE INFOSEG
        INCLUDE  gas.inc                ; GENERAL ALERT EQUATES
        .LIST
        .CREF

        EXTRN    devhlp_ptr:NEAR        ; POINTER TO DEV HELP ROUTINES
        EXTRN    tcaRegister:FAR        ; PDD REGISTER ROUTINE
        EXTRN    DosWrite:FAR

        page

         stdin   equ  0
         stdout  equ  1
         stderr  equ  2

         cr      equ  0dh
         lf      equ  0ah

dseg    SEGMENT  PUBLIC 'DATA'
dsegend         label      byte
     IdIn      db   cr,lf
               db   "Toolkit Sample Physical Device Driver"
               db   cr,lf
               db   "Copyright IBM Corp. 1991"
               db   cr,lf
     IdIn_len  equ  $-IdIn

     wlen      dw   ?
dseg    ends


;       Request Header

rh          segment at 0
rh_len      db  ?               ; length of request header
rh_unit     db  ?               ; unit cseg (not used)
rh_command  db  ?               ; command cseg
rh_status   dw  ?               ; status
rh_rsvd     dw  2 dup(?)        ; reserved for DOS
rh_q_link   dw  2 dup(?)        ; request queue linkage
rh_dseg     equ $               ; dseg appropriate to the operation

;       Request Header dseg for INIT command
            org rh_dseg-rh
rh_no_units db  ?               ; number of units (not used)
rh_end_addr dd  ?               ; ending address of device driver
rh_bpb      dd  ?               ; address of BPB array (not used)
rh_drive    db  ?

;       Request Header dseg for IOCTL command
            org rh_dseg-rh
rh_ioctl_categ db  ?            ; category cseg
rh_ioctl_funct db  ?            ; function cseg
rh_ioctl_parm  dd  ?            ; addr of parms (offset and selector)
rh_ioctl_buff  dd  ?            ; addr of buffer (offset and selector)

rh          ends

cseg    SEGMENT  PUBLIC 'CODE'
        ASSUME  CS:cseg,DS:dseg,ES:RH

end_of_driver label byte                 ; last byte of device driver    @VDD
;******************* START OF SPECIFICATIONS ************************
;
; SUBROUTINE NAME:  initialize
;
; DESCRIPTIVE NAME: PDD initialize routine
;
; FUNCTION: This entry point is the TCA PDD's initialization routine.
;           This routine will do the device driver  initialization,
;           (save devhlp address and set up overlay point), as well
;           as register the PDD entry point with the VDD.
;
; ENTRY POINT: initialize
;       LINKAGE: CALL NEAR
;
; INPUT: NONE
;
; EXIT-NORMAL: EAX = NONE
;
; EXIT-ERROR:  EAX = NONE
;
; INTERNAL REFERENCES:  NONE
;
; EXTERNAL REFERENCES:  NONE
;
;********************************************************************

Procedure initialize,FAR

;       Initialize device driver - pass back end of driver address

;initialize:

        ASSUME  CS:cseg,DS:dseg,ES:RH
;       int     3
        mov     ax, word ptr rh_end_addr[bx] ; Get address for devhlp routines
        mov     word ptr devhlp_ptr,ax       ;   and store in devhlp_ptr
        mov     ax, word ptr rh_end_addr+2[bx]
        mov     word ptr devhlp_ptr+2,ax

        push    es
        push    bx




;
;       Register the TCADD's VDD services entry point with VTCA.
;       This entry point is the router for all the IDC communications.
;
        call    tcaRegister                  ; register PDD entry point  ;


        ;
        ;Do initial sign-on message
        ;Init is done at ring three,some of the API's can be safely
        ;called from here
        ;
        .386P
         push stdout
         push ds
         push offset ds:Idin
         push IdIn_len
         push ds
         push offset ds:wlen
         call DosWrite
         mov word ptr es: [bx + 3 ],0100h

        .286P
        pop     bx
        pop     es

  ; the next 2 lines set up the address of the end of the real
  ; device driver. the init cseg will be deleted by dos

        mov     word ptr rh_end_addr[bx],offset end_of_driver
        mov     word ptr rh_end_addr+2[bx],offset dsegend

        ret


EndProc initialize
cseg    ends
end     initialize
