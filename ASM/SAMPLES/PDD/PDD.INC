;       SCCSID = @(#)pdd.inc	6.1 91/12/19
;***    TCA.INC
;
;
;       MVDM Physical 3270 Device Driver Exported Definitions
; ***************************************************************************
;                                                                           *
;                                                                           *
;                  Copyright (c) IBM Corporation  1987, 1990                *
;                            All Rights Reserved                            *
;                                                                           *
; ***************************************************************************
;
;
;
;


  ?CS_16bit equ 0         ; constants for ?cstype
  ?CS_32bit equ 1
  ?cstype  = ?CS_16bit

  ;***    TCA constants
  ;


  ;***    TCA data types
  ;


  ;***    TCA function prototypes
  ;
  setDS   MACRO   segname
          push    ax
          mov     ax,segname
          mov     ds,ax
          pop     ax
          ASSUME  ds:segname
          endm

  Stack_Data      struc
          old_bp  dw      ?
          old_cs  dd      ?
          old_ip  dd      ?
          ul2     dd      ?
          ul1     dd      ?
          uFunc   dd      ?
  Stack_Data      ends

  Flat_Pointer    struc
          fp_offlo        DW      ?
          fp_offhi        DW      ?
          fp_sel          DW      ?
  Flat_Pointer    ends

  PhysAddr struc
          _lo     dw      (?)     ; low word of a 32-bit pointer
          _hi     dw      (?)     ; high word of a 32-bit pointer
  PhysAddr ends



; Procedure macro   name,distance,scope,treg,abase,blank
; ifdef ALIGNCODE
;     align 4
; endif
;     ProcError macro msg
; %       %out @FileName.asm: Error in Procedure name: msg
;     endm
; ;   if2
; ;       ifnb <treg>
; ;           ProcError <treg_arg must be _blank: treg>
; ;           .err
; ;       endif
; ;       ifnb <blank>
; ;           ProcError <Too many parameters>
; ;           .err
; ;       endif
; ;       if ?depth gt 1
; ;           ProcError <Nesting too deep>
; ;           .err
; ;       endif
; ;   endif
;     ?depth       = ?depth + 1
;     ?olddistance = ?distance    ;; save previous value
;     ?frame       = 0
;     ?aframe      = 0
;     ?initstack   = ?stackdepth  ;; beginning of procedure
;     ?local       = 0            ;; default to public
;     ?distance    = 0            ;; default is set elsewhere
;     ?argfar      = 0            ;; okay to use ArgVar
;     ?nfields     = 0            ;; used here to count ArgVars
;     ?name        equ <name>     ;; save current procedure name
;     ?wdsz        = 2            ;; default word size
;     if (?cstype eq ?CS_32bit)
;         ?wdsz = 4
;     endif
;     ifnb <scope>
;         irp x,<scope>
;             ifidni <x>,<nearlocal>              ;; near is local
;                 ?local = ?local or ?LC_NEARLOCAL
;             elseifidni <x>,<far16local>         ;; far16 is local
;                 ?local = ?local or ?LC_FAR16LOCAL
;             elseifidni <x>,<far32local>         ;; far16 is local
;                 ?local = ?local or ?LC_FAR32LOCAL
;             elseifidni <x>,<farlocal>           ;; faronly is local
;                 ?local = ?local or ?LC_FARLOCAL
;             elseifidni <x>,<local>              ;; all are local
;                 ?local = ?local or ?LC_NEARLOCAL or ?LC_FARLOCAL \
;                                 or ?LC_FAR16LOCAL or ?LC_FAR32LOCAL \
;                                 or ?LC_LOCAL
;             elseif2
;                 ProcError <Bad scope_arg: x>
;                 .err
;             endif
;         endm
;     endif
;     .lall
;     ?bm1 = ?local                               ;; only for listing files
;     .xall
;
;     ifnb <distance>
;         irp x,<distance>
;             ifidni <x>,<near>           ;; is near
;                 ?distance = ?distance or ?PD_NEAR or ?PD_DIST
;             elseifidni <x>,<far16>      ;; is 16 bit callable from 32
;                 ?distance = ?distance or ?PD_FAR16 or ?PD_DIST
;             elseifidn <x>,<far32>       ;; is 32 bit callable from 16
;                 ?distance = ?distance or ?PD_FAR32 or ?PD_DIST
;             elseifidni <x>,<far>        ;; is 16 bit far
;                 ?distance = ?distance or ?PD_FAR or ?PD_DIST
;             elseifidni <x>,<faronly>    ;; is 16 bit faronly
;                 ?distance = ?distance or ?PD_FARONLY or ?PD_DIST
;             elseifidni <x>,<hybrid>     ;; is 16-bit near/faronly hybrid
;                 ?distance = ?distance or ?PD_NEAR or ?PD_FARONLY or ?PD_DIST
;             elseifidn <x>,<cdecl>       ;; is cdecl (caller cleanup)
;                 ?distance = ?distance or ?PD_CDECL
;             elseifidn <x>,<pascal>      ;; is pascal (callee cleanup)
;                 ?distance = ?distance or ?PD_PASCAL
;             elseif2
;                 ProcError <Bad distance_arg: x>
;                 .err
;             endif
;         endm
;
;         ;; If both types of 16 bit thunks are required, add a near
;         ;; procedure body, and have both thunks call it near:
;
;         if ((?distance and ?PD_DISTMASK) eq (?PD_FAR16 or ?PD_FARONLY))
;             ?distance = ?distance or ?PD_NEAR
;         endif
;
;         if2
;             ;; Disallow 16 bit thunks in 32 bit code.
;
;             if (?cstype eq ?CS_32bit)
;                 if (?distance and (?PD_FAR16 or ?PD_FARONLY))
;                     ProcError <16-bit Procedure in 32-bit code>
;                     .err
;                 endif
;             else
;                 if (?distance and ?PD_FAR32)
;                     ProcError <32-bit Procedure in 16-bit code>
;                     .err
;                 endif
;             endif
;             if (?distance and ?PD_FAR)
;                 if ((?distance and ?PD_DISTMASK) ne ?PD_FAR)
;                     ProcError <distance_arg cannot use FAR combinations>
;                     .err
;                 endif
;             endif
;             if ((?distance and (?PD_CDECL or ?PD_PASCAL)) eq \
;                 (?PD_CDECL or ?PD_PASCAL))
;
;                 ProcError <pascal and cdecl conflict>
;                 .err
;             endif
;         endif
;     endif
;     if ((?distance and ?PD_DIST) eq 0)
;         ?distance = ?distance or ?PD_NEAR       ;; default is near
;     endif
;     ifndef STDCALL
;         if ((?distance and ?PD_PASCAL) eq 0)
;             ?distance = ?distance or ?PD_CDECL  ;; force cdecl override
;         endif
;     endif
;     .lall
;     ?bm1 = ?distance                            ;; only for listing files
;     .xall
;
;     RETP macro n                                ;; use masm's default RET type
;         ret n
;     endm
;
;     ;; if near, generate any needed thunks first
;
;     if (?distance and ?PD_NEAR)
;         if (?distance and ?PD_FAR16)            ;; if far16 thunk needed
;             if (?distance and ?PD_FARONLY)      ;; and if faronly thunk needed,
;                 if (?local and ?LC_FARLOCAL)    ;; use call for faronly thunk
;                     GenHybrid name,<local>,<usecall>
;                 else
;                     GenHybrid name,,<usecall>
;                 endif
;             endif
;             if (?local and ?LC_FAR16LOCAL)      ;; far16 thunk falls through
;                 ?Gen16 name,local
;             else
;                 ?Gen16 name
;             endif
;                                                 ;; far16 thunk not needed
;         elseif (?distance and ?PD_FARONLY)      ;; if faronly thunk needed,
;             if (?local and ?LC_FARLOCAL)        ;; faronly thunk falls through
;                 GenHybrid name,local
;             else
;                 GenHybrid name
;             endif
;         elseif (?distance and ?PD_FAR32)        ;; if far32 thunk needed
;             if (?local and ?LC_FAR32LOCAL)      ;; use call for far32 thunk
;                 GenFar32 name,local
;             else
;                 GenFar32 name
;             endif
;         endif
;         if (?local and ?LC_NEARLOCAL)           ;; generate main proc label
;             GenPublic name,<local>,code
;         else
;             GenPublic name,,code
;         endif
;         name proc near                          ;; main proc is near
;     else
;
;     ;; main proc isn't near; may need to prepend HYBPRE_, F16PRE_ or F32PRE_
;
;         if (?distance and ?PD_FARONLY)
;             if (?local and ?LC_FARLOCAL)        ;; generate proc HYBPRE_label
;                 ?PrePublic %HYBPRE_, name,<local>,code
;             else
;                 ?PrePublic %HYBPRE_, name,,code
;             endif
;             CatPrefix , %HYBPRE_, <name>, <proc far> ;; main proc is far
;         endif
;         if (?distance and ?PD_FAR16)
;             if (?local and ?LC_FAR16LOCAL)      ;; generate proc F16PRE_label
;                 ?PrePublic %F16PRE_, name,<local>,code
;             else
;                 ?PrePublic %F16PRE_, name,,code
;             endif
;             CatPrefix , %F16PRE_, <name>, <proc far> ;; main proc is far
;             RETP macro n                        ;; use RETFD
;                 RETFD n
;             endm
;         endif
;         if (?distance and ?PD_FAR32)
;             if (?local and ?LC_FAR32LOCAL)      ;; generate proc F32PRE_label
;                 ?PrePublic %F32PRE_, name,<local>,code
;             else
;                 ?PrePublic %F32PRE_, name,,code
;             endif
;             CatPrefix , %F32PRE_, <name>, <proc far> ;; main proc is far
;         endif
;         if (?distance and ?PD_FAR)
;             if (?local and ?LC_LOCAL)           ;; generate main proc label
;                 GenPublic name,<local>,code
;             else
;                 GenPublic name,,code
;             endif
;             name proc far                       ;; main proc is far
;         endif
;     endif
;
;     if (?distance and ?PD_NEAR)
;         ?abase = 4 + 4                  ;; ret address, EBP are 4 bytes each?
;         if (?cstype ne ?CS_32bit)
;             ?abase = 2 + 2              ;; ret address, BP are 2 bytes each?
;         endif
;         if (?distance and (?PD_FAR32 or ?PD_FAR16))
;             ?argfar = 8                 ;; extra 32 bit far call on stack
;         endif
;         if (?distance and ?PD_FARONLY)
;             ife ?argfar
;                 ?argfar = 4             ;; extra 16 bit far call on stack
;             else
;                 ?argfar = -1            ;; doesn't work when thunks combined
;             endif
;         endif
;     else
;         if (?distance and ?PD_FAR32)
;             ?abase = 8 + 4              ;; ret addr is 8 bytes, EBP is 4 bytes!
;         endif
;         if (?distance and ?PD_FAR16)
;             ?abase = 8 + 2              ;; ret addr is 8 bytes, BP is 2 bytes!
;         endif
;         if (?distance and ?PD_FARONLY)
;             ?abase = 4 + 2              ;; ret addr is 4 bytes, BP is 2 bytes!
;         endif
;         if (?distance and ?PD_FAR)
;             ?abase = 8 + 4              ;; ret addr is 8 bytes, EBP is 4 bytes?
;             if (?cstype ne ?CS_32bit)
;                 ?abase = 4 + 2          ;; ret addr is 4 bytes, BP is 2 bytes!
;             endif
;         endif
;     endif
;     ifnb <abase>                        ;; if abase is not blank, then use it
;         ifidni <abase>,<esp>            ;; if abase is ESP, then no [E]BP frame
;             ?abase = ?abase - 4         ;; uncompensate for EBP
;             if (?cstype ne ?CS_32bit)
;                 ?abase = ?abase + 2     ;; oops.  uncompensate only for BP
;             endif
;             ?distance = ?distance or ?PD_ESPFRAME
;         else
;             ?abase = abase
;         endif
;     endif
;     .lall
;     ?bm1 = ?abase                               ;; only for listing files
;     ?bm1 = ?argfar                              ;; only for listing files
;     .xall
; endm
;
; ;*** EndProc - End a procedure
; ;
; ;   This ends a procedure declaration by generating appropriate
; ;   endp pseudo ops. It also checks to make sure the number of
; ;   registers saved with SaveReg are the same as the number of
; ;   registers restored with RestoreReg within the procedure body.
; ;   This check is not fool-proof because it assumes all the
; ;   SaveReg and RestoreReg macros will be executed exactly once
; ;   during run time, which may not be a valid assumption.
; ;
; ;   ENTRY   name = name of procedure to end
; ;           chk  = blank - verify #registers saved by SaveReg
; ;                  and restored by RestoreReg are the same.
; ;                = "NoCheck" - don't check
; ;   (global var)
; ;           ?depth       = level of Procedure nested.  Max is 1.
; ;           ?distance    = set by Procedure macro
; ;           ?olddistance = value of ?distance when Procedure macro
; ;                          was called.
; ;
; ;   EXIT    "endp" with appropriate label generated.
; ;   (global variables)
; ;           ?depth   = decremented
; ;           ?distance = restored to previous value when
; ;                       Procedure macro was called.
; ;
; ;   SEE ALSO: Procedure, ArgVar, LocalVar, EnterProc, SaveReg,
; ;             RestoreReg, LeaveProc, EndProc.
;
; EndProc macro name, chk
; ifdef ALIGNCODE
;     align 4
; endif
;     if2
;         if (?distance and ?PD_ENTERED)
;             ifdif <chk>,<NoCheck>
;                 ProcError <EndProc invoked without LeaveProc>
;                 .err
;             endif
;         endif
;         ife ?depth
;             ProcError <EndProc without matching Procedure>
;             .err
;         endif
;         ?bm1 = 0                                ;; assume no NoCheck
;         ifnb <chk>
;             ifdif <chk>,<NoCheck>
;                 ProcError <EndProc: bad NoCheck arg: chk>
;                 .err
;             else
;                 ?bm1 = 1                        ;; saw NoCheck
;             endif
;         endif
;         if (?bm1 eq 0)
;             if (?initstack ne ?stackdepth)      ;; is it different?
;                 ProcError <SaveReg/RestoreReg mismatch>
;             endif
;         endif
;     endif
;     if (?distance and ?PD_NEAR)
;         name endp                       ;; procedure is near
;     elseif (?distance and ?PD_FAR16)
;         CatPrefix , %F16PRE_, <name>, <endp> ;; procedure is is far16
;     elseif (?distance and ?PD_FAR32)
;         CatPrefix , %F32PRE_, <name>, <endp> ;; procedure is is far32
;     elseif (?distance and ?PD_FARONLY)
;         CatPrefix , %HYBPRE_, <name>, <endp> ;; procedure is is faronly
;     else
;         name endp                       ;; procedure is far
;     endif
;     ?depth = ?depth - 1
;     ?distance = ?olddistance            ;; restore previous value
;     ifdef KILLASSUMES
;         assume ds:nothing, es:nothing, ss:nothing
;         if (?cstype eq ?CS_32bit)
;             assume fs:nothing, gs:nothing
;         endif
;     endif
; ifdef ALIGNCODE
;     align 4
; endif
; endm
