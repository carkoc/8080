; 'uhrtest.asm'
; Programmierung einer Hardware-Interrupt-gesteuerten Uhr!
; 17.1.93 CK
	
	ORG 8000h
	jmp init

INCLUDE display.inc	;enthÑlt das gleichnamige UP zur Ansteuerung des
			;  Displays des Profi5-Computers (nur Ziffern)
INCLUDE input2.inc	;enthÑlt das gleichnamige UP zur Eingabe einer
			;  2-stelligen Hex-Zahl Åber die Tastatur
INCLUDE uhrstell.inc
INCLUDE   uhranz.inc

sekunden DB 0
minuten  DB 0
stunden  DB 0	

init:
	lxi  sp, 083c1h		;Stackpointer initialisieren
	call uhrstell	
        ei

; *** Main ***
start:
	nop
	nop
	call uhranz
jmp start
	

;*** Uhr um 1s weitersetzen  ***
;*   Interrupt-Unterprogramm   *
ORG 8100h
;	INCLUDE uhrset.inc
;*** Uhr um 1s weitersetzen  ***
;*   Interrupt-Unterprogramm   *
	di			;Mîglichkeit zum Hard-Int. abschalten
	push psw        ;Flag-Reg.,
	push b          ;  BC-Reg.,
	push d          ;  DE-Reg. und
	push h          ;  HL-Reg. auf dem Stack sichern
	lda sekunden		;Sekunden
	inr a			;  um 1 weitersetzen
	sta sekunden		;  um abspeichern
	cpi 60			;Ist schon 1 Minute = 60s vorbei?
	jnz return		; nein: -> Uhrzeit ist korrekt gestellt
	mvi a, 0                ;sonst: Sekunden auf Null setzen
	sta sekunden            ;       (1 volle Minute erreicht)

        lda minuten		;Minuten
	inr a                   ;  um 1 weitersetzen
	sta minuten             ;  und abspeichern
	cpi 60                  ;Ist schon 1 Stunde = 60min vorbei?
	jnz return     ; nein: -> Uhrzeit ist korrekt gestellt
	mvi a, 0                ;sonst: Minuten auf Null setzen
	sta minuten             ;	(1 volle Stunde erreicht)

	lda stunden		;Stunden
	inr a                   ;  um 1 weitersetzen
	sta stunden             ;  und abspeichern
	cpi 24                  ;Ist schon 1 Tag = 24 h vorbei?
	jnz return		; nein: -> Uhrzeit ist korrekt gestellt
	mvi a, 0                ;sonst: Stunden auf Null setzen
	sta stunden             ;       (1 voller Tag ist vergangen)
return:
	pop h		
	pop d		
	pop b
	pop psw
	ei
ret	;RÅcksprung aus dem UP 'uhrset'	

;----------------------------------------------------------------------------
END	; von uhrtest.asm!