; 'ad-wandl.asm'
; Programmierung eines A/D-Wandlers
; - fÅr den Profi-8K-ROM (->F8=Optionen)!

	ORG 8000h
	jmp init

INCLUDE ad1flank.inc

INCLUDE division.inc
INCLUDE akku10.inc

INCLUDE hx_dz.inc
	;Aufgabe:	Umrechnung einer 2stelligen Hex-Zahl
	;		in eine 3stellige Dezimalzahl
	;Aufrufwert: 	Hex-Zahl im Akku
	;RÅckgabewerte:	Hunderter  B-Reg. (low nibble),
	;		Zehner     C-Reg. (high nibble)
	;		Einer      C-Reg. (low nibble).

INCLUDE anzeige2.inc	;UP 'anzeige'!!!
	;Aufgabe:	Anzeige von zwei 3stelligen Dezimalzahl im Display
	;Aufrufwerte:   Hunderter-Stelle1 im B-Reg. (low  nibble)
	;		   Zehner-Stelle1 im C-Reg. (high nibble)
	;		    Einer-Stelle1 im C-Reg. (low  nibble)
	;		Hunderter-Stelle2 im D-Reg. (low  nibble)
	;		   Zehner-Stelle2 im E-Reg. (high nibble)
	;		    Einer-Stelle2 im E-Reg. (low  nibble)
	;RÅckgabewerte: keine
	;verwendete Register:
	;	HL = Zeiger auf 7-Segment-ABC-Code
	;	BC = Zeiger auf Textanfang fÅr das Monitor-UP 'text8'
;---------------------------------------------------------------------------
INCLUDE input2.inc

Text_Abgleich  db 77h,7ch,3dh,38h,79h,04h,58h,74h
Text_Divisor   db 5eh,04h,3eh,04h,6dh,5ch,50h,0
divisor  db 0

init:
	lxi sp,087C1h
	mvi a,99h	;8255 konfigurieren:
	out modusreg1	;	E A EE

	lxi  b,Text_Abgleich
	call text8
	mvi  a,01h
	call secd
	;//// Maximale Spg. Åber den DA-Wandler ausgeben
        mvi	a,250	;Beispiel zur Ermittlung des Umrechnungsfaktors
			;	 250 : 10 Volt = 25.00 V^-1
	out	digi_spg
	;//// Eingabe des Divisors (als Dezimalzahl!) zur Me·wertumrechnung!
	lxi  b,Text_Divisor
	call text8
	call input2
	call dezhx
        sta  divisor

jmp start

messwert  db 0	;Sp.adr. fÅr den 2stelligen Hex-Wert (ZÑhlerstand)
nachkomma db 0

start:
	call ad_wandlung	;RÅckgabewert im Akku
	;* Eingabe eines Me·wertes
;	call input2
	sta  messwert

	;Umrechnung mit Divisor vorbereiten
	lda  divisor 	;Divisor
	mov  b,a        ;  ins B-Reg.
	lda  messwert
	call division	;(D-Reg) = (Akku) : (B-Reg)
			;(E-Reg) := 1 Nachkommastelle
	mov  a,e	;Nachkommastelle
	sta  nachkomma	;  in der Sp.adr. 'nachkomma' sichern fÅr UP anzeige
	mov  a,d	;Vorkommazahlen
	call hx_dz      ;  in eine Dezimalzahl umwandeln
	mov  d,b	;fÅr das UP 'anzeige'	
	mov  e,c	;fÅr das UP 'anzeige'	

 	lda  messwert
	call hx_dz		;RÅckgabewerte im BC-Reg.
	call anzeige		;verwendet das BC-und das DE-Reg.
jmp start
	
ORG 8200h
;Codes der Ziffern 0-9 im "7-Segment-ABC":
;       (zur Ausgabe von Ziffern mit Hilfe des Monitor-UP 'text8'!!!)
segmentabc db 3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh
;  =            0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9

	