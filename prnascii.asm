 %nosyms
; 'prnascii.asm'
; Ausdrucken aller ASCII-Zeichen von 33d bis 255d
; Druckersteuerung ber den 8255 im Modus 0:
;							Sub-D-25-PIN
; Belegung des 8255:	PA0..7 = Datenleitungen D0..7  	2..9

;			PB7    = Busy			11
;			PB3    = -Error			15

;			PC0    = -Strobe		1

;---------------------------------------------------------------------------
;*** Namen der relevanten Sp.adr. zur parallelen Schnittstelle ***
	basisadr    EQU 20h	  ;(00h=8255/1, 10h=8255/2, 20h=8255/3)

	;Ab der Ver 2.53 des 8080sim wird die Adresse 20h auf LPTx
	;abgebildet (entsprechende Einstellung in der 'com.dat')!

	datenreg    EQU basisadr +0 ;Datenregister
	statusreg   EQU basisadr +1 ;Statusregister
	kontrollreg EQU basisadr +2 ;Kontrollregister
	configreg   EQU basisadr +3 ;Konfigurationsregister/
            		             ;Steuer-wort-register
        LF	    EQU 0Ah
	CR	    EQU 0Dh
	SPACE	    EQU 20h	
;--------------------------------------------------------------------------

	ORG 8000h
	jmp init

;--------------------------------------------------------------------------
	mvi  a,lf
	call print_char
	mvi  a,cr
	call print_char

	ORG 8010h
;---------------------------------------------------------------------------
;--------------------------------------------------------------------------
;*** UP 'print_char' zum Ausdrucken eines Zeichens mit Fehlererkennung ***
;*** Aufrufwert:   Das zu druckende Zeichen muá sich im ASCII-Format
;*** 		   im Akku befinden.
;*** Rckgabewert: -
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
print_char:	
	push psw	;zu druckendes Zeichen auf dem Stack sichern
	in   statusreg	;berprfen ob ein Drucker-ERROR (3.Bit) vorliegt
	ani  08h	;Error-Bit (0-aktiv) maskieren:
	jnz  prn_ok  	;  wenn kein Error (-Error=1): -> weiter bei prn_ok

	lxi  b,prnerror	;  wenn Error vorliegt (-Error=0):
	call text8	;  'PrnError' im Display ausgeben
immer_noch_error:
	in   statusreg		;solange Statusregister einlesen
	ani  08h		;  und Error-Bit maskieren
	jz   immer_noch_error	;bis Error-Bit=1

	lxi  b,printing		;dann 'PrintinG'
	call text8		;  im Display ausgeben
		
prn_ok:
	pop  psw	 ;zu druckendes Zeichen wieder vom Stack holen
	out  datenreg    ;Akkuinhalt (Zeichen) ins Datenregister schreiben
	mvi  A,00000100b ;Daten bernehmen: Strobe (0.Bit low-active)
	out  kontrollreg
	call t45	 ;4,5ms verz”gern
	mvi  A,00000101b ;Strobe deaktivieren
	out  kontrollreg
noch_busy:
	in   statusreg	;Statusregister einlesen
	ani  80h	;Busy-Bit (PB7) maskieren
	jz  noch_busy	;wenn Busy=1, noch auf Busy=0 warten

ret 	;Rcksprung aus dem UP 'print_char'
;---------------------------------------------------------------------------

;---------------------------------------------------------------------------
;*** UP 'akku_drucken' zum Drucken des Akku-Inhalts ***
;   (mit Umsetzung der Ziffern in den ASCII-Code)
akku_drucken:
	call basci	;Akku-Inhalt in ASCII-Zeichen wandeln
			;Rckgabewerte: BC-Reg.
	;** oberes Nibble drucken **
	mov  a,b
	call print_char
	;** unteres Nibble drucken **
	mov  a,c
	call print_char
ret	;Rcksprung aus dem UP 'akku_drucken'
;--------------------------------------------------------------------------

	ORG 8100h	;*** HAUPTPROGRAMM ***

ascii_zeichen 	db 00h
spalten  	db 00h	;Z„hlvariable fr die gedruckten Spalten pro Zeile
init:
	lxi  sp,087B1h          ;Stackpointer initialisieren (Sp.ende 87FFh)
	mvi  a,82h		;Modus 0 d. 8255:
	out  configreg		;   	  A E AA
	mvi  a,33		;1.ASCII-Zeichen
	sta  ascii_zeichen      ;  festlegen
	lxi  b, printing	;'Printing'
	call text8		;  im Display ausgeben
start:
	mvi  a,0		;Spaltenz„hler auf
	sta  spalten		;  Null setzen
	mvi  a,lf
	call print_char
	mvi  a,cr
	call print_char
weiter_in_zeile:
	lda  ascii_zeichen	;ASCII-Code (2 Hex-Ziffern)
	call akku_drucken	;  drucken

	mvi  a,space
	call print_char	
	
	lda  ascii_zeichen	;Code-Zeichen fr den
	call print_char         ;  2stelligen ASCII-Code drucken

	mvi  a,space
	call print_char
	mvi  a,space
	call print_char

	lda  ascii_zeichen	;ASCII-Code
	inr  a                  ;  um 1 erh”hen
	sta  ascii_zeichen      ;  und speichern
	ora  a			;Wenn ASCII-Code=0 (wg. FFh + 1 = 00h & C=1),
	jz   ende		;  PRG ist beendet
	
	lda  spalten            ;sonst: Zahl der gedruckten Spalten
	inr  a			;       um 1 erh”hen
	sta  spalten		;	und speichern
	cpi  11		 	;Ist schon die max. Spaltenzahl gedruckt?
	jz   start		;  ja: -> neue Zeile beginnen
	jmp  weiter_in_zeile	;nein: -> weiter in derselben Zeile drucken
ende:
	mvi  a,lf
	call print_char
	mvi  a,cr
	call print_char
	lxi  b,prnready
	call text8
	hlt

;*** Datenbereich ***
         ORG 8200h
AA	 db 77h,77h
EA	 db 79h,77h
prnerror db 73h,50h,54h,79h,50h,50h,5ch,50h
printing db 73h,50h,04h,54h,78h,04h,54h,3dh
prnready db 73h,50h,54h,50h,79h,77h,5eh,6eh

         END