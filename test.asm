ORG 8000h
jmp start

min db 4
max db 9

start:
	mvi  a, 99h
	dcr  a
	dcr  a
	dcr  a
	dcr  a
	dcr  a
	sui  5h
	hlt

	call tastm
	lhld min	;   Inhalt der Sp.adr. min (offset 0) ins L-Reg.
			; & Inhalt der Sp.adr  min (offset 1) ins H-Reg.
                        ;			(hier: min+1=max)
	cmp  l		;mit dem Minimalwert vergleichen:
	jm   kleiner	;  falls Ergebnis negativ ist:
			;  => weiter bei kleiner
	cmp  h		;mit dem Maximalwert vergeichen:
	jp   groesser  	;  falls Ergebnis positiv ist:
			;  => weiter bei groesser
kleiner:
jmp start

groesser:
jmp start
;***************************************************************************

END