;---------------------------------------------------------------------------
;*** UP 'print_akku' zum Drucken des Akku-Inhalts ***
;   (mit Umsetzung der Ziffern in den ASCII-Code)
print_akku:
	call basci	;Akku-Inhalt in ASCII-Zeichen wandeln
			;RÅckgabewerte: BC-Reg.
	;** oberes Nibble drucken **
	mov  a,b
	call print_char
	;** unteres Nibble drucken **
	mov  a,c
	call print_char
ret	;RÅcksprung aus dem UP 'print_akku'
;--------------------------------------------------------------------------
