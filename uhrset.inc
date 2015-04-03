;*** Uhr um 1s weitersetzen  ***
;*   Interrupt-Unterprogramm   *
	di			;Mîglichkeit zum Hard-Int. abschalten
	pusha
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
	popa
	ei
ret	;RÅcksprung aus dem UP 'uhrset'	

MACRO   pusha
	push psw        ;Flag-Reg.,
	push b          ;  BC-Reg.,
	push d          ;  DE-Reg. und
	push h          ;  HL-Reg. auf dem Stack sichern
ENDM
MACRO   popa
	pop h		;  HL-Reg.,
	pop d		;  DE-Reg.,
	pop b           ;  BC-Reg. und
	pop psw         ;Flag-Reg. vom Stack holen (LIFO-Prinzip
ENDM			;			    =Last In First Out!!!)
;----------------------------------------------------------------------------