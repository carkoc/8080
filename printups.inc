;---------------------------------------------------------------------------
; * UP zur Ausgabe einer Zeichenkette auf dem Drucker *
print_string:	
	in   statusreg   ;ÅberprÅfen ob ein Drucker-ERROR (3.Bit) vorliegt
	rrc		
	rrc
	rrc
	rrc
rnc              ;ja (=0) -> RÅcksprung aus dem UP
;^^	RÅcksprung aus dem UP 'print_string' ohne zu drucken,
;	da der Drucker ERROR meldet!

	mov  A,M         ;sonst: einlesen Åbernehmen des Zeichens aus speicher'
	cpi  0    	 ;wenn Ende des string erreicht ('0')
rz  		         ;<- RÅcksprung aus dem UP 'print_string_string'
	out  datenreg    ;Zeichen in Datenregister schreiben
	mvi  A,00000100b ;Strobe aktivieren
	out  kontrollreg ;  aktivieren (low-active)
warten:	
	in   statusreg
	rlc
	jc  warten
	mvi  A,00000101b ;Strobe
	out  kontrollreg ;  deaktivieren	
	inx  H           ;Textzeiger auf das nÑchste zu druckende
			 ;  Zeichen setzen
	jmp  print_string;weiterdrucken
;---------------------------------------------------------------------------


;---------------------------------------------------------------------------
;* UP zur Ausgabe eines Zeichens auf dem Drucker *
char db 0
print_char:	
	sta  char
	in   statusreg   ;ÅberprÅfen ob ein Drucker-ERROR (3.Bit) vorliegt
	rrc		
	rrc
	rrc
	rrc
rnc              ;ja (=0) -> RÅcksprung aus dem UP
;^^	RÅcksprung aus dem UP ohne zu drucken, da Drucker ERROR meldet!

	lda  char
	out  datenreg    ;Akkuinhalt (Zeichen) ins Datenregister schreiben
	mvi  A,00000100b ;Daten Åbernehmen: Strobe (0.Bit low-active)
	out  kontrollreg
	mvi  A,00000101b ;Strobe deaktivieren
	out  kontrollreg
ret 	;RÅcksprung aus dem UP nach Drucken eines Zeichens
;---------------------------------------------------------------------------