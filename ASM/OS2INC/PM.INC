PM_INCLUDED	EQU	1

ifdef INCL_PM
INCL_AVIO	EQU	1

INCL_BITMAPFILEFORMAT	EQU	1

INCL_DEV	EQU	1

INCL_ERRORS	EQU	1

INCL_FONTFILEFORMAT	EQU	1

INCL_GPI	EQU	1

INCL_ORDERS	EQU	1

INCL_PIC	EQU	1

INCL_SPL	EQU	1

INCL_WIN	EQU	1

INCL_WINSTDDLGS	EQU	1

INCL_WINWORKPLACE	EQU	1

endif 
INCLUDE pmwin.INC
INCLUDE pmgpi.INC
INCLUDE pmdev.INC
INCLUDE pmwp.INC
ifdef INCL_AVIO
INCLUDE pmavio.INC
endif
ifdef INCL_SPL
INCLUDE pmspl.INC
endif
ifdef INCL_PIC
INCLUDE pmpic.INC
endif
ifdef INCL_ORDERS
INCLUDE pmord.INC
endif
ifdef INCL_FONTFILEFORMAT
INCLUDE pmfont.INC
endif
INCLUDE pmstddlg.INC
