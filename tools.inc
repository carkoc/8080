;----------------------------------------------------------------------------
; 'tools.inc'

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