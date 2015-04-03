%nosyms
; 'disasm.asm'
; Versuch zur Programmierung eines DisAssemblers fÅr den 8080

	ORG 8300h
	jmp init

INCLUDE    tools.inc	;pusha & popa als Macros!
INCLUDE  par_adr.inc	;Registernamen des 8255 als Centronics-Schnittstelle
INCLUDE prn_char.inc	;UP 'print_char' zum Drucken eines Zeichens
			;  Aufrufwert: ASCII-Code des Zeichens im Akku
INCLUDE prn_akku.inc	;UP 'print_akku' zum Drucken des Akku-Inhalts
			;  als zweistellige Hex-Zahl!
			;  (enthÑlt eine ASCII-Wandlung)

;---------------------------------------------------------------------------
MACRO   PRN_NEW_LINE
	mvi  a,LF
	call print_char
	mvi  a,CR
	call print_char
ENDM
;---------------------------------------------------------------------------

;---------------------------------------------------------------------------
; *** UP 'print_mnemonic' zum Ausdrucken von Mnemo-Befehlen ***
;
; Aufrufwert:   !!!BC!!! zeigt auf das erste zu druckende Zeichen
;               - Endkennzeichen der Zeichenkette: ASCII-Code 00h!
;___________________________________________________________________________
print_mnemonic:
	ldax b
	cpi  0                  ;Endzeichen schon erreicht?
rz      ;RÅcksprung aus dem UP 'print_mnemonic'
	call print_char
	inx  b
	jmp  print_mnemonic
;---------------------------------------------------------------------------

; { M A I N }

AA       db 77h,77h
EA       db 79h,77h
prnerror db 73h,50h,54h,79h,50h,50h,5ch,50h
printing db 73h,50h,04h,54h,78h,04h,54h,3dh
prnready db 73h,50h,54h,50h,79h,77h,5eh,6eh

init:
	lxi sp,087B1h
	mvi a,82h       ;Modus 0 d. 8255:
	out modusreg    ;         A E AA

INCLUDE aa_ea_in.inc   ;Modul zur Eingabe einer Anfangs- und einer Endadresse
		       ;RÅckgabewerte: AA im Rp HL, EA im Rp DE	
decod_opcode:
;** Zeilenanfang: Adresse drucken, aus der danach der Opcode gelesen wird **
	mov  a,h
	call akku_drucken
	mov  a,l
	call akku_drucken
	mvi  a,':'
	call print_char
	mvi  a,SPACE
	call print_char

	mov  a,M        ;Opcode lesen
	INCLUDE compare.inc	;enthÑlt alle Vergleiche zur Interpretation
				;  des gelesenen Opcodes
next:
	PRN_NEW_LINE	  ;Macro (!) zum Drucken von LF+CR
	call subhd	  ;wenn (HL)=(DE) => Zero-Flag=1
	jz   ende	  ;ja:  DisAssemblierung ist beendet
	inx  h		  ;sonst:
	jmp  decod_opcode

ende:
	PRN_NEW_LINE	  ;Macro (!) zum Drucken von LF+CR
	lxi  b,prnready
	call text8
	hlt

;============================================================================
Plus_1_Byte:
;ErgÑnzen des 1-Byte-Datums eines 2-Byte-Befehls!
	inx  h            ;nÑchstes Byte
	mov  a,M          ;  lesen
	call print_akku   ;  und so im Hex-Code drucken
ret     ;RÅcksprung aus dem UP 'Plus_1_Byte'
;----------------------------------------------------------------------------
Plus_2_Byte:
;ErgÑnzen der 2-Byte-Datums eines 3-Byte-Befehls!
	inx  h
	inx  h
	mov  a,M
	call print_akku
	dcx  h
	mov  a,M
	call print_akku
	inx  h
ret	;RÅcksprung aus dem UP 'Plus_2_Byte'
;============================================================================

;----------------------------------------------------------------------------
nop:
	lxi  b,mnemonic00
	call print_mnemonic
	jmp  next
;----------------------------------------------------------------------------
lxib:
	lxi  b,mnemonic01
	call print_mnemonic
	call Plus_2_Byte
	jmp  next
;----------------------------------------------------------------------------
staxb:
	lxi  b,mnemonic02
	call print_mnemonic
	call Plus_2_Byte
	jmp  next
;----------------------------------------------------------------------------
inxb:
	lxi  b,mnemonic03
	call print_mnemonic
	jmp  next
;----------------------------------------------------------------------------
inrb:
	lxi  b,mnemonic04
	call print_mnemonic
	jmp  next
;----------------------------------------------------------------------------
dcrb:
	lxi  b,mnemonic05
	call print_mnemonic
	jmp  next
;----------------------------------------------------------------------------
mvib:
	lxi  b,mnemonic06
	call print_mnemonic
	call Plus_1_Byte
	jmp  next
;----------------------------------------------------------------------------
rlc:
	lxi  b,mnemonic07
	call print_mnemonic
	jmp  next
;----------------------------------------------------------------------------
dadb:
	lxi  b,mnemonic09
	call print_mnemonic
	jmp  next
;----------------------------------------------------------------------------
ldaxb:
	lxi  b,mnemonic0a
	call print_mnemonic
	jmp  next
;----------------------------------------------------------------------------

INCLUDE mnemo.inc	;enthÑlt den auszudruckenden Mnemonic-Text
			;  der einzelnen Befehle
	;Aufbau: mnemonicXY db '<Mnemo-Text>',0 (<-Endzeichen!)

;  TESTPROGRAMM
   ORG 08500h
db 00h, 01h,45h,67h, 02h,67h,45h, 03h, 03h, 04h, 05h, 06h,0FFh, 07h, 07h
db 22h,29h,0B3h

	 END	;... des Quellcodes