;---------------------------------------------------------------------------
;			I N C l u d e - Datei
;			***  'hx_dz.inc'  ***
;			 V 1.2 - 22.12.92 CK
;---------------------------------------------------------------------------
	;Aufgabe:	Umrechnung einer 2stelligen Hex-Zahl
	;		in eine 3stellige Dezimalzahl
	;Aufrufwert: 	Hex-Zahl im Akku
	;Rckgabewerte:	Hunderter  B-Reg. (low nibble),
	;		Zehner     C-Reg. (high nibble)
	;		Einer      C-Reg. (low nibble).
;===========================================================================

;   *** "Variablendeklaration" ***
hex_rest DB 00h

;   *** UP 'hx_dz' ***
hx_dz:
	
	sta hex_rest    ;umzuwandelnden (Hex-)Wert vom Akku
			;... in die Variable "hex_rest" bertragen	
	mvi b, 0        ;Register zur Speicherung der Dezimalziffern
	mov c, b        ; (Hunderter, Zehner, Einer) auf Null setzen
   hunderter_umrechnen:
	lda hex_rest	;vom umzuwandelnden Rest-(Hex-)Wert
	sui 064h	;... 100d (=64h) subtrahieren
	jc  zehner_umrechnen	;wenn das Ergebnis negativ ist:
			;  => Zehner-Stelle umrechnen
	sta hex_rest	;sonst: - gebildete Differenz ist die jetzt
			;	  noch umzuwandelnde Rest-(Hex-)Zahl!
	inr b           ;	- Hunderter-Stelle um 1 erh”hen
	jmp hunderter_umrechnen
   zehner_umrechnen:
	lda hex_rest	;vom umzuwandelnden Rest-(Hex-)Wert
	sui 0ah		;... 10d (=0ah) subtrahieren
	jc  einer_umrechnen       ;wenn das Ergebnis negativ ist:
			;  => Einer-Stelle umrechnen
	sta hex_rest	;sonst: - gebildete Differenz ist die jetzt
			;	  noch umzuwandelnde Rest-(Hex-)Zahl!
	mov a, c	;	- Zehner-Stelle
	adi 10h		;         um 1
	mov c, a	;         erh”hen
	jmp zehner_umrechnen
   einer_umrechnen:
        lda hex_rest	;umzuwandelnden Rest-(Hex-)Wert
	sui 01h		;... um 1d (=01h) verringern
	rc		;wenn das Ergebnis negativ ist:
	  		; => Umrechnung ist beendet!
;------ ^^ Rcksprung ins Haupt-PRG !!!	
	sta hex_rest	;sonst: - gebildete Differenz ist die jetzt
			;	  noch umzuwandelnde Rest-(Hex-)Zahl!
	inr c	        ;	- Einer-Stelle um Eins erh”hen	
	jmp einer_umrechnen	
;---------------------------------------------------------------------------
