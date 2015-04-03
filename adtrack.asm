	Org	08000h
	jmp	start

Include 8255def.inc


Start:
	mvi	a,098h	; 8255 initialisieren (PA= Eingang, PB= Ausgang)
	out	ctl	; Steuerwort ausgeben
	mvi	b,080h	; Anfangswert <> 5V
	mvi	b,0	; Register fr den Wandlungswert
	lxi	h,083ECh; Speicherstelle fr Anzeige
loop:	
	mov	a,b	; aktuellen Wert holen
	out	pb	; und ausgeben
	in	pa	; Komparator abfragen (Bit 0 von PA)
	rrc	a	; Bit 0 -> Cy
	cnc	dec	; zu groá ? -> Dann verkleinern
	cc	inc	; zu klein? -> Dann vergr”áern
	mov	m,b
	jmp	loop

dec:	
	dcr	b	; Wertregister verkleinern
	ret
inc:	
	inr	b	; Wertregister vergr”áern
	ret	

        end