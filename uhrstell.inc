	;* Uhr stellen *
uhrstell:
	call input2	;Eingabe einer 2-stelligen Dezimalzahl
	call dezhx	;  in eine Hex-Zahl umwandeln
			;-> (Uhrzeit wird im Hex-System gespeichert)!!!
	sta  stunden	;  und als Stunden speichern
	call input2	;Eingabe einer 2-stelligen Dezimalzahl
	call dezhx	;  in eine Hex-Zahl umwandeln
	sta  minuten    ;  und als Minuten speichern
	call input2     ;Eingabe einer 2-stelligen Dezimalzahl
	call dezhx	;  in eine Hex-Zahl umwandeln
	sta  sekunden   ;  und als Sekunden speichern

	mvi a,11011011b ;Display-Maske fr "decod" festlegen ...
	sta dunkel      ;   ... und speichern
	
	mvi a,00001110b ;Interrupt-Maske festlegen ...
	sim             ;   ... und setzen
	ei	        ;"Erlaube Interrupt"
ret