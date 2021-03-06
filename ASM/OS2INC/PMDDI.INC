DDI_INCLUDED	EQU	1

ifdef INCL_GREALL
INCL_GRE_ARCS	EQU	1

INCL_GRE_BITMAPS	EQU	1

INCL_GRE_CLIP	EQU	1

INCL_GRE_COLORTABLE	EQU	1

INCL_GRE_DCS	EQU	1

INCL_GRE_DEVICE	EQU	1

INCL_GRE_DEVMISC	EQU	1

INCL_GRE_DEVSUPPORT	EQU	1

INCL_GRE_FONTS	EQU	1

INCL_GRE_JOURNALING	EQU	1

INCL_GRE_LCID	EQU	1

INCL_GRE_LINES	EQU	1

INCL_GRE_MARKERS	EQU	1

INCL_GRE_PALETTE	EQU	1

INCL_GRE_PATHS	EQU	1

INCL_GRE_PICK	EQU	1

INCL_GRE_POLYGON	EQU	1

INCL_GRE_REGIONS	EQU	1

INCL_GRE_SCANS	EQU	1

INCL_GRE_SCREEN	EQU	1

INCL_GRE_SETID	EQU	1

INCL_GRE_STRINGS	EQU	1

INCL_GRE_XFORMS	EQU	1

endif 
ifdef INCL_GRE_DEVMISC
INCL_GRE_DEVMISC1	EQU	1

INCL_GRE_DEVMISC2	EQU	1

INCL_GRE_DEVMISC3	EQU	1

endif  
MAXTABLEENTRIES	EQU	223 
NUMBEROFMAJORFUN	EQU	MAXTABLEENTRIES
NUMBEROFMINORFUN	EQU	86 

DISPATCHER	STRUC
dr_pfnTblEntry	DD	MAXTABLEENTRIES DUP (?)
DISPATCHER	ENDS

FUNINFOTABLE	STRUC
fit_FunInfo_00	DB	NUMBEROFMAJORFUN DUP (?)
fit_FunInfo_02	DB	NUMBEROFMINORFUN DUP (?)
FUNINFOTABLE	ENDS

RECTS	STRUC
rcs_pts1	DB	SIZE POINTS DUP (?)
rcs_pts2	DB	SIZE POINTS DUP (?)
RECTS	ENDS

POINTFX	STRUC
ptfx_x	DD	?
ptfx_y	DD	?
POINTFX	ENDS

RECTFX	STRUC
rcfx_ptfx1	DB	SIZE POINTFX DUP (?)
rcfx_ptfx2	DB	SIZE POINTFX DUP (?)
RECTFX	ENDS

XFORM	STRUC
xform_fxM11	DD	?
xform_fxM12	DD	?
xform_fxM21	DD	?
xform_fxM22	DD	?
xform_lM41	DD	?
xform_lM42	DD	?
XFORM	ENDS
ifdef INCL_GRE_HFONT
endif 
ifdef INCL_DDICOMFLAGS
COM_DRAW16	EQU	00000001H 
COM_BOUND16	EQU	00000002H 
COM_CORRELATE16	EQU	00000004H 
COM_ALT_BOUND16	EQU	00000008H 
COM_AREA16	EQU	00000010H 
COM_PATH16	EQU	00000020H 
COM_TRANSFORM16	EQU	00000040H 
COM_RECORDING16	EQU	00000080H 
COM_DEVICE16	EQU	00000100H 
COM_SCR_BOUND16	EQU	00000200H 
COM_PRECLIP16	EQU	04000000H 
COM_DRAW	EQU	00010000H 
COM_BOUND	EQU	00020000H 
COM_CORRELATE	EQU	00040000H 
COM_ALT_BOUND	EQU	00080000H 
COM_AREA	EQU	00100000H 
COM_PATH	EQU	00200000H 
COM_TRANSFORM	EQU	00400000H 
COM_RECORDING	EQU	00800000H 
COM_DEVICE	EQU	01000000H 
COM_SCR_BOUND	EQU	02000000H 
COM_PRECLIP	EQU	04000000H 
endif 
ifdef INCL_GRE_ARCS

BOXPARAMS	STRUC
boxp_ptl	DB	SIZE POINTL DUP (?)
boxp_sizl	DB	SIZE SIZEL DUP (?)
BOXPARAMS	ENDS
endif 
ifdef INCL_GRE_CLIP
COPYCRGN_ALLINTERSECT	EQU	0 
COPYCRGN_VISRGN	EQU	1 
COPYCRGN_CLIPRGN	EQU	2 
SETUPDC_VISRGN	EQU	00000001H 
SETUPDC_ORIGIN	EQU	00000002H 
SETUPDC_ACCUMBOUNDSON	EQU	00000004H 
SETUPDC_ACCUMBOUNDSOFF	EQU	00000008H 
SETUPDC_RECALCCLIP	EQU	00000010H 
SETUPDC_SETOWNER	EQU	00000020H 
SETUPDC_CLEANDC	EQU	00000040H 
endif 
ifdef INCL_GRE_XFORMS

VIEWPORTSIZE	STRUC
vs_cx	DD	?
vs_cy	DD	?
VIEWPORTSIZE	ENDS
endif 
ifdef INCL_GRE_DEVSUPPORT
INAT_DEFAULTATTRIBUTES	EQU	1 
INAT_CURRENTATTRIBUTES	EQU	2 

DC_BLOCK	STRUC
ivr_hdc	DD	?
ivr_hddc	DD	?
DC_BLOCK	ENDS
endif 
ifdef INCL_DDIMISC

DISPLAYINFO	STRUC
dspinfo_cb	DW	?
dspinfo_cxIcon	DW	?
dspinfo_cyIcon	DW	?
dspinfo_cxPointer	DW	?
dspinfo_cyPointer	DW	?
dspinfo_cxBorder	DW	?
dspinfo_cyBorder	DW	?
dspinfo_cxHSlider	DW	?
dspinfo_cyVSlider	DW	?
dspinfo_cxSizeBorder	DW	?
dspinfo_cySizeBorder	DW	?
dspinfo_cxDeviceAlign	DW	?
dspinfo_cyDeviceAlign	DW	?
DISPLAYINFO	ENDS

DENPARAMS	STRUC
den_ulStateInfo	DD	?
den_ulType	DD	?
den_ulHDC	DD	?
DENPARAMS	ENDS

STYLERATIO	STRUC
sr_dx	DB	?
sr_dy	DB	?
STYLERATIO	ENDS
GATTR_DEFAULT	EQU	1 
ATYPE_COLOR	EQU	1 
ATYPE_BACK_COLOR	EQU	2 
ATYPE_MIX_MODE	EQU	3 
ATYPE_BACK_MIX_MODE	EQU	4 
CHS_START_XY	EQU	00000020H 
CHS_ATTR_INFO	EQU	00000040H 

CSP_INFO	STRUC
csp_cSize	DD	?
csp_lColor	DD	?
csp_lBackColor	DD	?
CSP_INFO	ENDS
PCTL_DRAW	EQU	00000001H 
PCTL_BOUND	EQU	00000002H 
PCTL_CORRELATE	EQU	00000004H 
PCTL_USERBOUNDS	EQU	00000008H 
PCTL_AREA	EQU	00000010H 
RB_GPI	EQU	00000001H 
RB_USER	EQU	00000002H 
GBD_GPI	EQU	0 
GBD_USER	EQU	1 
EA_DRAW	EQU	00000000H 
EA_CANCEL	EQU	00000001H 
BLTMODE_SRC_BITMAP	EQU	00010000H 
BLTMODE_ATTRS_PRES	EQU	00020000H 
BBO_TARGWORLD	EQU	00000100H 

BITBLTPARAMETERS	STRUC
bbp_rclTarg	DB	SIZE RECTL DUP (?)
bbp_rclSrc	DB	SIZE RECTL DUP (?)
BITBLTPARAMETERS	ENDS

BITBLTATTRS	STRUC
bba_cSize	DD	?
bba_lColor	DD	?
bba_lBackColor	DD	?
BITBLTATTRS	ENDS
LCID_AVIO_1	EQU	(-2 )
LCID_AVIO_2	EQU	(-3 )
LCID_AVIO_3	EQU	(-4 )
LCID_BITMAP_ID_REQUEST	EQU	(-5 )
LCID_RANGE_GPI	EQU	1 
LCID_RANGE_AVIO	EQU	2 
LCID_RANGE_BOTH	EQU	3 
LCID_GRAPHICS_MIN	EQU	1 
LCID_GRAPHICS_MAX	EQU	254 
LCIDT_NONE	EQU	0 
RDC_RGBMODE	EQU	1H 
RDC_SETOWNERTOSHELL	EQU	2H 
SX_UNITY	EQU	0 
SX_CAT_AFTER	EQU	1 
SX_CAT_BEFORE	EQU	2 
SX_OVERWRITE	EQU	3 
MATRIX_SIMPLE	EQU	0001H   
MATRIX_UNITS	EQU	0002H   
MATRIX_XY_EXCHANGE	EQU	0004H   
MATRIX_X_NEGATE	EQU	0008H   
MATRIX_Y_NEGATE	EQU	0010H   
MATRIX_TRANSLATION	EQU	0020H   
NCC_CLEANDC	EQU	0002H   

NOTIFYTRANSFORMDATA	STRUC
ntd_usType	DD	?
ntd_xform	DB	SIZE XFORM DUP (?)
NOTIFYTRANSFORMDATA	ENDS
LCOL_SYSCOLORS	EQU	0010H 

QCDARRAY	STRUC
qcd_iFormat	DD	?
qcd_iSmallest	DD	?
qcd_iLargest	DD	?
qcd_cAvailable	DD	?
qcd_cSpecifiable	DD	?
qcd_iMax	DD	?
QCDARRAY	ENDS
CAPS_MIX_OR	EQU	00000001H 
CAPS_MIX_COPY	EQU	00000002H 
CAPS_MIX_UNDERPAINT	EQU	00000004H 
CAPS_MIX_XOR	EQU	00000008H 
CAPS_MIX_INVISIBLE	EQU	00000010H 
CAPS_MIX_AND	EQU	00000020H 
CAPS_MIX_OTHER	EQU	00000040H 
CAPS_DEV_FONT_SIM_BOLD	EQU	1       
CAPS_DEV_FONT_SIM_ITALIC	EQU	2 
CAPS_DEV_FONT_SIM_UNDERSCORE	EQU	4 
CAPS_DEV_FONT_SIM_STRIKEOUT	EQU	8 
CAPS_BACKMIX_OR	EQU	00000001H 
CAPS_BACKMIX_COPY	EQU	00000002H 
CAPS_BACKMIX_UNDERPAINT	EQU	00000004H 
CAPS_BACKMIX_XOR	EQU	00000008H 
CAPS_BACKMIX_INVISIBLE	EQU	00000010H 
CAPS_FONT_OUTLINE_MANAGE	EQU	16 
CAPS_FONT_IMAGE_MANAGE	EQU	32 
SFONT_RASTER	EQU	100 
SFONT_OUTLINE	EQU	101 
FONT	EQU	1000        
DCCAPS_LINE	EQU	0100H 
DCCAPS_CURVE	EQU	0200H 
DCCAPS_AREA	EQU	0400H 
DCCAPS_MARKER	EQU	0800H 
DCCAPS_TEXT	EQU	1000H 
BITMAP_USAGE_TRANSLATE	EQU	0004H 

DELETERETURN	STRUC
dr_pInfo	DD	?
dr_pBits	DD	?
DELETERETURN	ENDS
SLH_FORMAT_IS_16_DOT_16	EQU	1 
PSL_YMAJOR	EQU	8000H     

SHORTLINEHEADER	STRUC
slh_ulStyle	DD	?
slh_ulFormat	DD	?
slh_ptlStart	DB	SIZE POINTL DUP (?)
slh_ptlStop	DB	SIZE POINTL DUP (?)
slh_lxLeft	DD	?
slh_lxRight	DD	?
slh_pslhNext	DD	?
slh_pslhPrev	DD	?
SHORTLINEHEADER	ENDS

SHORTLINE	STRUC
sl_slh	DB	SIZE SHORTLINEHEADER DUP (?)
sl_ax	DD	1 DUP (?)
SHORTLINE	ENDS

BRECTL	STRUC
brctl_ptl1	DB	SIZE POINTL DUP (?)
brctl_ptl2	DB	SIZE POINTL DUP (?)
BRECTL	ENDS

RLEHDR	STRUC
rle_lType	DD	?
rle_brectlBounds	DB	SIZE BRECTL DUP (?)
rle_pRLE	DD	?
RLEHDR	ENDS

SCANDATA	STRUC
sd_pslFirstLeft	DD	?
sd_pslLastLeft	DD	?
sd_pslFirstRight	DD	?
sd_pslLastRight	DD	?
sd_c	DD	?
sd_rclBound	DB	SIZE RECTL DUP (?)
SCANDATA	ENDS
DI_HDC	EQU	00000000H 
DI_HBITMAP	EQU	00000001H 
endif  
ifdef INCL_DDIMISC2
REALIZE_FONT	EQU	1    
REALIZE_ENGINE_FONT	EQU	2 
DELETE_FONT	EQU	3 
RF_DEVICE_FONT	EQU	1 
RF_LOAD_ENGINE_FONT	EQU	2 
RF_DELETE_FONT	EQU	3 
RF_DELETE_ENGINE_FONT	EQU	4 
endif  
ifdef INCL_DDIBUNDLES

LINEDEFS	STRUC
ldef_defType	DD	?
LINEDEFS	ENDS

DLINEBUNDLE	STRUC
dlbnd_cAttr	DD	?
dlbnd_cDefs	DD	?
dlbnd_lbnd	DB	SIZE LINEBUNDLE DUP (?)
dlbnd_ldef	DB	SIZE LINEDEFS DUP (?)
DLINEBUNDLE	ENDS

AREADEFS	STRUC
adef_defSet	DD	?
adef_fFlags	DD	?
adef_CodePage	DD	?
AREADEFS	ENDS

DAREABUNDLE	STRUC
dabnd_cAttr	DD	?
dabnd_cDefs	DD	?
dabnd_abnd	DB	SIZE AREABUNDLE DUP (?)
dabnd_adef	DB	SIZE AREADEFS DUP (?)
DAREABUNDLE	ENDS

CHARDEFS	STRUC
cdef_defSet	DD	?
cdef_fFlags	DD	?
cdef_CodePage	DD	?
cdef_charSpacing	DD	?
CHARDEFS	ENDS

DCHARBUNDLE	STRUC
dcbnd_cAttr	DD	?
dcbnd_cDefs	DD	?
dcbnd_cbnd	DB	SIZE CHARBUNDLE DUP (?)
dcbnd_cdef	DB	SIZE CHARDEFS DUP (?)
DCHARBUNDLE	ENDS
ifdef BOGUS

IMAGEDEFS	STRUC
IMAGEDEFS	ENDS
endif       

DIMAGEBUNDLE	STRUC
dibnd_cAttr	DD	?
dibnd_cDefs	DD	?
dibnd_ibnd	DB	SIZE IMAGEBUNDLE DUP (?)
DIMAGEBUNDLE	ENDS

MARKERDEFS	STRUC
mdef_defSet	DD	?
mdef_fFlags	DD	?
mdef_CodePage	DD	?
MARKERDEFS	ENDS

DMARKERBUNDLE	STRUC
dmbnd_cAttr	DD	?
dmbnd_cDefs	DD	?
dmbnd_mbnd	DB	SIZE MARKERBUNDLE DUP (?)
dmbnd_mdef	DB	SIZE MARKERDEFS DUP (?)
DMARKERBUNDLE	ENDS
endif 
ifdef INCL_DDIFONTSTRUCS
INCLUDE pmfont.INC
endif 
ifdef INCL_DDIBITMAPFILE
INCLUDE pmbitmap.INC
endif 
ifdef INCL_DDIPATHS
CURVE_IDENTIFIER	EQU	43H 
LINE_IDENTIFIER	EQU	4CH 
CURVE_DO_FIRST_PEL	EQU	0002H 

CURVE	STRUC
cv_bIdent	DB	?
cv_bType	DB	?
cv_usReserved	DW	?
cv_flStyle	DD	?
cv_fl	DD	?
cv_pcvNext	DD	?
cv_pcvPrev	DD	?
cv_pcvAttrs	DD	?
cv_ptfxA	DB	SIZE POINTFX DUP (?)
cv_ptfxC	DB	SIZE POINTFX DUP (?)
cv_Reserved2	DB	28 DUP (?)
CURVE	ENDS

LINE	STRUC
ln_bIdent	DB	?
ln_bType	DB	?
ln_usReserved	DW	?
ln_flStyle	DD	?
ln_fl	DD	?
ln_pcvNext	DD	?
ln_pcvPrev	DD	?
ln_pcvAttrs	DD	?
ln_ptfxA	DB	SIZE POINTFX DUP (?)
ln_ptfxC	DB	SIZE POINTFX DUP (?)
ln_ptlA	DB	SIZE POINTL DUP (?)
ln_ptlC	DB	SIZE POINTL DUP (?)
ln_fxRslope	DD	?
ln_Reserved1	DB	8 DUP (?)
LINE	ENDS
endif  
ifdef INCL_GRE_JOURNALING
JNL_TEMP_FILE	EQU	00000001H 
JNL_PERM_FILE	EQU	00000002H 
JNL_ENGINERAM_FILE	EQU	00000004H 
JNL_USERRAM_FILE	EQU	00000008H 
JNL_DRAW_OPTIMIZATION	EQU	00000010H 
JNL_BOUNDS_OPTIMIZATION	EQU	00000020H 
endif  
ifdef INCL_GRE_DEVICE

BITMAPFORMAT	STRUC
bmf_cPlanes	DD	?
bmf_cBitCount	DD	?
BITMAPFORMAT	ENDS
endif 
ifdef INCL_GRE_PALETTE

PALETTEINFOHEADER	STRUC
palinfohdr_flCmd	DD	?
palinfohdr_ulFormat	DD	?
palinfohdr_cclr	DD	?
PALETTEINFOHEADER	ENDS

PALETTEINFO	STRUC
palinfo_flCmd	DD	?
palinfo_ulFormat	DD	?
palinfo_cclr	DD	?
palinfo_argb	DB	SIZE RGB2 * 1 DUP (?)
PALETTEINFO	ENDS
RP_BACKGROUND	EQU	0 
RP_FOREGROUND	EQU	1 
RP_DEFAULTSCHANGED	EQU	2 
endif
ifdef INCL_GRE_BITMAPS
LR_CLIPPED	EQU	2 
LR_NOTBORDER	EQU	0 
LR_BORDER	EQU	1 
LR_LEFT	EQU	2 
LR_RIGHT	EQU	4 
endif
OPTH_NO_CLIPPING_REQD	EQU	0001H 
OPTH_QRY_PATH_POINTS	EQU	0002H 

MCDESCRIPTION	STRUC
mcdesc_pMoveCursor	DD	?
mcdesc_ulCodeLength	DD	?
mcdesc_pCursorData	DD	?
mcdesc_ulDataLength	DD	?
MCDESCRIPTION	ENDS

WINCURSORDATA	STRUC
winmc_pMoveCursor	DD	?
winmc_pMoveCursorAlias	DD	?
winmc_pCursorData	DD	?
winmc_pCursorDataAlias	DD	?
winmc_ulRoutineType	DD	?
winmc_hModDisplay	DD	?
winmc_pWCThunkCode	DD	?
winmc_ulThunkLen	DD	?
winmc_usR0CS	DW	?
winmc_usR0DS	DW	?
WINCURSORDATA	ENDS
MC_32BIT	EQU	32 
MC_16BIT	EQU	16 
ifdef INCL_GRE_SCREEN
GSB_OPT_4BPP	EQU	0000H 
GSB_OPT_8BPP	EQU	0001H 
GSB_OPT_16BPP	EQU	0002H 
GSB_OPT_LINEAR	EQU	0000H 
GSB_OPT_PLANAR	EQU	0008H 
GSB_OPT_HRGN	EQU	0010H 
endif 
INCLUDE pmddim.INC
