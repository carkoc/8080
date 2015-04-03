;----------------------------------------------------------------------------
;		I N C l u d e - File
;		*** 'input2.inc  ***
;		10.1.93 CK
;----------------------------------------------------------------------------
; Inhalt:	UP 'eingabe'
;Aufgabe:
;	Eingabe einer zweistelligen Hex-Zahl Åber die Tastatur des Profi5.
;	Die zuerst eingegebene Ziffer wird als 16er-Stelle betrachtet,
;	die danach eingegebene Ziffer als 1er-Stelle.
;	RÅckgabewert:	Am Ende des UP steht die eingegebene zweistellige
;			Hex-Zahl im Akku (16er-Stelle im oberen Nibble,
;					   1er-Stelle im unteren Nibble).
;----------------------------------------------------------------------------

; * UP *
input2:	
	call tastd      ;mit Hilfe des Monitor-UP "tastd"
	mov b, a	;  die 16er-Stelle einlesen & im B-Reg. zw.sp.
	call tastd      ;  und ebenso
	mov c, a        ;  die 1er-Stelle einlesen  & im C-Reg. zw.sp.
	
	;* Bildung einer zweistelligen Hex-Zahl
	;* aus den beiden eingegebenen Ziffern
	mov a, b  	;eingegebene 16er-Stelle
	rlc		;  ins
	rlc             ;  obere
	rlc             ;  Nibble (des Akkus)
	rlc             ;  rotieren
	add c           ;und die 1er-Stelle hinzuaddieren
ret	;RÅcksprung aus dem UP 'input2'
;----------------------------------------------------------------------------