;---------------------------------------------------------------------------
;*****************	INClude-File 'prn_char.inc'    *********************
;			CK 14.4.93
;___________________________________________________________________________
;***  UP 'print_char' zum Ausdrucken eines Zeichens mit Fehlererkennung  ***
;*** Aufrufwert:   Das zu druckende Zeichen mu· sich im ASCII-Format
;*** 		   im Akku befinden.
;*** RÅckgabewert: -
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
print_char:	
	pusha
	push psw	;zu druckendes Zeichen auf dem Stack sichern
	in   statusreg	;ÅberprÅfen ob ein Drucker-ERROR (3.Bit) vorliegt
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
	mvi  A,00000100b ;Strobe aktivieren(0.Bit low-active)
	out  kontrollreg ;
	push d
	call t45	 ;  4,5ms verzîgern
	pop  d
	mvi  A,00000101b ;
	out  kontrollreg ;Strobe deaktivieren
noch_busy:
	in   statusreg	;Statusregister einlesen
	ani  80h	;Busy-Bit (PB7) maskieren
	;!!! FöR "ORIGINAL BUSY" JNZ einsetzen (Opcode C2h):
	jz  noch_busy	 ;NUR beim 8080SIM ist Busy 0-aktiv!
	popa
ret 	;RÅcksprung aus dem UP 'print_char'
;---------------------------------------------------------------------------
