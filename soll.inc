; ********* UP 'soll' **************
maxfrage db 54h,77h,76h,0,0dbh,0,0,0
minfrage db 54h,06h,54h,0,0dbh,0,0,0

soll:
	lxi  b, maxfrage
	call text8
	call input2	;Eingabe einer 2stelligen Hex-Zahl
	sta  max	;  als Maximalwert
	lxi  b, minfrage
	call text8
	call input2	;Eingabe einer 2stelligen Hex-Zahl
	sta  min 	;  als Minimalwert
	call dunkl	;Display "dunkel" steuern
ret
;*********************************************************
max	db 0
min	db 0