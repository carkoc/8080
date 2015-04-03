%nosyms
; '8255mod1.asm'
; Text ausdrucken
;Druckersteuerung Åber den 8255 im Modus 1 (Handshake-Betrieb)
;notw. Hardware: MF 74121/3 zur Verl. d. -Strobe-Impulses!

	basisadr    EQU 00h
	datenreg    EQU basisadr +0 ;Datenregister
	statusreg   EQU basisadr +2 ;Statusregister des 8255/MOD1:
				    ;PC7=-Strobe,PC6=-Ackn,PC5=-Error
	steuerreg   EQU basisadr +3 ;Steuer-wort-register

	ORG 8000h

init:
	mvi a,0ABh	;Modus 1 d. 8255 = Druckermodus:
	out steuerreg	;   	PC7=-Strobe,PC6=-Ackn;PC5=-Error
	lxi h,text	;Datenzeiger HL auf Textanfang setzen	
status:
	in   statusreg		;Kanal C = Statusreg. einlesen
	ani  20h		;Error-Bit (=PC5) ist 0 bei Error
	;	xx0x AND 0010 = 0000 => Error,da Error-Bit (PC5) (low-)aktiv ist
	;	xx1x AND 0010 = 0010 => kein Error
	jnz  drucken            ;wenn kein Error: weiter drucken
	lxi  b,prnerror		;sonst: 'PrnError' im Display
	call text8		;  ausgeben
	jmp  status		;  und solange Status einlesen
				;  bis Error-Bit=1 ist
drucken:
	lxi  b,printing         ;'PrintinG' im Display
	call text8              ;	ausgeben
	mov  a,m                ;Zeichen aus Speicher lesen
	ora  a			;Ist das Zeichen = 00h?
	jz   ende		;  ja: Ende des Textes erreicht
	out  datenreg		;nein: Zeichen ins Datenregister schreiben

	push d
	call t45
	pop  d

	inx  h                  ;Datenzeiger auf das nÑchste Zeichen setzen
	jmp  drucken
ende:
	lxi  b,prnready
	call text8
	hlt

;--------------------------------------------------------------------------
	ORG 08250h
prnerror  db 73h,50h,54h,79h,50h,50h,5ch,50h
printing  db 73h,50h,04h,54h,78h,04h,54h,3dh
prnready  db 73h,50h,54h,50h,79h,77h,5eh,6eh

	ORG 08300h
text 	db 'Drau·en scheint die Sonne, weil es FrÅhling ist.',0Ah,0Dh,0	

	END