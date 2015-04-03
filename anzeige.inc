;****************************************************************************
; 		 * INCLUDE-Datei 'anzeige.inc' *
;		 ***  UP Nr.2 - Aufrufname: "anzeige"  ***
;****************************************************************************



anzeige:
	in   statusreg	;Druckerstatus zur Auswertung in den Akku laden
	rrc		;3.Bit
	rrc		;  (ERROR-Bit - low-active!)
	rrc		;  des Statusregisters
	rrc		;  ins Carry-Flag rotieren
	jnc  fehler_aus	;falls ERROR-Bit gesetzt (low-active):
			;   =>  Ausgabe einer Fehlermeldung vorbereiten
	mvi  a, 80h	;Code fr den DezimalPunkt
	sta  segment1	;
	sta  segment2	;
        jmp  weiter1    ;	... und 'weiter1'... zur Display-Ausgabe!

   fehler_aus:
	lxi  b, prnerror; 'PrnError' auf dem Display
	call text8	;    ausgeben
	mvi  a, 3	;3/10 s lang
	call zsecd	;  verz”gern
        mvi  a, 5eh	;"d" fr Drucker
	sta  segment1	;  in Sp.adr. fr das 1.Segment speichern
	mvi  a, 71h	;"F" fr Fehler
	sta  segment2	;  in Sp.adr. fr das 2.Segment speichern
	
weiter1:
;	* Meáwert in 7-Segment-Code umwandeln *
	lxi  h, segmentabc
	lda hunderter	;Hunderter-Stelle in den Akku laden
	mov  l, a	;  HL-Zeiger auf entsprechenden 7-Segment-ABC-Code
			;  der Ziffer setzen
	mov  a, M	;  Ziffern-Code der Hunderter-Stelle
	sta  segment4   ;  ins 4.Segment speichern
	lda  zehner	;Zehner- und Einer-Stelle in den Akku laden
	mov l, a	;  HL-Zeiger auf entsprechenden 7-Segment-ABC-Code
			;  der Ziffer setzen
	mov  a, M	;  Ziffern-Code der Zehner-Stelle
	sta  segment5   ;  ins 5.Segment speichern
	lda  einer	;Zehner- und Einer-Stelle in den Akku laden	
	mov  l, a	;  HL-Zeiger auf entsprechenden 7-Segment-ABC-Code
			;  der Ziffer setzen
	mov  a, M	;  Ziffern-Code der Einer-Stelle
	adi  80h	;    + DezimalPunkt hinzufgen (als Trennung zur Einheit)
	sta  segment6   ;  ins 6.Segment speichern	

	lxi  b, segment1;	
	call text8      ;Meáwert mit Einheit und evtl. "DF"
			;  im Display anzeigen
ret	;Rcksprung aus dem UP Nr.2 'anzeige'

;* Datenbereich zur Display-Ausgabe *
segment1 db 0	;reserviert zur Anzeige von "dF" (=DruckerFehler),
segment2 db 0   ;  falls der Drucker nicht druckbereit
segment3 db 0   ;--unbenutzt--
segment4 db 0   ;reserviert fr die Hunderter-Stelle,
segment5 db 0   ;    "      fr die Zehner-Stelle,
segment6 db 0   ;    "      fr die Einer-Stelle  des Meáwertes
segment7 db 76h	;"H"
segment8 db 5bh ;"2" - steht fr "Z"/"z"

prnerror db 73h,50h,54h,79h,50h,50h,5ch,50h
;****************************************************************************