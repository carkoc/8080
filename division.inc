;***************************************************************************
;*		INCLUDE-File 'division.inc'	 			 					   *
;*			UP 'division'						   *
;**************************************************************************
;Aufrufwerte:   	Dividend im Akku   (Hexzahl)
;			Divisor  im B-Reg. (Hexzahl)
;Rckgabewert: 		Ergebnis im D-Reg. (Hexzahl)
;        	 Nachkommastelle im E-Reg. (nur bis 09h!?)
;---------------------------------------------------------------------------
;Prinzip: Anzahl der m”glichen Subtraktionen z„hlen.
;		Es wird immer abgerundet!

division:
	mvi d,00h	;Ergebnisreg. auf 0 setzen
weiter_subtrahieren:
	cmp b		;Divisor vom Dividenden subtrahieren
	jc  _nachkomma	;Nachkommastellen ermitteln,
			;	 wenn Divisor > Rest-Dividend!	
	sub b		;jetzt tats„chlich abziehen
	inr d		;
	jmp weiter_subtrahieren
_nachkomma:
	mvi e,00h
	;//// Akku = Akku * 10 ////
	call akku10
weiter_nachkomma_ermitteln:
	cmp b	
rc	;Rcksprung, wenn Divisor > Rest-Dividend
	sub b
	inr e
	jmp weiter_nachkomma_ermitteln
;***************************************************************************
