;***************************************************************************
;* 		UP 'ad_wandlung' 					   *
;*		nach dem Einflankenverfahren				   *
;***************************************************************************
;A/D-Wandlung nach dem Z„hlverfahren (Z„hlen, solange kleiner ->Aufrunden)
;Rckgabewert:	im Akku befindet sich die ermittelte Spannung
;		als 2stellige Hex-Zahl (Digitalwert)
;Prinzip:	Der Mikrocomputer arbeitet als "Z„hler"
;		und beendet die Wandlung, sobald der Analogwert des
;		Z„hlerstandes (etwas) gr”áer als der Meáwert ist!
;		(Einflankenverfahren)

basisadr1   EQU 10h       ;(00h=8255/1, 10h=8255/2, 20h=8255/3)
op_out      EQU basisadr1 +0 ;Ausgangssignal des OP
digi_spg    EQU basisadr1 +1 ;Digitale Ausgangsspannung
modusreg1   EQU basisadr1 +3 ;Modus-/Steuerwort-register
;---------------------------------------------------------------------------
ad_wandlung:
	mvi e,00h	;Anfangswert 00h
vergleich:
	mov a,e		;aktuellen "Z„hlerstand"
	out digi_spg	;  ber den D/A-Wandler ausgeben
	in op_out	;Einlesen des OP-Ausgangssignals:
			;   zu wandelnde Spg. > Analogwert d. Digitalspg. = 1
			;   zu wandelnde Spg. < Digi_Spg (Analogwert)     = 0	
	ani 01h		;PA0 maskieren
	jz  fertig	;PA0 = 0: fertig, da gewandelter Wert groesser ist
kleiner:
	mov a,e
	cpi 0FFh	;War der Z„hlerstand 255d erreicht,
			;  aber nicht ausreichend?
	jz  zu_gross	;ja:  fertig wg. Meábereichs-šberschreitung!
count:                  ;sonst:
	inr e		;Weiter-Hochz„hlen des Digitalwertes
	jmp vergleich   ;  und mit diesem neuen Wert vergleichen
;-----------------------
zu_gross:
	lxi b, zugross
	call text8
fertig:
	mov a,e		;ermittelter Hex-Wert in den Akku laden
	ret	;Rcksprung aus dem UP 'ad-wandlung'
zugross db 5ah,1ch,00h,3dh,50h,5ch,6dh,6dh
;---------------------------------------------------------------------------
