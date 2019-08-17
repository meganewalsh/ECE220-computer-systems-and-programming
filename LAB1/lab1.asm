 ; Lab 1 
 ; assignment: develop a code to print a value stored in a register 
 ;             as a hexadecimal number to the monitor
 ; algorithm: turnin each group of four bits into a digit
 ;            calculate the corresponding ASCII character;
 ;            print the character to the monitor

.ORIG x3000

	AND R1, R1, #0		; init digit counter
	ADD R1, R1, #4		; set digit counter to 4
	LD R5, DIG
	LD R6, LET	

PRINT4D	AND R2, R2, #0		; init bit counter
	ADD R2, R2, #4		; set bit counter to 4
	AND R1, R1, #0		; reinit digit counter
	AND R0, R0, #0		; resetting trap OUT

SHIFTD	ADD R0, R0, R0		; shift digit left

	ADD R3, R3, #0
	BRzp ADD0
	ADD R0, R0, #1		; add 1 to digit

ADD0	ADD R3, R3, R3		; shift digit left
	ADD R2, R2, #-1		; decrement bit counter
	BRnp SHIFTD

	ADD R4, R4, #0
	ADD R4, R4, #-9		; check <= 9
	BRp CHECK9

	ADD R0, R0, R5		; add '0'
	OUT	
	ADD R1, R1, #-1		; decrement digit counter
	BRnp PRINT4D
	BRnzp DONE
	
CHECK9	ADD R0, R0, R6		; add 'A'-10
	ADD R0, R0, #-10	
	OUT
	ADD R1, R1, #-1		; decrement digit counter
	BRnp PRINT4D

DONE	HALT			; stops the computer

	DIG .FILL x30
	LET .FILL x31
.END
