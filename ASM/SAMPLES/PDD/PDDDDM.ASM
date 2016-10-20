;       SCCSID = @(#)pddddm.asm	6.2 92/03/24
;**************************************************************************
;                   IBM Sample Physical Device Driver
;
;                   Copyright  IBM Corp 1992.
;***************************************************************************
.286P

        page    60,132
        title   _DD   Kriter Tca Device Driver

      .MODEL  large,os_os2
        INCLUDE  devhlp.inc             ; DEFINITION OF DEVICE HELP CALLS

        EXTRN   initialize:NEAR                                         ;@VDD
        EXTRN   VTCAAddress:FAR                                         ;@VDD
        PUBLIC  devhlp_ptr                                              ;@VDD
        page


;       Request Header

rh          segment at 0
rh_len      db  ?               ; length of request header
rh_unit     db  ?               ; unit CSEG (not used)
rh_command  db  ?               ; command CSEG
rh_status   dw  ?               ; status
rh_rsvd     dw  2 dup(?)        ; reserved for DOS
rh_q_link   dw  2 dup(?)        ; request queue linkage
rh_DSEG     equ $               ; DSEG appropriate to the operation

;       Request Header DSEG for INIT command
            org rh_DSEG-rh
rh_no_units db  ?               ; number of units (not used)
rh_end_addr dd  ?               ; ending address of device driver
rh_bpb      dd  ?               ; address of BPB array (not used)
rh_drive    db  ?

;       Request Header DSEG for IOCTL command
            org rh_DSEG-rh
rh_ioctl_categ db  ?            ; category CSEG
rh_ioctl_funct db  ?            ; function CSEG
rh_ioctl_parm  dd  ?            ; addr of parms (offset and selector)
rh_ioctl_buff  dd  ?            ; addr of buffer (offset and selector)

rh          ends

;
;*******************************************************************************
; DSEG segment
;*******************************************************************************

DSEG    SEGMENT   PUBLIC  'DATA'                                          ;@VDD

;       Device Header


        dd     -1               ; address of next device header
        dw     8880h            ; device attribute
        dw     dev_strategy     ; address of device strategy entry point
        dw     ?                ; reserved
        db     'TCA_DDM '       ; name
        dw     4 dup(?)         ; reserved




; TCA Device Driver Work Area

devhlp_ptr      dd         ?    ; device help interface pointer

public IRQ_level
IRQ_level       dw         9    ; hardware IRQ level currently in use    @A0A

DSEG            ends

;*******************************************************************************
; CSEG segment
;*******************************************************************************

CSEG    SEGMENT  PUBLIC 'CODE'                                           ;@VDD

StatusReg       equ   02d0h     ; Tca card status reg io port (adapter 0)
ControlReg      equ   02d4h     ; Tca card control reg io port (adapter 0)

ControlDisable  equ   080h      ; Output to ControlReg to disable adapter

        page
        assume  cs:CSEG,ds:DSEG,es:rh

;Device Strategy Entry Point

dev_strategy proc far

        ; INT     3

        mov     rh_status[bx],0100h      ; store successful return CSEG and
                                         ;    request complete status in
                                         ;    request header status word
        mov     al,rh_command[bx]        ; route control based on
        cmp     al,10h                   ;      command CSEG
        ja      invalid_command          ; invalid if above generic ioctl
        sal     al,1                     ; set up to
        cbw                              ;   take the
        mov     si,ax                    ;      correct jump into the table
        jmp     short route

        page

function_table label word
        dw      initialize               ; init
        dw      media_check
        dw      build_bpb
        dw      reserved_3
        dw      read
        dw      non_destruc_read
        dw      input_status
        dw      input_flush
        dw      write
        dw      write_verify
        dw      output_status
        dw      output_flush
        dw      reserved_c
        dw      dev_open                 ; open
        dw      dev_close                ; close
        dw      remov_media
        dw      ioctl                    ; generic ioctl
route:
        jmp     function_table[si]


;       Unsupported command CSEGs

invalid_command:
media_check:
build_bpb:
reserved_3:
read:
non_destruc_read:
input_status:
input_flush:
write:
write_verify:
output_status:
output_flush:
reserved_c:
remov_media:
dev_open:
dev_close:
ioctl:

        mov     rh_status[bx],8103h      ; store unknown command error and
                                         ;    request complete status in
                                         ;    request header status word

        ret

dev_strategy endp

;Device Interrupt Entry Point

 public dev_interrupt
 dev_interrupt proc far
        assume   ds:DSEG


         cli                              ; ensure interrupts are inhibited

 ;
 ;       remove IRQ entry point (disables IRQ)
 ;

         mov     bx,9                     ; get the IRQ number              @A0C
         mov     dl,DevHlp_UnSetIRQ       ; UnSetIRQ command code in dl     @A1A
         call    dword ptr [devhlp_ptr]   ; Call to Device Help Services

         jnc     int198
         ; int 3

 int198:
 ;                                                                         @VDD
 ;    Let VTCA know the interrupt occurred                                 @VDD
 ;                                                                         @VDD

 .386P
         mov    eax,0                                                     ;@VDD

         push   eax                       ;Function                        @VDD
         push   eax                                                       ;@VDD
         push   eax                                                       ;@VDD

         call    FWORD PTR [VTCAAddress]                                  ;@VDD
 .286P

         mov     ax,IRQ_level             ; hardware EOI level in use      @A2C
         mov     dl,31h
         call    [devhlp_ptr]    ; issue EOI for level 9 interrupt

         sti                                                              ;@VDD

         clc
                                                                          ;@VDD
         ret                              ; return                         @VDD

 dev_interrupt endp

CSEG    ends
        end
