%nosyms
; 'hardint1.asm'
; Aufgabe:
; Schreibe ein Programm, das bei jedem Hardware-Interrupt RST 5.5
; einen von 3 Prozessen aufruft, und zwar beim 1. Interrupt Proze· 1,
; beim 2. Interrupt Proze· 2, beim 3. Interrupt Proze· 3 und beim
; 4. Interrupt wieder von vorne mit dem Aufruf von Proze· 1 beginnt.

ORG 8000h
jmp init

;       *** verwendete Speicheradressen ***
dunkel  equ 083d9h     ;Speicheradresse fÅr die Display-Maske
disp1   equ 083f4h     ;Speicheradr. fÅr Disp.-Stellen Nr.1 & 2 (von links

pm	db  0		;'Proze·merker'

prozess1:
 	mvi  a, 1
        sta  disp1
	call decod
ret

prozess2:
	mvi  a, 2
	sta  disp1
	call decod
ret

prozess3:
	mvi  a, 3
	sta  disp1
	call decod
ret



;*** Voreinstellungen ***
init:
	lxi sp, 083c1h

	mvi a, 01000000b
	sta dunkel

	mvi a, 0
	sta pm

	mvi a, 00001110b
	sim
	ei

	jmp start


; *** MAIN ***
start:
	nop
	nop
	nop
jmp start

; *** IRQ 5.5 - UnterProgramm ***
ORG 8100h

	di
	lda pm
	inr a
	sta pm
	cpi 4
	jnz weiter
	mvi a, 1
	sta pm
weiter:
	lda pm
	cpi 1
	cz  prozess1
	
	lda pm
	cpi 2
	cz  prozess2
	
	lda pm
	cpi 3
	cz  prozess3

	ei
ret	;RÅcksprung aus dem IRQ 5.5-UP

