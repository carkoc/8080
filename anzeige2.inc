;***************************************************************************
;*	        INClude-File:  'anzeige2.inc'				   *
;*		UP-Aufrufname: 'anzeige'				   *
;*		V1.1 29.4.93 CK	(ursprÅnglich fÅr einen AD-Wandler)					   *
;***************************************************************************
;Aufgabe:	Anzeige einer 3stelligen Dezimalzahl
;		im Display des Profi5-8K
;Aufrufwerte:   Hunderter-Stelle im B-Reg. (low  nibble)
;		   Zehner-Stelle im C-Reg. (high nibble)
;		    Einer-Stelle im C-Reg. (low  nibble)
;
;
;RÅckgabewerte: keine
;verwendete Register: HL = Zeiger auf 7-Segment-ABC-Code
;                     BC = Zeiger auf Textanfang fÅr das Monitor-UP 'text8'
;---------------------------------------------------------------------------

anzeige:
	;*** Vorbereitungen zur Textausgabe  ***
	;* Me·wert als 3stellige Dezimalzahl in den 7-Segment-Code umwandeln *
	lxi  h, segmentabc
	;--- Hunderter-Stelle ---
	mov  l, b	;HL-Zeiger auf den entsprechenden Code setzen
			;  (Ziffer als OFFSET zur Basisadresse 'segmentabc'!)
	mov  a, M	;  Ziffern-Code der Hunderter-Stelle
	sta  segment1   ;  ins 1.Segment speichern
	;--- Zehner-Stelle ---
        mov a, c	;Zehner- und Einer-Stelle in den Akku laden
	ani 0F0h	;  Zehner-Stelle maskieren
	rrc		;  und ins untere Nibble rotieren
	rrc             ;
	rrc             ;
	rrc             ;
	mov l, a	;HL-Zeiger auf den entsprechenden Code setzen
	mov a, M	;Ziffern-Code der Zehner-Stelle
	sta segment2    ;  ins 2.Segment speichern
	;--- Einer-Stelle ---
	mov  a,c        ;Zehner- und Einer-Stelle in den Akku laden
	ani  0Fh	;  Einer-Stelle maskieren
	mov  l,a	;HL-Zeiger auf den entsprechenden Code setzen
	mov  a, M	;Ziffern-Code der Einer-Stelle
	sta  segment3   ;  ins 3.Segment speichern	

	;** umgerechneten Wert aus dem DE-Reg. anzeigen
	;--- Hunderter-Stelle ---
	mov  a,d
	ora  a
	jz   zwei_komma_eins

drei_komma_null:
	mov  l, d	;HL-Zeiger auf den entsprechenden Code setzen
			;  (Ziffer als OFFSET zur Basisadresse 'segmentabc'!)
	mov  a, M	;  Ziffern-Code der Hunderter-Stelle
	sta  segment5   ;  ins 5.Segment speichern
	;--- Zehner-Stelle ---
        mov a, e	;Zehner- und Einer-Stelle in den Akku laden
	ani 0F0h	;  Zehner-Stelle maskieren
	rrc		;  und ins untere Nibble rotieren
	rrc             ;
	rrc             ;
	rrc             ;
	mov l, a	;HL-Zeiger auf den entsprechenden Code setzen
	mov a, M	;Ziffern-Code der Zehner-Stelle
	sta segment6    ;  ins 6.Segment speichern
	;--- Einer-Stelle ---
	mov  a,e        ;Zehner- und Einer-Stelle in den Akku laden
	ani  0Fh	;  Einer-Stelle maskieren
	mov  l,a	;HL-Zeiger auf den entsprechenden Code setzen
	mov  a, M	;Ziffern-Code der Einer-Stelle
	sta  segment7   ;  ins 7.Segment speichern	
	jmp  display_ausgabe

zwei_komma_eins:
	;--- Zehner-Stelle ---
        mov a, e	;Zehner- und Einer-Stelle in den Akku laden
	ani 0F0h	;  Zehner-Stelle maskieren
	rrc		;  und ins untere Nibble rotieren
	rrc             ;
	rrc             ;
	rrc             ;
	mov l, a	;HL-Zeiger auf den entsprechenden Code setzen
	mov a, M	;Ziffern-Code der Zehner-Stelle
	sta segment5    ;  ins 5.Segment speichern
	;--- Einer-Stelle ---
	mov  a,e        ;Zehner- und Einer-Stelle in den Akku laden
	ani  0Fh	;  Einer-Stelle maskieren
	mov  l,a	;HL-Zeiger auf den entsprechenden Code setzen
	mov  a, M	;Ziffern-Code der Einer-Stelle
	adi  80h	;Dezimalpunkt setzen!!!
	sta  segment6   ;  ins 6.Segment speichern	
	;--- Nachkomma-Stelle ---           	
	lda  nachkomma  ;Nachkommastelle in den Akku laden
	mov  l,a	;HL-Zeiger auf den entsprechenden
	mov  a, M	;  Ziffern-Code der Nachkomma-Stelle setzen
	sta  segment7	;  und Ziffern-Code im 7.Segment speichern
	jmp  display_ausgabe

eins_komma_zwei:

	;*** Textausgabe auf dem Display ***
display_ausgabe:
	lxi  b, segment1;	
	call text8      ;Me·wert mit Einheit im Display anzeigen
ret	;RÅcksprung aus dem 'anzeige'

;* Datenbereich zur Display-Ausgabe *
segment1 db 0	;Hunderter
segment2 db 0   ;Zehner
segment3 db 0   ;Einer
segment4 db 48h ;=
segment5 db 0   ;
segment6 db 0   ;
segment7 db 0	;
segment8 db 3Eh ;U fÅr V(olt)
;****************************************************************************
