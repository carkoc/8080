uhranz:
	di
	lda  stunden
	call hexdz	;Umwandlung einer zweistelligen Hex-Zahl
			;  in eine zweistellige Dezimalzahl (<99!)
	sta  disp1

	lda  minuten
        call hexdz
        rrc             ;Zehner-Minuten
	rrc             ;  ins untere
	rrc             ;  Nibble
	rrc             ;  rotieren
	ani  0fh	;und maskieren
	sta  disp2    	;
	lda  minuten
	call hexdz
	rlc             ;Einer-Minuten
	rlc             ;  ins obere
	rlc             ;  Nibble
	rlc             ;  rotieren
	ani  0f0h	;und maskieren
	sta  disp3

	lda  sekunden
	call hexdz
	sta  disp4
	call decod
	ei
ret	;Rcksprung aus dem UP 'uhranz'