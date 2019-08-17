; Megan Walsh	meganew2
;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; Prints the histogram generated from the code above to the screen.
; The number of characters counted will be displayed as hexadecimal values, 
; beginning with the number of non-alphabetic characters (represented by the
; @ symbol) and thereafter the counts of alphabetic characters. 

; Register Table
; R1 is printed counter
; R2 is bit counter
; R3 holds value to be printed
; R5 holds value to be added for a digit
; R6 holds value to be added for a letter
; R4 is used to check if R0 is a letter or a number
; R0 is used for printing


; initiliaze registers
 AND R3,R3,#0		; clear R3
 AND R0,R0,#0		; clear R0
 AND R2,R2,#0		; clear R2

 LD R2,COUNT		; initiliaze counter

 AND R5,R5,#0		; clear R5
 AND R6,R6,#0		; clear R6
 LD R5, DIGIT		
 LD R6, LETTER
 LD R1, HIST_ADDR	; load R3 with first histogram location

 LD R4,STARTT		; load with first character
 
; beginning of outer loop
 OUTLOOP  
 AND R0,R0,#0		; clear R0
 ADD R0,R0,R4
 OUT
 ADD R4,R4,#1		; increment R4
 LD R0,SPACE 		; load with space
 OUT
 
; store registers that will be changed
 ST R4, STORER4		; save R4
 ST R1, STORER1		; save R1
 ST R2, STORER2		; save R2
 
 LDR R3,R1,#0		; load R3 with value
 AND R1,R1,x0		; clear R1
 ADD R1,R1,#4		; set printed counter

; beginning of inner loop
 LOOP 
 AND R2,R2,x0		; clear R2
 AND R0,R0,x0		; clear R0
 AND R4,R4,x0		; clear R4
 ADD R2,R2,#4		; set bit counter
 
 START 
 ADD R0,R0,R0		; shift digit left

 ADD R3,R3,#0	
 BRzp ZERO		; check if 1 or 0
 ADD R0,R0,#1		; add 1 to digit

 ZERO ADD R3,R3,R3	; shift R3 left
 ADD R2,R2,#-1		; decrement bit counter
 BRnp START

 ADD R4,R4,R0;
 ADD R4,R4,#-9		; check if less than or = to 9
 BRp LET		; check if letter
 ADD R0,R0,R5 ;
 OUT 

 ADD R1,R1,#-1
 BRnp LOOP		; check if done
 
; restore registers used earlier
 LD R4,STORER4		; restore R4
 LD R2,STORER2		; restore R2
 LD R1,STORER1		; restore R1
 
 ADD R2,R2,#-1		; decrement R2
 BRz DONE

 ADD R1,R1,#1		; increment R1
 LD R0,NWLN		; print new line
 OUT
 BRnzp OUTLOOP

 LET 
 ADD R0,R0,R6;
 ADD R0,R0,#-10
 OUT
 ADD R1,R1,#-1
 BRnp LOOP		; check if done

 LD R4,STORER4		; restore R4
 LD R2,STORER2		; restore R2
 LD R1,STORER1		; restore R1
 
 ADD R2,R2,#-1		; decrement R2
 BRz DONE

 ADD R1,R1,#1		; increment R1
 LD R0,NWLN		; print new line
 OUT
 BRnzp OUTLOOP

 DONE 
 HALT; stop the computer


DIGIT 		.FILL x30		
LETTER 		.FILL x41
STARTT		.FILL x40
SPACE		.FILL x20
NWLN		.FILL xA
COUNT		.FILL x1B
STORER4		.BLKW 1
STORER1		.BLKW 1
STORER2		.BLKW 1

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START		.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
