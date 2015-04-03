input:
;** Eingabe der AnfangAdresse **
	lhld AA         ;"AA" erscheint in den beiden ersten
			;       Display-Stellen bei UP "hexin"!
	call hexin      ;Eingabe einer 4stelligen Hex-Zahl Åber die Tastatur
	push h          ;  und auf dem Stack sichern
;** Eingabe der EndAdresse **
	lhld EA         ;"EA" erscheint in den beiden ersten
			;       Display-Stellen bei UP "hexin"!
	call hexin      ;Eingabe einer 4stelligen Hex-Zahl Åber die Tastatur
	xchg            ;End.adr. ins DE
	pop h           ;Anf.adr. wieder ins HL
	
	lxi  b,printing ;'PrintinG' im Display
	call text8      ;       ausgeben
