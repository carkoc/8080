;-----------------------------------------------------------------------------
;                        I N C l u d e - Datei
;                       ***  'display.inc'  ***
;			  V 1.1   19.12.92 CK
;-----------------------------------------------------------------------------
;Inhalt:  	
;	Unterprogramm (UP) "display" (=Aufrufname) zur Ansteuerung
;	der Display-Anzeige des Profi5-4K-Computer (=>F8-Optionen!)
;	unter Verwendung des Monitor-UP "decod" - mit Sicherung
;	des Flagregisters und aller anderen Register !
;    			  	&
;       Benennung der relevanten Speicheradressen fÅr die Aufrufwerte!
;-----------------------------------------------------------------------------
;Aufrufwerte:
;	Die anzuzeigenden Werte mÅssen sich vor Aufruf des UP "anzeige"
;	in den entsprechenden Speicheradressen befinden, die die
;	Bezeichnungen "disp1", "disp2", "disp3" und "disp4" tragen.
;
;	Es kînnen einzelne 7-Segment-Anzeigen auch "dunkel" gesteuert werden,
;       indem die entsprechende Bitkombination (von links nach rechts:
;       0=aus, 1=an) in der Speicheradresse mit dem Namen "dunkel" (!)
;	abgespeichert wird.
;============================================================================

;       *** verwendete Speicheradressen ***
dunkel  equ 083d9h     ;Speicheradresse fÅr die Display-Maske
disp1   equ 083f4h     ;Speicheradr. fÅr Disp.-Stellen Nr.1 & 2 (von links
disp2   equ 083f5h     ;Speicheradr. fÅr Disp.-Stellen Nr.3 & 4  ...
disp3   equ 083f6h     ;Speicheradr. fÅr Disp.-Stellen Nr.5 & 6  ...
disp4   equ 083f7h     ;Speicheradr. fÅr Disp.-Stellen Nr.7 & 8  nach rechts)

;       *** UP "display" ***
display:
	push psw        ;Flag-Reg.,
	push b          ;  BC-Reg.,
	push d          ;  DE-Reg. und
	push h          ;  HL-Reg. auf dem Stack sichern
	call decod      ; Aufruf des Monitor-UP "decod"
	pop h		;  HL-Reg.,
	pop d		;  DE-Reg.,
	pop b           ;  BC-Reg. und
	pop psw         ;Flag-Reg. vom Stack holen (LIFO-Prinzip
			;			    =Last In First Out!!!)
ret                     ;ENDE des UP "display"
;---------------------------------------------------------------------------
