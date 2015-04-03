%nosyms
; 'hexdump.asm'
; Ausdrucken eines Speicherbereichs als Hex-Dump
; Druckersteuerung Åber den 8255 im Modus 0

;*** Namen der relevanten Sp.adr. zur parallelen Schnittstelle ***
	basisadr2   EQU 20h	  ;(00h=8255/1, 10h=8255/2, 20h=8255/3)

	;Ab der Ver 2.53 des 8080sim wird die Adresse 20h auf LPTx
	;abgebildet (entsprechende Einstellung in der 'com.dat')!

	datenreg    EQU basisadr2 +0 ;Datenregister
	statusreg   EQU basisadr2 +1 ;Statusregister
	kontrollreg EQU basisadr2 +2 ;Kontrollregister
	modusreg    EQU basisadr2 +3 ;Konfigurationsregister/
            		             ;Steuer-wort-register
        LF	    EQU 0Ah
	CR	    EQU 0Dh
	SPACE	    EQU 20h	

	ORG 8000h
	jmp init

INCLUDE tools.inc

	ORG 8010h
INCLUDE prn_char.inc

	ORG 8050h
INCLUDE prn_akku.inc


;---------------------------------------------------------------------------
MACRO   prn_5_space
	mvi  b,05h	;5 StÅck
  prn_space:	
	mvi  a, space   ;  Leerzeichen
	push b		;
	call print_char ;  drucken
	pop  b		;
	dcr  b		;
	jnz  prn_space  ;
ENDM
;---------------------------------------------------------------------------

;---------------------------------------------------------------------------
;*** UP 'ascii_spalte' ***
ascii_spalte:
	prn_5_space	;MACRO zum Drucken von 5 Leerzeichen
	sub a	;SpaltenzÑhler auf Null setzen
	sta  spalten	;
	shld nextadr	;Adr. d. als nÑchstes zu druck. Adr. sichern
	lhld firstadr	;HL-Zeiger auf die zuerst gedruckte Adr. d. Zeile
next_ascii:	
	mov  a,m        ;

	cpi  first_ascii	;fÅr alle ASCII-Zeichen, die vor 20h=SPACE sind,
	jc   prn_punkt  	;  einen '.' drucken!
	cpi  last_ascii+1 	;fÅr alle ASCII-Zeichen, die nach 5Fh sind,
	push psw
	cc   print_char   	;  einen '.' drucken! - SONST: Zeichen normal drucken
	pop  psw
	jc   kein_punkt
prn_punkt:
	mvi  a,'.'
	call print_char
kein_punkt:
	inx  h		;Datenzeiger auf das nÑchste Element setzen
	
        lda  spalten	;
	inr  a		;
	sta  spalten    ;
	cpi  16         ;
	jnz  next_ascii ;
	lhld nextadr	;Adr. d. nÑchsten zu druckenden Adr. ins HL-Reg.
ret	;RÅcksprung aus UP 'ascii_spalte'		
;---------------------------------------------------------------------------

;{ MAIN }
;Registerbelegungen des Hauptprogramms 'hexdump.asm':
;	HL = Anfangsadresse des zu druckenden Speicherbereichs
;	DE = Endadresse	    " ...
;	BC = Zeiger auf den Text, der Åber das Monitor-UP 'text8',
;		im Display ausgegeben werden soll
;	->Nur das Rp. darf verÑndert werden, da es nur vorÅbergehend
;	  als Zeiger benutzt wird!!!

	ORG 8100h

spalten db 00h		;ZÑhlvariable fÅr die gedruckten Spalten pro Zeile
firstadr  dw 0000h	;Sp.adr. der zuerst  gedruckten Adr. einer Zeile
nextadr	  dw 0000h	;Sp.adr. der als nÑchstes zu druckenden Adr.
			;=1.Adr. d. nÑchsten Zeile
first_ascii = SPACE
 last_ascii = 7Ah	;'z'

init:
	lxi sp,087B1h
	mvi a,82h	;Modus 0 d. 8255:
	out modusreg	;         A E AA
input:
	;** Eingabe der AnfangAdresse **
	lhld AA		;"AA" erscheint in den beiden ersten
			;	Display-Stellen bei UP "hexin"!
	call hexin	;Eingabe einer 4stelligen Hex-Zahl Åber die Tastatur
	push h		;  und auf dem Stack sichern
	;** Eingabe der EndAdresse **
	lhld EA		;"EA" erscheint in den beiden ersten
			;	Display-Stellen bei UP "hexin"!
	call hexin	;Eingabe einer 4stelligen Hex-Zahl Åber die Tastatur
	xchg		;  und im Rp. DE sichern
	pop h		;Anfangsadresse wieder ins Rp. HL laden
	
	lxi  b,printing ;'PrintinG' im Display
	call text8      ;	ausgeben
neue_zeile:
	shld firstadr	;die zuerst zu druckende Adr. einer Zeile sichern
			;  (-> fÅr ASCII-Spalte drucken)
	sub a		;Zahl der gedruckten Spalten (=Sp.adr.)
	sta  spalten	;  auf Null setzen
	mvi  a,lf
	call print_char
	mvi  a,cr
	call print_char
	;*** Zeilenanfang: erste Adresse drucken ***
	mov  a,h
	call print_akku
	mov  a,l
	call print_akku

	mvi  a,':'
	call print_char
	mvi  a,space
	call print_char
	;*** Inhalt einer Sp.adr. drucken ***
weiter_in_zeile:
	mov  a,m
	call print_akku

	call subhd	;wenn (HL)=(DE)=>Z=1
	push psw
	cz   ascii_spalte
			;auch noch fÅr die letzte evtl. angebrochende Zeile
			;  die ASCII-Spalte drucken
	pop  psw
	jz   ende	;ja:    Ende des Ausdrucks!
	inx  h		;nein:  Datenzeiger auf das nÑchste Zeichen setzen		

	lda  spalten
	inr  a		;Zahl der gedruckten Spalten um 1 erhîhen
	sta  spalten
	cpi  16			;Sind schon 16 Spalten gedruckt?
	cz   ascii_spalte	;   ja: "ASCII-Spalte" drucken! am Zeilenende
	mvi  a,space        	;sonst: Space
	call print_char		;       drucken
        jmp  weiter_in_zeile    ;	und in derselben Zeile weiterdrucken


ende:
	mvi  a,lf
	call print_char
	mvi  a,cr
	call print_char
	lxi  b,prnready
	call text8
	hlt

         ORG 8200h
AA	 db 77h,77h
EA       db 79h,77h
prnerror db 73h,50h,54h,79h,50h,50h,5ch,50h
printing db 73h,50h,04h,54h,78h,04h,54h,3dh
prnready db 73h,50h,54h,50h,79h,77h,5eh,6eh
         END