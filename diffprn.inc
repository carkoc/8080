;*********** INClude-File 'diffprn.inc' ***********************************
; Inhalt:       gleichnamiges UP 'diffprn'
; Aufgabe: 	Das UP 'diffprn' stellt fest, ob der Me·wert (Sp.adr. 'wert'
;		innerhalb des vorgebenen Sollbereichs liegt
;		(-> Sp.adr. 'min' & 'max').
;		Liegt der Me·wert au·erhalb des Sollbereichs,
;		wird Åber den Drucker eine entsprechende Fehlermeldung
;		ausgegeben.

diffprn:
	lda  wert	;Me·wert als Hex-Zahl
	lhld min	;   Inhalt der Sp.adr. min (offset 0) ins L-Reg.
			; & Inhalt der Sp.adr. max ( min+1  ) ins H-Reg.
	cmp l		;mit dem Minimalwert vergeichen:
	jc kleiner	;  falls Ergebnis negativ (Carry-/Borrow-Flag=1):
			;  => weiter bei kleiner
	cmp  h		;mit dem Maximalwert vergleichen:
	jnc   groesser	;  falls Ergebnis positiv (>0) ist:
			;  => weiter bei groesser
ret			;
;^^   	RÅcksprung aus dem UP 'abweich', da Me·wert im Sollbereich liegt!


zuklein	db '  - zu klein.',10,13,0
kleiner:	
	call me·wert_drucken
	lxi  h, zuklein
	call print_string
ret

zugro·  db '  - zu gro·.',10,13,0
groesser:
        call me·wert_drucken
	lxi  h, zugro·
	call print_string
ret
;***************************************************************************

;** Me·wert ausdrucken **
;(3-stelliger Dezimalwert aus hunderter,zehner,einer)
me·wert_drucken:
	lda  hunderter	  ;Hunderter-Stelle des Me·wertes
	adi  30h 	  ;  (ASCII-Code der Ziffer bilden)
	call print_char	  ;  ausdrucken
	lda  zehner       ;Zehner-Stelle des Me·wertes
	adi  30h 	  ;  (ASCII-Code der Ziffer bilden)
	call print_char   ;  ausdrucken
	lda  einer        ;Einer-Stelle des Me·wertes
	adi  30h 	  ;  (ASCII-Code der Ziffer bilden)
	call print_char   ;  ausdrucken
	lxi  h, einheit
	call print_string
ret
einheit DB ' Hz',0