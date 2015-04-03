;-------------------------------------------------------------------------
;	*** INCLUDE-File 'drucken.inc' ***
;	enth„lt das gleichnamige UP 'drucken'

;* nur fr das UP 'drucken' ben”tigte INCLUDE-Files *
	;enth„lt die relevanten Adressen der parallelen Schnittstelle
INCLUDE par_adr.inc
	;enth„lt die UP 'print_string' und 'print_char'!
INCLUDE printups.inc
;---------------------------------------------------------------------------
;*** UP Nr.3 'drucken' ***

	;** Meáwert ausdrucken **
	;(3-stelliger Dezimalwert aus hunderter,zehner,einer)
drucken:
	lda  hunderter	  ;Hunderter-Stelle des Meáwertes
	adi  30h 	  ;  (ASCII-Code der Ziffer bilden)
	call print_char	  ;  ausdrucken
	lda  zehner       ;Zehner-Stelle des Meáwertes
	adi  30h 	  ;  (ASCII-Code der Ziffer bilden)
	call print_char   ;  ausdrucken
	lda  einer        ;Einer-Stelle des Meáwertes
	adi  30h 	  ;  (ASCII-Code der Ziffer bilden)
	call print_char   ;  ausdrucken
	lxi  h, einheit
	call print_string

ret	;Rcksprung aus dem UP Nr.3 'drucken'

einheit DB ' Hz',10,13,0
;-------------------------------------------------------------------------