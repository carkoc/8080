%nosyms
; 'hardint2.asm'
; Aufgabe:
; Schreibe ein Programm, das bei jedem Hardware-Interrupt RST 5.5
; einen von 3 Prozessen aufruft, und zwar beim 1. Interrupt Proze· 1,
; beim 2. Interrupt Proze· 2, beim 3. Interrupt Proze· 3 und beim
; 4. Interrupt wieder von vorne mit dem Aufruf von Proze· 1 beginnt.

ORG 8000h
jmp init

;INCLUDE display.inc

p1	db 73h,50h,5ch,5bh,79h,6dh,6dh,06h
prozess1:
	lxi  b, p1
	call text8
;	mvi  a, 1
;       sta  disp1
:	call decod
ret

p2	db 73h,50h,5ch,5bh,79h,6dh,6dh,5bh
prozess2:
	lxi  b, p2
	call text8
;	mvi  a, 2
;	sta  disp1
;	call decod
ret

p3	db 73h,50h,5ch,5bh,79h,6dh,6dh,4fh
prozess3:
	lxi  b, p3
	call text8
;	mvi  a, 3
;	sta  disp1
;	call decod
ret

; Proze·merker 'pm'
pm db 0

;*** Voreinstellungen ***
init:
	lxi sp, 083c1h

;	mvi a, 01000000b
;	sta dunkel

	mvi a, 00001110b
	sim
	ei

	mvi a, 0
	sta pm

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