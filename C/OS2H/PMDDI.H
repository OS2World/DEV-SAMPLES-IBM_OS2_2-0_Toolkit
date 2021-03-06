/****************************** Module Header ******************************\
*
* Module Name: PMDDI.H
*
* OS/2 Presentation Manager entry points, macros, and types for the
* Graphics Engine.
*
* Copyright (c) International Business Machines Corporation 1981, 1988-1992
*
* ===========================================================================
*
* The following symbols are used in this file for conditional sections.
*
*   #define:                To include:
*
*   INCL_DDIGRE             don't want OS2DEF, PMGPI, and PMDEV included
*   INCL_DDIDEFS            don't want the above, but do want GRE structs
*
* It is expected that callers of the Engine will want to define INCL_DDIGRE
* and possibly INCL_DDIDEFS.  The Engine itself and device drivers define
* neither of these.
*
* Further defines must be made to specify which of the GRE function macros
* should be defined.
*
*   #define:                To include:
*
*   INCL_GREALL           All of the following
*   INCL_GRE_ARCS         Arcs functions
*   INCL_GRE_BITMAPS      Bitmap functions
*   INCL_GRE_CLIP            etc...
*   INCL_GRE_COLORTABLE
*   INCL_GRE_DCS
*   INCL_GRE_DEVICE
*   INCL_GRE_DEVMISC
*   INCL_GRE_DEVSUPPORT
*   INCL_GRE_FONTS
*   INCL_GRE_JOURNALING
*   INCL_GRE_LCID
*   INCL_GRE_LINES
*   INCL_GRE_MARKERS
*   INCL_GRE_PALETTE
*   INCL_GRE_PATHS
*   INCL_GRE_PICK
*   INCL_GRE_POLYGON
*   INCL_GRE_REGIONS
*   INCL_GRE_SCANS
*   INCL_GRE_SETID
*   INCL_GRE_STRINGS
*   INCL_GRE_XFORMS
*
* ===========================================================================
*
* Comments at the end of each typedef line give the name tags used in
* the assembler include version of this file.
*
* The assembler include version of this file excludes lines between NOINC
* and INC comments.
*
\***************************************************************************/
/* NOINC */
#ifdef __IBMC__
   #pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( suspend )
   #endif
   #pragma checkout( resume )
#endif
/* INC */

#define DDI_INCLUDED


#ifdef INCL_GREALL
   #define INCL_GRE_ARCS
   #define INCL_GRE_BITMAPS
   #define INCL_GRE_CLIP
   #define INCL_GRE_COLORTABLE
   #define INCL_GRE_DCS
   #define INCL_GRE_DEVICE
   #define INCL_GRE_DEVMISC
   #define INCL_GRE_DEVSUPPORT
   #define INCL_GRE_FONTS
   #define INCL_GRE_JOURNALING
   #define INCL_GRE_LCID
   #define INCL_GRE_LINES
   #define INCL_GRE_MARKERS
   #define INCL_GRE_PALETTE
   #define INCL_GRE_PATHS
   #define INCL_GRE_PICK
   #define INCL_GRE_POLYGON
   #define INCL_GRE_REGIONS
   #define INCL_GRE_SCANS
   #define INCL_GRE_SCREEN
   #define INCL_GRE_SETID
   #define INCL_GRE_STRINGS
   #define INCL_GRE_XFORMS
#endif /* INCL_GREALL */

#ifdef INCL_GRE_DEVMISC
   #define INCL_GRE_DEVMISC1
   #define INCL_GRE_DEVMISC2
   #define INCL_GRE_DEVMISC3
#endif  /* INCL_GRE_DEVMISC */


/*** Engine dispatch tables ************************************************/

#define MAXTABLEENTRIES        223
#define NUMBEROFMAJORFUN       MAXTABLEENTRIES
#define NUMBEROFMINORFUN       86

typedef struct _DISPATCHER    /* dr */
{
   PFN    pfnTblEntry[MAXTABLEENTRIES];
} DISPATCHER;
typedef DISPATCHER *PDISPATCHER;

typedef struct _FUNINFOTABLE    /* fit */
{
   BYTE   FunInfo_00[NUMBEROFMAJORFUN];
   BYTE   FunInfo_02[NUMBEROFMINORFUN];
} FUNINFOTABLE;
typedef FUNINFOTABLE *PFUNINFOTABLE;

/*** exported Engine DDI functions *****************************************/

LONG  APIENTRY SetDriverInfo(ULONG hDrv,
                             LHANDLE hEng,
                             ULONG ulIndex,
                             HDC hdc);

LONG  APIENTRY GetDriverInfo(LHANDLE hEng,
                             ULONG ulIndex,
                             HDC hdc);

LONG  APIENTRY PostDeviceModes(PDRIVDATA pDrvData,
                               PSZ pszDrvName,
                               PSZ pszDevName,
                               PSZ pszPrtName,
                               ULONG ulOptions);

BOOL  APIENTRY GreInitialize(VOID);

ULONG APIENTRY SSAllocMem(PVOID ppAddr,
                          ULONG ulSize,
                          ULONG ulReserved);

ULONG APIENTRY SSFreeMem(PVOID pAddr);

/*** define common types in the Engine and DDI *****************************/

typedef struct _RECTS   /* rcs */
{
   POINTS pts1;
   POINTS pts2;
} RECTS;
typedef RECTS *PRECTS;

/* NOINC */
#ifndef POINTFX_DEFINED
   #define POINTFX_DEFINED
   /* INC */
   typedef struct _POINTFX   /* ptfx */
   {
      FIXED x;
      FIXED y;
   } POINTFX;
   typedef POINTFX *PPOINTFX;
   /* NOINC */
#endif
/* INC */

typedef struct _RECTFX   /* rcfx */
{
   POINTFX ptfx1;
   POINTFX ptfx2;
} RECTFX;
typedef RECTFX *PRECTFX;

typedef struct _XFORM   /* xform */
{
   FIXED fxM11;
   FIXED fxM12;
   FIXED fxM21;
   FIXED fxM22;
   LONG  lM41;
   LONG  lM42;
} XFORM;
typedef XFORM *PXFORM;

typedef LONG LCID;      /* locally-coded id */
typedef LCID *PLCID;
typedef LONG PHID;      /* path id */
typedef ULONG HDEVPAL;

#ifdef INCL_GRE_HFONT
   typedef LHANDLE HFONT;       /* font handle */
#endif /* INCL_GRE_HFONT */

#ifdef INCL_DDICOMFLAGS
   #define COM_DRAW16                      0x00000001L
   #define COM_BOUND16                     0x00000002L
   #define COM_CORRELATE16                 0x00000004L
   #define COM_ALT_BOUND16                 0x00000008L
   #define COM_AREA16                      0x00000010L
   #define COM_PATH16                      0x00000020L
   #define COM_TRANSFORM16                 0x00000040L
   #define COM_RECORDING16                 0x00000080L
   #define COM_DEVICE16                    0x00000100L
   #define COM_SCR_BOUND16                 0x00000200L
   #define COM_PRECLIP16                   0x04000000L
   
   #define COM_DRAW                        0x00010000L
   #define COM_BOUND                       0x00020000L
   #define COM_CORRELATE                   0x00040000L
   #define COM_ALT_BOUND                   0x00080000L
   #define COM_AREA                        0x00100000L
   #define COM_PATH                        0x00200000L
   #define COM_TRANSFORM                   0x00400000L
   #define COM_RECORDING                   0x00800000L
   #define COM_DEVICE                      0x01000000L
   #define COM_SCR_BOUND                   0x02000000L
   #define COM_PRECLIP                     0x04000000L
#endif /* INCL_DDICOMFLAGS */

#ifdef INCL_GRE_ARCS
   
   /* BoxBoundary */
   /* BoxInterior */
   /* BoxBoth */
   
   typedef struct _BOXPARAMS      /* boxp */
   {
      POINTL ptl;
      SIZEL  sizl;
   } BOXPARAMS;
   typedef BOXPARAMS *PBOXPARAMS;
#endif /* INCL_GRE_ARCS */

#ifdef INCL_GRE_CLIP
   
   /* CopyClipRegion */
   
   #define COPYCRGN_ALLINTERSECT        0L
   #define COPYCRGN_VISRGN              1L
   #define COPYCRGN_CLIPRGN             2L
   
   /* SetupDC */
   
   #define SETUPDC_VISRGN               0x00000001L
   #define SETUPDC_ORIGIN               0x00000002L
   #define SETUPDC_ACCUMBOUNDSON        0x00000004L
   #define SETUPDC_ACCUMBOUNDSOFF       0x00000008L
   #define SETUPDC_RECALCCLIP           0x00000010L
   #define SETUPDC_SETOWNER             0x00000020L
   #define SETUPDC_CLEANDC              0x00000040L
   
#endif /* INCL_GRE_CLIP */

#ifdef INCL_GRE_XFORMS
   
   /* QueryViewportSize */
   typedef struct _VIEWPORTSIZE   /* vs */
   {
      ULONG cx;
      ULONG cy;
   } VIEWPORTSIZE;
   typedef VIEWPORTSIZE *PVIEWPORTSIZE;
   
#endif /* INCL_GRE_XFORMS */

#ifdef INCL_GRE_DEVSUPPORT
   
   /* Constants for GreInitializeAttributes */
   
   #define INAT_DEFAULTATTRIBUTES       1L
   #define INAT_CURRENTATTRIBUTES       2L
   
   /* InvalidateVisRegion */
   
   typedef struct _DC_BLOCK   /* ivr */
   {
      ULONG hdc;
      ULONG hddc;
   } DC_BLOCK;
   typedef DC_BLOCK *PDC_BLOCK;
   
#endif /* INCL_GRE_DEVSUPPORT */

#ifdef INCL_DDIMISC
   
   /* Display information resource structure (RT_DISPLAYINFO) */
   typedef struct _DISPLAYINFO           /* dspinfo */
   {
      USHORT cb;
      SHORT cxIcon;
      SHORT cyIcon;
      SHORT cxPointer;
      SHORT cyPointer;
      SHORT cxBorder;
      SHORT cyBorder;
      SHORT cxHSlider;
      SHORT cyVSlider;
      SHORT cxSizeBorder;
      SHORT cySizeBorder;
      SHORT cxDeviceAlign;
      SHORT cyDeviceAlign;
   } DISPLAYINFO;
   typedef DISPLAYINFO *PDISPLAYINFO;
   
   /* Parameters for the DC Enable function */
   
   typedef struct _DENPARAMS   /* den */
   {
      ULONG ulStateInfo;
      ULONG ulType;
      ULONG ulHDC;
   } DENPARAMS;
   typedef DENPARAMS *PDENPARAMS;
   
   
   typedef struct _STYLERATIO   /* sr */
   {
      BYTE dx;
      BYTE dy;
   } STYLERATIO;
   typedef STYLERATIO *PSTYLERATIO;
   
   /* Options flags for SetGlobalAttribute */
   
   #define GATTR_DEFAULT                   1L
   
   /* Attribute Types for SetGlobalAttribute */
   
   #define ATYPE_COLOR                     1L
   #define ATYPE_BACK_COLOR                2L
   #define ATYPE_MIX_MODE                  3L
   #define ATYPE_BACK_MIX_MODE             4L
   
   /* Options for CharStringPos */
   
   #define CHS_START_XY                    0x00000020L
   #define CHS_ATTR_INFO                   0x00000040L
   
   typedef struct _CSP_INFO   /* csp */
   {
      LONG  cSize;
      LONG  lColor;
      LONG  lBackColor;
   } CSP_INFO;
   typedef CSP_INFO *PCSP_INFO;
   
   /* Set/GetProcessControl */
   
   #define PCTL_DRAW                       0x00000001L
   #define PCTL_BOUND                      0x00000002L
   #define PCTL_CORRELATE                  0x00000004L
   #define PCTL_USERBOUNDS                 0x00000008L
   #define PCTL_AREA                       0x00000010L
   
   /* ResetBounds */
   
   #define RB_GPI                          0x00000001L
   #define RB_USER                         0x00000002L
   
   /* GetBoundsData */
   
   #define GBD_GPI                         0L
   #define GBD_USER                        1L
   
   /* EndArea Cancel Option */
   
   #define EA_DRAW                         0x00000000L
   #define EA_CANCEL                       0x00000001L
   
   /* Bitblt Style */
   
   #define BLTMODE_SRC_BITMAP              0x00010000L
   #define BLTMODE_ATTRS_PRES              0x00020000L
   #define BBO_TARGWORLD                   0x00000100L
   
   typedef struct _BITBLTPARAMETERS   /* bbp */
   {
      RECTL rclTarg;
      RECTL rclSrc;
   } BITBLTPARAMETERS;
   typedef BITBLTPARAMETERS *PBITBLTPARAMETERS;
   
   typedef struct _BITBLTATTRS   /* bba */
   {
      LONG cSize;
      LONG lColor;
      LONG lBackColor;
   } BITBLTATTRS;
   typedef BITBLTATTRS *PBITBLTATTRS;
   
   /* LCIDs */
   
   #define LCID_AVIO_1                     (-2L)
   #define LCID_AVIO_2                     (-3L)
   #define LCID_AVIO_3                     (-4L)
   #define LCID_BITMAP_ID_REQUEST          (-5L)
   
   #define LCID_RANGE_GPI                  1L
   #define LCID_RANGE_AVIO                 2L
   #define LCID_RANGE_BOTH                 3L
   #define LCID_GRAPHICS_MIN               1
   #define LCID_GRAPHICS_MAX               254
   
   #define LCIDT_NONE                      0L
   
   /* ResetDC */
   
   #define RDC_RGBMODE                     0x1L
   #define RDC_SETOWNERTOSHELL             0x2L
   
   /* SetRandomXform */
   
   #define SX_UNITY                        0L
   #define SX_CAT_AFTER                    1L
   #define SX_CAT_BEFORE                   2L
   #define SX_OVERWRITE                    3L
   
   /* transform accelerators                    */
   /*  These bits are only valid if the MATRIX_SIMPLE bit is set.           */
   /*  The X and Y negate flags are only meaningful if MATRIX_UNITS is set.*/
   
   #define MATRIX_SIMPLE            0x0001L  /* two entries are zero */
   #define MATRIX_UNITS             0x0002L  /* all entries are +1 or -1 */
   #define MATRIX_XY_EXCHANGE       0x0004L  /* zeros are on the diagonal*/
   #define MATRIX_X_NEGATE          0x0008L  /* X is hit by negative */
   #define MATRIX_Y_NEGATE          0x0010L  /* Y is hit by negative */
   #define MATRIX_TRANSLATION       0x0020L  /* non-zero translation */
   
   /* NotifyClipChange */
   
   #define NCC_CLEANDC              0x0002L  /* clear DC dirty bit */
   
   /* NotifyTransformChange */
   
   typedef struct _NOTIFYTRANSFORMDATA   /* ntd */
   {
      ULONG  usType;
      XFORM  xform;
   } NOTIFYTRANSFORMDATA;
   typedef NOTIFYTRANSFORMDATA *PNOTIFYTRANSFORMDATA;
   
   /* ColorTable */
   
   #define LCOL_SYSCOLORS           0x0010L
   
   
   /* query device caps */
   
   typedef struct _QCDARRAY   /* qcd */
   {
      LONG    iFormat;
      LONG    iSmallest;
      LONG    iLargest;
      LONG    cAvailable;
      LONG    cSpecifiable;
      LONG    iMax;
   } QCDARRAY;
   typedef QCDARRAY *PQCDARRAY;
   
   #define CAPS_MIX_OR                  0x00000001L
   #define CAPS_MIX_COPY                0x00000002L
   #define CAPS_MIX_UNDERPAINT          0x00000004L
   #define CAPS_MIX_XOR                 0x00000008L
   #define CAPS_MIX_INVISIBLE           0x00000010L
   #define CAPS_MIX_AND                 0x00000020L
   #define CAPS_MIX_OTHER               0x00000040L
   
   #define CAPS_DEV_FONT_SIM_BOLD       1L      /* for CAPS_DEVICE_FONT_SIM */
   #define CAPS_DEV_FONT_SIM_ITALIC     2L
   #define CAPS_DEV_FONT_SIM_UNDERSCORE 4L
   #define CAPS_DEV_FONT_SIM_STRIKEOUT  8L
   
   #define CAPS_BACKMIX_OR              0x00000001L
   #define CAPS_BACKMIX_COPY            0x00000002L
   #define CAPS_BACKMIX_UNDERPAINT      0x00000004L
   #define CAPS_BACKMIX_XOR             0x00000008L
   #define CAPS_BACKMIX_INVISIBLE       0x00000010L
   
   
   /*#define CAPS_RASTER_BITBLT         0x00000001L defined in pmdev.h */
   /*#define CAPS_RASTER_BANDING        0x00000002L */
   /*#define CAPS_RASTER_STRETCHBLT     0x00000004L */
   /*#define CAPS_RASTER_SETPEL         0x00000010L */
   #define CAPS_FONT_OUTLINE_MANAGE     16L
   #define CAPS_FONT_IMAGE_MANAGE       32L
   #define SFONT_RASTER                 100
   #define SFONT_OUTLINE                101
   #define FONT              1000       /* must not conflict with RT_XXX */
   /* constants in BSEDOS.H */
   
   /* DCCaps */
   
   #define DCCAPS_LINE                  0x0100
   #define DCCAPS_CURVE                 0x0200
   #define DCCAPS_AREA                  0x0400
   #define DCCAPS_MARKER                0x0800
   #define DCCAPS_TEXT                  0x1000
   
   /* DeviceDeleteBitmap */
   #define BITMAP_USAGE_TRANSLATE       0x0004
   
   /* DeleteBitmap return structure */
   typedef struct _DELETERETURN   /* dr */
   {
      ULONG      pInfo;
      ULONG      pBits;
   } DELETERETURN;
   typedef DELETERETURN *PDELETERETURN;
   
   /* Short Line Header */
   
   #define SLH_FORMAT_IS_16_DOT_16 1
   #define PSL_YMAJOR 0x8000    /* bit mask for usStyle */
   
   typedef struct _SHORTLINEHEADER   /* slh */
   {
      ULONG  ulStyle;
      ULONG  ulFormat;
      POINTL ptlStart;
      POINTL ptlStop;
      LONG   lxLeft;
      LONG   lxRight;
      struct _SHORTLINEHEADER *pslhNext;
      struct _SHORTLINEHEADER *pslhPrev;
   } SHORTLINEHEADER;
   typedef SHORTLINEHEADER *PSHORTLINEHEADER;
   /* Short Line */
   
   typedef struct _SHORTLINE   /* sl */
   {
      SHORTLINEHEADER slh;
      LONG      ax[1];
   } SHORTLINE;
   typedef SHORTLINE *PSHORTLINE;
   
   /* Bounding rectangle for subpaths. */
   
   typedef struct _BRECTL          /* brctl */
   {
      POINTL ptl1;
      POINTL ptl2;
   } BRECTL;
   typedef BRECTL *PBRECTL;
   
   typedef struct _RLEHDR   /* rle */
   {
      LONG     lType;
      BRECTL   brectlBounds;
      PVOID    pRLE;
   } RLEHDR;
   typedef RLEHDR *PRLEHDR;
   
   
   typedef struct _SCANDATA   /* sd */
   {
      PSHORTLINE pslFirstLeft;
      PSHORTLINE pslLastLeft;
      PSHORTLINE pslFirstRight;
      PSHORTLINE pslLastRight;
      ULONG      c;
      RECTL      rclBound;
   } SCANDATA;
   typedef SCANDATA *PSCANDATA;
   
   /* Index for Set/GetDriverInfo */
   
   #define DI_HDC                      0x00000000L
   #define DI_HBITMAP                  0x00000001L
   
#endif  /* INCL_DDIMISC */

#ifdef INCL_DDIMISC2
   
   /* RealizeFont */
   
   #define REALIZE_FONT                 1   /* To be removed */
   #define REALIZE_ENGINE_FONT          2
   #define DELETE_FONT                  3
   
   #define RF_DEVICE_FONT               1
   #define RF_LOAD_ENGINE_FONT          2
   #define RF_DELETE_FONT               3
   #define RF_DELETE_ENGINE_FONT        4
   
#endif  /* INCL_DDIMISC2 */

#ifdef INCL_DDIBUNDLES
   
   /* Device Line Bundle */
   
   typedef struct _LINEDEFS   /* ldef */
   {
      ULONG      defType;
   } LINEDEFS;
   typedef LINEDEFS *PLINDEFS;
   
   typedef struct _DLINEBUNDLE   /* dlbnd */
   {
      LONG       cAttr;
      LONG       cDefs;
      LINEBUNDLE lbnd;
      LINEDEFS   ldef;
   } DLINEBUNDLE;
   typedef DLINEBUNDLE *PDLINEBUNDLE;
   
   /* Device Area Bundle */
   
   typedef struct _AREADEFS   /* adef */
   {
      ULONG      defSet;
      ULONG      fFlags;
      ULONG      CodePage;
   } AREADEFS;
   typedef AREADEFS *PAREADEFS;
   
   typedef struct _DAREABUNDLE   /* dabnd */
   {
      LONG       cAttr;
      LONG       cDefs;
      AREABUNDLE abnd;
      AREADEFS   adef;
   } DAREABUNDLE;
   typedef DAREABUNDLE *PDAREABUNDLE;
   
   /* Device Character Bundle */
   
   typedef struct _CHARDEFS   /* cdef */
   {
      ULONG      defSet;
      ULONG      fFlags;
      ULONG      CodePage;
      ULONG      charSpacing;
   } CHARDEFS;
   typedef CHARDEFS *PCHARDEFS;
   
   typedef struct _DCHARBUNDLE   /* dcbnd */
   {
      LONG       cAttr;
      LONG       cDefs;
      CHARBUNDLE cbnd;
      CHARDEFS   cdef;
   } DCHARBUNDLE;
   typedef DCHARBUNDLE *PDCHARBUNDLE;
   
   /* Device Image Bundle */
   
   #ifdef BOGUS
      typedef struct _IMAGEDEFS   /* idef */
      {
      } IMAGEDEFS;
   #endif       /* BOGUS */
   
   typedef struct _DIMAGEBUNDLE   /* dibnd */
   {
      LONG       cAttr;
      LONG       cDefs;
      IMAGEBUNDLE ibnd;
      /* IMAGEDEFS     idef; */
   } DIMAGEBUNDLE;
   typedef DIMAGEBUNDLE *PDIMAGEBUNDLE;
   
   /* Device Marker Bundle */
   
   typedef struct _MARKERDEFS   /* mdef */
   {
      ULONG      defSet;
      ULONG      fFlags;
      ULONG      CodePage;
   } MARKERDEFS;
   typedef MARKERDEFS *PMARKERDEFS;
   
   typedef struct _DMARKERBUNDLE   /* dmbnd */
   {
      LONG       cAttr;
      LONG       cDefs;
      MARKERBUNDLE mbnd;
      MARKERDEFS   mdef;
   } DMARKERBUNDLE;
   typedef DMARKERBUNDLE *PDMARKERBUNDLE;
   
   
#endif /* INCL_DDIBUNDLES */

#ifdef INCL_DDIFONTSTRUCS
   #include <pmfont.h>
#endif /* INCL_DDIFONTSTRUCS */

#ifdef INCL_DDIBITMAPFILE
   #include <pmbitmap.h>
#endif /* INCL_DDIBITMAPFILE */

#ifdef INCL_DDIPATHS
   /* Curve types */
   
   #define CURVE_IDENTIFIER             0x43
   #define LINE_IDENTIFIER              0x4C
   #define CURVE_DO_FIRST_PEL           0x0002
   
   typedef struct _CURVE   /* cv */
   {
      BYTE        bIdent;             /*  1    1  */
      BYTE        bType;              /*  1    2  */
      USHORT      usReserved;         /*  2    4  */
      ULONG       flStyle;            /*  4    8  */
      ULONG       fl;                 /*  4   12  */
      struct      _CURVE *pcvNext;    /*  4   16  */
      struct      _CURVE *pcvPrev;    /*  4   20  */
      struct      _CURVE *pcvAttrs;   /*  4   24  */
      POINTFX     ptfxA;              /*  8   32  */
      POINTFX     ptfxC;              /*  8   40  */
      BYTE        Reserved2[28];      /* 28   68  */
   } CURVE;
   typedef CURVE *PCURVE;
   
   typedef struct _LINE   /* ln */
   {
      BYTE        bIdent;             /*  1    1  */
      BYTE        bType;              /*  1    2  */
      USHORT      usReserved;         /*  2    4  */
      ULONG       flStyle;            /*  4    8  */
      ULONG       fl;                 /*  4   12  */
      PCURVE      pcvNext;            /*  4   16  */
      PCURVE      pcvPrev;            /*  4   20  */
      PCURVE      pcvAttrs;           /*  4   24  */
      POINTFX     ptfxA;              /*  8   32  */
      POINTFX     ptfxC;              /*  8   40  */
      POINTL      ptlA;               /*  8   48  */
      POINTL      ptlC;               /*  8   56  */
      FIXED       fxRslope;           /*  4   60  */
      BYTE        Reserved1[8];       /*  8   68  */
   } LINE;
   typedef LINE *PLINE;
   
#endif  /* INCL_DDIPATHS */

#ifdef INCL_GRE_JOURNALING
   #define JNL_TEMP_FILE            0x00000001L
   #define JNL_PERM_FILE            0x00000002L
   #define JNL_ENGINERAM_FILE       0x00000004L
   #define JNL_USERRAM_FILE         0x00000008L
   #define JNL_DRAW_OPTIMIZATION    0x00000010L
   #define JNL_BOUNDS_OPTIMIZATION  0x00000020L
#endif  /* INCL_GRE_JOURNALING */


#ifdef INCL_GRE_DEVICE
   
   /* QueryDeviceBitmaps */
   
   typedef struct _BITMAPFORMAT   /* bmf */
   {
      ULONG cPlanes;
      ULONG cBitCount;
   } BITMAPFORMAT;
   typedef BITMAPFORMAT *PBITMAPFORMAT;
   
#endif /* INCL_GRE_DEVICE */

#ifdef INCL_GRE_PALETTE
   
   typedef struct _PALETTEINFOHEADER   /* palinfohdr */
   {
      ULONG  flCmd;         /* options from creation                   */
      ULONG  ulFormat;      /* specifies format of entries at creation */
      ULONG  cclr;          /* number of elements supplied at creation */
   } PALETTEINFOHEADER;
   typedef PALETTEINFOHEADER *NPPALETTEINFOHEADER;
   typedef PALETTEINFOHEADER *PPALETTEINFOHEADER;
   
   typedef struct _PALETTEINFO   /* palinfo */
   {
      ULONG  flCmd;         /* options from creation                   */
      ULONG  ulFormat;      /* specifies format of entries at creation */
      ULONG  cclr;          /* number of elements supplied at creation */
      RGB2   argb[1];       /* the palette entries                     */
   } PALETTEINFO;
   typedef PALETTEINFO *NPPALETTEINFO;
   typedef PALETTEINFO *PPALETTEINFO;
   
   /* flType values for RealizePalette */
   #define RP_BACKGROUND                0
   #define RP_FOREGROUND                1
   #define RP_DEFAULTSCHANGED           2
   
#endif

#ifdef INCL_GRE_BITMAPS
   #define LR_CLIPPED   2
   #define LR_NOTBORDER 0
   #define LR_BORDER    1
   #define LR_LEFT      2
   #define LR_RIGHT     4
#endif

/* Flags  for GreOutlinePath */
#define OPTH_NO_CLIPPING_REQD         0x0001L
#define OPTH_QRY_PATH_POINTS          0x0002L

/*** 32-bit cursor/pointer stuff ******************************/
typedef struct _MCDESCRIPTION   /* mcdesc */
{
   PVOID    pMoveCursor;
   ULONG    ulCodeLength;
   PVOID    pCursorData;
   ULONG    ulDataLength;
}  MCDESCRIPTION;
typedef MCDESCRIPTION *PMCDESCRIPTION;

typedef struct _WINCURSORDATA   /* winmc */
{
   ULONG      pMoveCursor;
   ULONG      pMoveCursorAlias;
   ULONG      pCursorData;
   ULONG      pCursorDataAlias;
   ULONG      ulRoutineType;
   HMODULE    hModDisplay;
   PVOID      pWCThunkCode;
   ULONG      ulThunkLen;
   USHORT     usR0CS;
   USHORT     usR0DS;
}  WINCURSORDATA;
typedef WINCURSORDATA *PWINCURSORDATA;

#define MC_32BIT   32
#define MC_16BIT   16

#ifdef INCL_GRE_SCREEN
   
   /* GetScreenBits */
   
   typedef LHANDLE   HSCA;     /* hsca */
   typedef HSCA *PHSCA;
   
   #define GSB_OPT_4BPP    0x0000L
   #define GSB_OPT_8BPP    0x0001L
   #define GSB_OPT_16BPP   0x0002L
   #define GSB_OPT_LINEAR  0x0000L
   #define GSB_OPT_PLANAR  0x0008L
   #define GSB_OPT_HRGN    0x0010L
   
#endif /* INCL_GRE_SCREEN */

#include <pmddim.h>

/* NOINC */
#ifdef __IBMC__
   #pragma checkout( suspend )
   #ifndef __CHKHDR__
      #pragma checkout( resume )
   #endif
   #pragma checkout( resume )
#endif
/* INC */

/**************************** end of file **********************************/
