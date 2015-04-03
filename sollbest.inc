; **************** INClude-File sollbest.inc ******************************
; enthÑlt das gleichnamige UP 'sollbest'
; zur Eingabe eines Sollbereichs (Minimal- und Maximalwert)
; Åber die Tastatur (00h-FFh)
; ->RÅckgabewerte: Minimalwert in der Sp.adr. 'min'
;		&  Maximalwert in der Sp.adr. 'max'


minfrage db 54h,06h,54h,0,0dbh,0,0,0
maxfrage db 54h,77h,76h,0,0dbh,0,0,0

sollbest:
	lxi  b, minfrage
	call text8
	call input2	;Eingabe einer 2stelligen Hex-Zahl
	sta  min 	;  als Minimalwert
	lxi  b, maxfrage
	call text8
	call input2	;Eingabe einer 2stelligen Hex-Zahl
	sta  max	;  als Maximalwert

	call dunkl	;Display "dunkel" steuern
ret
;*********************************************************
min	db 0
max	db 0