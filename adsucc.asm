	Org	08000h
	jmp	start

Include 8255def.inc
include macro1.inc
Include p5-anz.inc

sub:	
	mov	a,b	; letzte Bitpositon holen
	rrc		; neu einstellen
	mov	b,a	; und sichern
	mov	a,c	; Zwischenergebnis holen
	ora	b	; Neues Ausgabebyte herstellen
	ret

add:	
	mov	a,c	; Zwischenergebnis holen
	ora	b	; und
	mov	c,a     ; aktualisieren
	mov	a,b	; letzte Bitposition holen
	rrc		; neu einstellen
	mov	b,a	; und sichern
	ora	c	; Neues Ausgabebyte herstellen
	stc		; Cy setzen
	ret	

Start:
	mvi	a,090h 	; Port initialisieren PA=Ein, PB=Aus
	out	ctl	; Steuerport 8255 (s. 8255def.asm)
	lxi	h,08000h; Speicherzelle fÅr Endergebnis
loop2:	mvi	b,080h	; Anfangswert
	mov	a,b     ; = Erster Ausgabewert
	mvi	e,8     ; 8 DurchlÑufe
	mvi	c,0	; fÅr Zwischen- u. Endergebnis

loop:	
	out	pb	; Wert	ausgeben
	in	pa	; Ergebnis abfragen (Bit 0 von PA)
	rrc	a	; Bit 0 -> Cy
	cc	add	; Wert zu klein
	cnc	sub	; Wert zu gro·
	dcr	e	; Durchlauf erledigt
	jnz	loop	; Letzter Durchlauf? Wenn nein weiter
	mov	m,c	; Endergebnis speichern
	mov	a,c	; zum ÅberprÅfen
	out	pb	;	"
	call	disp
	jmp	loop2

disp:	
	Push	h
	push	psw
	lxi	h,8000h
	mov	a,m
	call	anz	; Wert auf dem Display anzeigen
	pop	psw
	pop	h
	ret

	end

