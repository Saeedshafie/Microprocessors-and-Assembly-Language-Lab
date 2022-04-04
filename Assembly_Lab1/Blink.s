PIO_PER  EQU 0x400E0E00
PIO_OER  EQU 0x400E0E10
PIO_SODR EQU 0x400E0E30
PIO_CODR EQU 0x400E0E34
PIO_ISR  EQU  0x400E0E4C

	
DELAY    EQU 0x0020000
	
	area myCode, code, readonly
	export __main
	entry
	
__main
	BL enable_pio
	
	BL led1_on
	BL led2_on
	BL led3_on
LOOP
	
	ldr r1, =PIO_ISR
	ldr r2, [r1]
	cmp r2, #2_1000000
	BEQ ELSE
		
	; 0
	BL delay
	BL led1_on
	BL led2_on
	BL led3_on
	
	; 1
	BL delay
	BL led1_off

	; 2
	BL delay
	BL led1_off
	BL led2_off
	
	; 3
	BL delay
	BL led1_on
	
	; 4
	BL delay
	BL led1_off
	BL led2_on
	BL led3_off
	
	; 5
	BL delay	
	BL led1_on
	
	; 6
	BL delay
	BL led1_off
	BL led2_off
	
	; 7
	BL delay
	BL led1_on
	B END_CONDITION
	
ELSE
	BL led1_off
	BL led2_off
	BL led3_off
	
END_CONDITION
	B LOOP
		
enable_pio
	MOV r4, #2_111
	
	LDR r5, =PIO_PER
	STR r4, [r5]
	
	LDR r5, =PIO_OER
	STR r4, [r5]
	
	BX lr
	
led1_on
	MOV r4, #2_001
	
	LDR r5, =PIO_SODR
	STR r4, [r5]
		
	BX lr

led2_on
	MOV r4, #2_010
	
	LDR r5, =PIO_SODR
	STR r4, [r5]
		
	BX lr
	
led3_on
	MOV r4, #2_100
	
	LDR r5, =PIO_SODR
	STR r4, [r5]
		
	BX lr

led1_off
	MOV r4, #2_001
	
	LDR r5, =PIO_CODR
	STR r4, [r5]
		
	BX lr
	
led2_off
	MOV r4, #2_010
	
	LDR r5, =PIO_CODR
	STR r4, [r5]
		
	BX lr
	
led3_off
	MOV r4, #2_100
	
	LDR r5, =PIO_CODR
	STR r4, [r5]
		
	BX lr
	
delay
	MOV r4, #0
	LDR r5, =DELAY
	
delay_loop
	ADD r4, r4, #1
	
	CMP r4, r5
	BNE delay_loop
	
	BX lr
	
	END