;----------------------------------------------------------------------------
datum:
	lxi  b,db_Anweisung
	call print_mnemonic
	dcx  h
	call Plus_1_Byte
	jmp  next
;----------------------------------------------------------------------------
;============================================================================
mnemonic00 db 'NOP',0
mnemonic01 db 'LXI  B,',0
mnemonic02 db 'STAX B,',0
mnemonic03 db 'INX  B',0
mnemonic04 db 'INR  B',0
mnemonic05 db 'DCR  B',0
mnemonic06 db 'MVI  B,',0
mnemonic07 db 'RLC',0
mnemonic09 db 'DAD  B,',0
mnemonic0A db 'LDAX B,',0
mnemonic0B db 'DCX  B',0
mnemonic0C db 'INR  C',0
mnemonic0D db 'DCR  C',0
mnemonic0E db 'MVI  C,',0
mnemonic0F db 'RRC',0

mnemonic11 db 'LXI  D,',0
mnemonic12 db 'STAX D;',0
mnemonic13 db 'INX  D',0
mnemonic14 db 'INR  D',0
mnemonic15 db 'DCR  D',0
mnemonic16 db 'MVI  D,',0
mnemonic17 db 'RAL',0
mnemonic19 db 'DAD  D,',0
mnemonic1A db 'LDAX D,',0
mnemonic1B db 'DCX  D,',0
mnemonic1C db 'INR  E',0
mnemonic1D db 'DCR  E',0
mnemonic1E db 'MVI  E,',0
mnemonic1F db 'RAR',0

mnemonic20 db 'RIM',0
mnemonic21 db 'LXI  H,',0
mnemonic22 db 'SHLD ',0
mnemonic23 db 'INX  H',0
mnemonic24 db 'INR  H',0
mnemonic25 db 'DCR  H',0
mnemonic26 db 'MVI  H,',0
mnemonic27 db 'DAA',0
mnemonic29 db 'DAD  H',0
mnemonic2A db 'LHLD ',0
mnemonic2B db 'DCX  H',0
mnemonic2C db 'INR  L',0
mnemonic2D db 'DCR  L',0
mnemonic2E db 'MVI  L,',0
mnemonic2F db 'CMA',0

mnemonic30 db 'SIM',0
mnemonic31 db 'LXI  SP,',0
mnemonic32 db 'STA  ',0
mnemonic33 db 'INX  SP',0
mnemonic34 db 'INR  M',0
mnemonic35 db 'DCR  M',0
mnemonic36 db 'MVI  M,',0
mnemonic37 db 'STC',0
mnemonic39 db 'DAD  SP',0
mnemonic3A db 'LDA  ',0

db_Anweisung   db 'DB ',0

;============================================================================
