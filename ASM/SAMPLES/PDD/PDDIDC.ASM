;       SCCSID = @(#)pddidc.asm	6.3 92/03/24
;**************************************************************************
;                   IBM Sample Physical Device Driver
;
;                   Copyright  IBM Corp 1992.
;***************************************************************************
;CODING CONVENTIONS
; all psuedo-ops, equates, documentation, publics, and externs are in uppercase.
; all CSEG and DSEG names are in lowercase.
;
;  ROUTINES IN THIS MODULE:
;             tcacmd_entry               router routine for vtca calls
;             tcaRegister                registers PDD with VDMM
;
;****************************************************************************
INCL_ERRORS     equ 1
INCL_MACROS     equ 1

.MODEL  large,os_os2
.XCREF
.XLIST
        INCLUDE  pdd.inc                ; TCA MACROS AND DEFINITIONS
        INCLUDE  bseerr.inc             ; ERROR CSEGS FOR DEVICES
        INCLUDE  basemaca.inc           ; VARIOUS MACRO'S (BREAK, LJC, ETC.)
        INCLUDE  devhlp.inc             ; DEFINITION OF DEVICE HELP CALLS
.286P
        .LIST
        .CREF
;**********************************************************************
;           EXTERNALS FOR VDD
;**********************************************************************
        PUBLIC ptcaname                 ; pointer to Driver Name
        PUBLIC VTCAAddress              ; address of TCA VDD entry point
        EXTRN devhlp_ptr:DWORD          ; pointer to DEV HELP services
        EXTRN    dev_interrupt:far
        EXTRN    IRQ_level:word
;*****************************************************************************
; DSEG AREA FOR MVDM VDD-PDD IMPLEMENTATION
;*****************************************************************************
DSEG    SEGMENT  PUBLIC  'DATA'
VTCAAddress df         0               ; HOLDS ADDRESS OF TCA VDD ENTRY POINT

ptcaname    db         'PDD.SYS',0     ;DEVICE DRIVER NAME

DSEGend         label      byte
DSEG            ends

;***************************************************************
; CSEG segment
;***************************************************************

CSEG    SEGMENT  PUBLIC 'CODE'

        page


;******************* START OF SPECIFICATIONS ************************
;
; SUBROUTINE NAME:  tcacmd_entry
;
; DESCRIPTIVE NAME: TCA command processing entry point for VDD
;
; FUNCTION: This entry point is the TCA PDD's IDC router/handler.
;           IDC function requests are routed to the proper routines.
;           The address of this routine is set up during
;           initialization with the DevHlp RegisterPDD call.
;           Currently, the VDD does not call the PDD except during
;           VDD initialization.
;
; ENTRY POINT: tcacmd_entry
;       LINKAGE: CALL FAR
;
; INPUT: On entry the stack is set-up as shown:
;
;        TOS -> return address (4 words)
;               variable 2     (2 words)
;               variable 1     (2 words)
;               function code  (2 words)
;
; Where: Variable 1 and 2 are specified in the worker routine.
;        CX    -> Variable 1
;        DX:DI -> variable 2
;
; EXIT-NORMAL: EAX = 1
;
;           if Func = 0    (Register)
;              P1.offset  = 0
;              P1.segment = VDD's CS
;              P2.offset  = low 16-bits of VDD EIP for entry point
;              P2.segment = high 16-bits of VDD EIP for entry point
;
;           returns:
;              AX = 1
;
;           if Func = 1    (Enable)
;              P1.offset  = 0
;              P1.segment = 0
;              P2.offset  = 0
;              P2.segment = 0
;
;           returns:
;              AX = 1
;
;           if Func = 2    (Disable)
;              P1.offset  = 0
;              P1.segment = 0
;              P2.offset  = 0
;              P2.segment = 0
;
;           returns:
;              AX = 1
;
; EXIT-ERROR:  EAX = error return code
;              ERROR_I24_INVALID_PARAMETER    if function code from
;                                             VDD is not recognized
;
; INTERNAL REFERENCES:  NONE
;
; EXTERNAL REFERENCES:  NONE
;
;********************************************************************
tcacmd_entry PROC FAR

        ASSUME  CS:CSEG,DS:DSEG

;
;       set up stack frame pointer
;
        SaveReg   <bp>
        mov       bp,sp
        SaveReg   <ds>
        SaveReg   <bx>

        setDS   DSEG              ; get DS addressability
;
;    Select (Function type)
;
;        Case (Register - 0):
pse000:
.386P
        cmp     [bp].uFunc,0

.286P
        jne     pse010
;
;            Save 16:32 pointer of VTCA notification entry point
;            in global (fixed) DSEG (VTCAAddress)
;
        mov     ax,[bp].ul1._lo
        mov     [VTCAAddress].fp_sel,ax
        mov     ax,[bp].ul2._lo
        mov     [VTCAAddress].fp_offlo,ax
        mov     ax,[bp].ul2._hi
        mov     [VTCAAddress].fp_offhi,ax

        jmp     pse198

pse010:
;
;        Case (Enable - 1):
.386P
        cmp     [bp].uFunc,1
.286P
        jne     pse020
;
;       register interrupt entry point for IRQ (enables IRQ)
;

        mov     ax,offset CS:dev_interrupt  ; offset to interrupt routine @VDD?
        mov     bx,9                     ; get the IRQ number              @A0C
        mov     irq_level,bx              ;
        mov     dh,0                                                     ; @A1A
        mov     dl,DevHlp_SetIRQ         ; SetIRQ command code in dl       @A1A
        call    dword ptr [devhlp_ptr]   ; Call to Device Help Services

        jnc     pse198
      ; int 3

;
;        Case (Disable - 2):
pse020:
.386P
        cmp     [bp].uFunc,2
.286P
        jne     pse199
;
;       remove IRQ entry point (disables IRQ)
;

        mov     bx,9                     ; get the IRQ number              @A0C
        mov     dl,DevHlp_UnSetIRQ       ; UnSetIRQ command code in dl     @A1A
        call    dword ptr [devhlp_ptr]   ; Call to Device Help Services

        jnc     pse198
        ; int 3

pse198:
        mov     ax,1                    ; show no error
        jmp     pse200                  ; now return

pse199:
        mov     ax,ERROR_I24_INVALID_PARAMETER  ; indicate error
pse200:

        RestoreReg <bx,ds,bp>              ; restore frame pointer
;
;    RETURN (32 bit)
;
        db      66h
        ret     12

tcacmd_entry endp


;******************* START OF SPECIFICATIONS ************************
;
; SUBROUTINE NAME:  tcaRegister
;
; DESCRIPTIVE NAME: TCA PDD register entry point for initializtion
;
; FUNCTION: This entry point is the TCA PDD's Register routine.
;           This routine registers the PDD's entry point with the
;           VDD. The PDD entry point is the router for all the IDC
;           communications.
;
; ENTRY POINT: tcaRegister
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

Procedure tcaRegister,FAR

        ASSUME  CS:CSEG,DS:DSEG

;
;VDM call VDMM to register a stack-based entry point
;

;        int   3                 ;uncomment this for debug
         SaveReg <si,di,es>      ; save used registers

         lea     si,ptcaname     ; set up ds:si -> name string

         mov     dx,CSEG         ; set up es:di -> routine being registered
         and dl,0FCh             ; make sure this is ring 0 !!!!!!!!!!!!

         mov     es,dx
         lea     di,CSEG:tcacmd_entry

         mov     dl,DevHlp_RegisterPDD   ; set up function type


         call    [devhlp_ptr]            ; call DEV HELP

         RestoreReg <es,di,si>           ; restore used registers

         ret

EndProc tcaRegister

CSEG    ends
        end
