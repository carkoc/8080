;***************************************************************************
;		UP 'akku10'
;***************************************************************************
;Verfahren: (Akku) wird mit 10d=0Ah multipliziert (9 mal selbst addiert)
;Aufrufwert:	Akku: Multiplikand
;ver„nderte Register: C-Reg. (als Z„hler)
ergebnis db 0
;---------------------------------------------------------------------------
akku10:
      push d
	sta  ergebnis
	mov  d,a
	mvi  c,0
plus:
	lda  ergebnis
	add  d
	sta  ergebnis
	inr  c
	mov  a,c
	cpi  9
	jnz  plus
	lda  ergebnis
      pop  d
ret
;***************************************************************************
