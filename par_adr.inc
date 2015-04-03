;---------------------------------------------------------------------------
;*****************      INClude-File 'par_adr.inc'    **********************
;                       CK 12/92
;___________________________________________________________________________
;*** Namen der relevanten Sp.adr. zur parallelen Schnittstelle ***
	basisadr2   EQU 20h       ;(00h=8255/1, 10h=8255/2, 20h=8255/3)

	;Ab der Ver 2.53 des 8080sim wird die Adresse 20h auf LPTx
	;abgebildet (entsprechende Einstellung in der 'com.dat')!

	datenreg    EQU basisadr2 +0 ;Datenregister
	statusreg   EQU basisadr2 +1 ;Statusregister
	kontrollreg EQU basisadr2 +2 ;Kontrollregister
	modusreg    EQU basisadr2 +3 ;Modus-/Steuerwort-register

	LF      EQU 0Ah
	CR      EQU 0Dh
	SPACE   EQU 20h
;---------------------------------------------------------------------------
