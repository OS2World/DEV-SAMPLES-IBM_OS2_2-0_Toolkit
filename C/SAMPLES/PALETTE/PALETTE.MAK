#旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커
#�                                                                          �
#� PROGRAM NAME: PALETTE                                                    �
#�  A PM program demonstrating vector fonts, palette manager APIs, and IPF  �
#�  help.                                                                   �
#�                                                                          �
#� COPYRIGHT:                                                               �
#� ----------                                                               �
#�  Copyright (C) International Business Machines Corp., 1992               �
#�                                                                          �
#� DISCLAIMER OF WARRANTIES:                                                �
#� -------------------------                                                �
#�  The following [enclosed] code is sample code created by IBM Corporation.�
#�  This sample code is not part of any standard IBM product and is provided�
#�  to you solely for the purpose of assisting you in the development of    �
#�  your applications.  The code is provided "AS IS", without warranty of   �
#�  any kind.  IBM shall not be liable for any damages arising out of your  �
#�  use of the sample code, even if they have been advised of the           �
#�  possibility of such damages.                                            �
#�                                                                          �
#� For details on what this program does etc., please see the PALETTE.C     �
#� file.                                                                    �
#�                                                                          �
#읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸

.SUFFIXES:

.SUFFIXES: .c .rc .ipf

ALL: PALETTE.EXE \
     PALETTE.HLP \
     PALETTE.RES

PALETTE.EXE:  \
  PALETTE.OBJ \
  PALETTE.RES \
  PALETTE.DEF \
  PALETTE.MAK
   @REM @<<PALETTE.@0
     /CO /M /PM:PM +
     PALETTE.OBJ
     PALETTE.EXE
     PALETTE.MAP

     PALETTE.DEF;
<<
   LINK386.EXE @PALETTE.@0
   RC -p -x PALETTE.RES PALETTE.EXE

palette.res:  palette.rc palette.ico palette.h
    copy ..\prodinfo.bmp
    $(RC) -r palette.rc palette.res
    del prodinfo.bmp

{.}.ipf.hlp:
   IPFC .\$*.IPF

{.}.c.obj:
  ICC.EXE /Ss /Ti /W2 /Gm /Gs- /C .\$*.c

!include PALETTE.INC
