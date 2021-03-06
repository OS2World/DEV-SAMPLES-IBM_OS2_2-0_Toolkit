ifndef MLE_INCLUDED
MLE_INCLUDED	EQU	1

MLS_WORDWRAP	EQU	00000001H 
MLS_BORDER	EQU	00000002H 
MLS_VSCROLL	EQU	00000004H 
MLS_HSCROLL	EQU	00000008H 
MLS_READONLY	EQU	00000010H 
MLS_IGNORETAB	EQU	00000020H 
MLS_DISABLEUNDO	EQU	00000040H 

FORMATRECT	STRUC
MLEFRD_cxFormat	DD	?
MLEFRD_cyFormat	DD	?
FORMATRECT	ENDS

MLECTLDATA	STRUC
MLECTL_cbCtlData	DW	?
MLECTL_afIEFormat	DW	?
MLECTL_cchText	DD	?
MLECTL_iptAnchor	DD	?
MLECTL_iptCursor	DD	?
MLECTL_cxFormat	DD	?
MLECTL_cyFormat	DD	?
MLECTL_afFormatFlags	DD	?
MLECTLDATA	ENDS
MLFFMTRECT_LIMITHORZ	EQU	00000001H 
MLFFMTRECT_LIMITVERT	EQU	00000002H 
MLFFMTRECT_MATCHWINDOW	EQU	00000004H 
MLFFMTRECT_FORMATRECT	EQU	00000007H 
MLFIE_CFTEXT	EQU	0 
MLFIE_NOTRANS	EQU	1 
MLFIE_WINFMT	EQU	2 
MLFIE_RTF	EQU	3 

MLEOVERFLOW	STRUC
overflow_afErrInd	DD	?
overflow_nBytesOver	DD	?
overflow_pixHorzOver	DD	?
overflow_pixVertOver	DD	?
MLEOVERFLOW	ENDS
MLFEFR_RESIZE	EQU	00000001H 
MLFEFR_TABSTOP	EQU	00000002H 
MLFEFR_FONT	EQU	00000004H 
MLFEFR_TEXT	EQU	00000008H 
MLFEFR_WORDWRAP	EQU	00000010H 
MLFETL_TEXTBYTES	EQU	00000020H 

MLEMARGSTRUCT	STRUC
margin_afMargins	DW	?
margin_usMouMsg	DW	?
margin_iptNear	DD	?
MLEMARGSTRUCT	ENDS
MLFMARGIN_LEFT	EQU	0001H 
MLFMARGIN_BOTTOM	EQU	0002H 
MLFMARGIN_RIGHT	EQU	0003H 
MLFMARGIN_TOP	EQU	0004H 
MLFQS_MINMAXSEL	EQU	0 
MLFQS_MINSEL	EQU	1 
MLFQS_MAXSEL	EQU	2 
MLFQS_ANCHORSEL	EQU	3 
MLFQS_CURSORSEL	EQU	4 
MLFCLPBD_TOOMUCHTEXT	EQU	00000001H 
MLFCLPBD_ERROR	EQU	00000002H 

SEARCH	STRUC
search_cb	DW	?
search_pchFind	DD	?
search_pchReplace	DD	?
search_cchFind	DW	?
search_cchReplace	DW	?
search_iptStart	DD	?
search_iptStop	DD	?
search_cchFound	DW	?
SEARCH	ENDS
MLFSEARCH_CASESENSITIVE	EQU	00000001H 
MLFSEARCH_SELECTMATCH	EQU	00000002H 
MLFSEARCH_CHANGEALL	EQU	00000004H 
MLM_SETTEXTLIMIT	EQU	01b0H 
MLM_QUERYTEXTLIMIT	EQU	01b1H 
MLM_SETFORMATRECT	EQU	01b2H 
MLM_QUERYFORMATRECT	EQU	01b3H 
MLM_SETWRAP	EQU	01b4H 
MLM_QUERYWRAP	EQU	01b5H 
MLM_SETTABSTOP	EQU	01b6H 
MLM_QUERYTABSTOP	EQU	01b7H 
MLM_SETREADONLY	EQU	01b8H 
MLM_QUERYREADONLY	EQU	01b9H 
MLM_QUERYCHANGED	EQU	01baH 
MLM_SETCHANGED	EQU	01bbH 
MLM_QUERYLINECOUNT	EQU	01bcH 
MLM_CHARFROMLINE	EQU	01bdH 
MLM_LINEFROMCHAR	EQU	01beH 
MLM_QUERYLINELENGTH	EQU	01bfH 
MLM_QUERYTEXTLENGTH	EQU	01c0H 
MLM_FORMAT	EQU	01c1H 
MLM_SETIMPORTEXPORT	EQU	01c2H 
MLM_IMPORT	EQU	01c3H 
MLM_EXPORT	EQU	01c4H 
MLM_DELETE	EQU	01c6H 
MLM_QUERYFORMATLINELENGTH	EQU	01c7H 
MLM_QUERYFORMATTEXTLENGTH	EQU	01c8H 
MLM_INSERT	EQU	01c9H 
MLM_SETSEL	EQU	01caH 
MLM_QUERYSEL	EQU	01cbH 
MLM_QUERYSELTEXT	EQU	01ccH 
MLM_QUERYUNDO	EQU	01cdH 
MLM_UNDO	EQU	01ceH 
MLM_RESETUNDO	EQU	01cfH 
MLM_QUERYFONT	EQU	01d0H 
MLM_SETFONT	EQU	01d1H 
MLM_SETTEXTCOLOR	EQU	01d2H 
MLM_QUERYTEXTCOLOR	EQU	01d3H 
MLM_SETBACKCOLOR	EQU	01d4H 
MLM_QUERYBACKCOLOR	EQU	01d5H 
MLM_QUERYFIRSTCHAR	EQU	01d6H 
MLM_SETFIRSTCHAR	EQU	01d7H 
MLM_CUT	EQU	01d8H 
MLM_COPY	EQU	01d9H 
MLM_PASTE	EQU	01daH 
MLM_CLEAR	EQU	01dbH 
MLM_ENABLEREFRESH	EQU	01dcH 
MLM_DISABLEREFRESH	EQU	01ddH 
MLM_SEARCH	EQU	01deH 
MLM_QUERYIMPORTEXPORT	EQU	01dfH 
MLN_OVERFLOW	EQU	0001H 
MLN_PIXHORZOVERFLOW	EQU	0002H 
MLN_PIXVERTOVERFLOW	EQU	0003H 
MLN_TEXTOVERFLOW	EQU	0004H 
MLN_VSCROLL	EQU	0005H 
MLN_HSCROLL	EQU	0006H 
MLN_CHANGE	EQU	0007H 
MLN_SETFOCUS	EQU	0008H 
MLN_KILLFOCUS	EQU	0009H 
MLN_MARGIN	EQU	000aH 
MLN_SEARCHPAUSE	EQU	000bH 
MLN_MEMERROR	EQU	000cH 
MLN_UNDOOVERFLOW	EQU	000dH 
MLN_CLPBDFAIL	EQU	000fH 
endif 
