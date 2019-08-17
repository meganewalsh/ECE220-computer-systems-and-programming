; Implement a program to find the nearest smaller (or equal) perfect square of a given positive number
; The input will be stored in R2 and output (the nearest perfect square) should be stored in R3
; TODO: Write a subroutine called "PSquare" which returns the nearest perfect square of a given input and 
;       you must invoke this subroutine in the main part.
; Note : R2, R4, R5 and R6 must be left unchanged in PSquare.
;
; 
; PSquare :  input is stored in R2
;            output is stored in R3

.ORIG	x3000
	AND R2, R2, #0
	LD R2, NUM
	JSR Psquare
	HALT

Psquare
	ST R7, SAVE_R7
	AND R0, R0, #0
    	AND R1, R1, #0
    	AND R3, R3, #0

ADD_ONE ADD R1, R1, #1
 	ADD R3, R1, #0   ;  R3 is a counter that contains the same number as R1
	AND R0, R0, #0
    	JSR SQUARE
    	ADD R0, R0, #0
    	NOT R0, R0
    	ADD R0, R0, #1
    	ADD R0, R2, R0
    	BRzp ADD_ONE
    	BRnzp LOOP       ;  R1 contains the number (n) 

SQUARE 	ADD R0, R0, R1   ;  R0 contains the sum to be added to
    	ADD R3, R3, #-1  ;  decrement counter
    	BRp SQUARE
    	RET		 ;  once counter is = 0, return with answer in R0
 
LOOP   	ADD R1, R1, #-1  ;  R1 now contains (n-1)
 	ADD R3, R1, #0   ;  R3 is a counter that contains the same number as R1
	AND R0, R0, #0
    	JSR SQUARE
    	ADD R3, R0, #0   ; answer is transferred to R3
	LD R7, SAVE_R7
    	RET

NUM 	.FILL x40
SAVE_R7 .BLKW #1
.END
