;'ramtest.asm'
;Testprogramm fÅr ein RAM 6116 (8 Bit x 2K)

	ORG 0E000h
	jmp 0

	ORG 0E100h
	jmp init

init:
	mvi b, 0
	mvi c, 0ffh
	mvi h, 81h
	mvi l, 00h
start:
	;Speicherbereich fÅllen - abwechselnd mit 00h und FFh
	mov a,b
	mov m,a               	
	inx h
	mov a,l
	cpi 0
	jz  weiter
	mov a,c
	mov m,a
	inx h
	mov a,l
	cpi 0
	jnz start
weiter:
	hlt		
		