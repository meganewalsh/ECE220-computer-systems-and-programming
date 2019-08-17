;
;
;
.ORIG x3000
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
;your code goes here
		AND R0, R0, #0		; initialize all registers
		AND R1, R1, #0
		AND R2, R2, #0
		AND R3, R3, #0
		AND R4, R4, #0
		AND R5, R5, #0
		AND R6, R6, #0
		AND R7, R7, #0

READCHAR       	GETC			; read character from input
               	OUT

CHECKSPACE	LD    R2, SPACE           ; check for a space
                NOT   R2, R2
		ADD   R2, R2, #1
                ADD   R3, R0, R2
                BRz   READCHAR    	       ; if space go to next value

CHECKEND    	LD    R2, SEMICOLON		; check for a semicolon.
            	NOT   R2, R2
		ADD   R2, R2, #1
            	ADD   R3, R0, R2
            	BRnp  CHECKPLUS			; no semicolon --> check plus.
		JSR   POP
		ADD   R5, R5, #0
		BRp   INVALID_CHAR		; check underflow
		ADD   R3, R0, #0
            	JSR   PRINT_HEX       		; if semicolon, print answer.  
            	BRnzp FINISH

CHECKPLUS   	LD    R2,PLUS_SIGN		; check for plus sign
            	NOT   R2,R2
	    	ADD   R2, R2, #1
            	ADD   R3,R0,R2
            	BRnp  CHECKMINUS		; no plus --> check minus.
            	JSR   PLUS
            	BRnzp READCHAR

CHECKMINUS  	LD    R2,MINUS_SIGN		; check for minus sign
          	NOT   R2,R2
		ADD   R2, R2, #1
           	ADD   R3,R0,R2
            	BRnp  CHECKMULT			; no minus --> check for mult.
            	JSR   MINUS
            	BRnzp READCHAR

CHECKMULT   	LD    R2,MULT_SIGN		; check for mult sign
            	NOT   R2,R2
	    	ADD   R2, R2, #1
            	ADD   R3,R0,R2
            	BRnp  CHECKEXP			; no mult --> check for expo
            	JSR   MULT
            	BRnzp READCHAR

CHECKEXP   	LD    R2, EXP_SIGN		; check for exponent
            	NOT   R2, R2
	    	ADD   R2, R2, #1
            	ADD   R3, R0, R2
            	BRnp  CHECKDIV			; no expo --> check for division
            	JSR   EXPO			; if expo, jump to expo sub
            	BRnzp READCHAR

CHECKDIV   	LD    R2, DIV_SIGN		; check for division sign
            	NOT   R2, R2
	    	ADD   R2, R2, #1
            	ADD   R3, R0, R2
            	BRnp  CHECK_NUM			; at this point, input is not an
            	JSR   DIVI			; operator. Check for number instead
            	BRnzp READCHAR

CHECK_NUM   	LD   R2, NUM_ZERO
            	NOT  R2, R2
		ADD  R2, R2, #1
            	ADD  R3, R0, R2
            	BRn  INVALID_CHAR   	; if character is less than 0, invalid
            	LD   R2, NUM_DIGITS	; if character is >9, invalid
            	NOT  R2, R2
		ADD  R2, R2, #1
            	ADD  R3, R3, R2
            	BRp  INVALID_CHAR
		LD   R2, NUM_ZERO
		NOT  R2, R2
		ADD  R2, R2, #1
		ADD  R0, R0, R2 
            	JSR  PUSH		; push new value onto stack
            	BRnzp READCHAR

INVALID_CHAR  	LEA R0,INV_CHAR		; prints 'invalid expression'
            	PUTS

FINISH      	HALT

PLUS_SIGN 	.FILL x002B
DIV_SIGN	.FILL x002F
EXP_SIGN	.FILL x005E
MINUS_SIGN	.FILL x002D
MULT_SIGN	.FILL x002A

SEMICOLON	.FILL x003B

SPACE		.FILL x0020
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

		LD  R0, PRINTx		; print hex (x)
		OUT
		AND R1,R1,x0		; clear R1

 		AND R5,R5,#0		; clear R5
 		AND R6,R6,#0		; clear R6
 		LD R5, DIGIT		; load x30	
 		LD R6, LETTER		; load x41 = A

 		ADD R1,R1,#4		; set printed counter

 	LOOP5 	AND R2,R2, #0		; clear R2
 		AND R0,R0, #0		; clear R0
 		AND R4,R4, #0		; clear R4
 		ADD R2,R2, #4		; set bit counter
 
 	START 	ADD R0,R0,R0		; shift digit left

 		ADD R3,R3,#0	
 		BRzp ZERO		; check if 1 or 0
 		ADD R0,R0,#1		; add 1 to digit

 	ZERO 	ADD R3,R3,R3 		; shift R3 left
 		ADD R2,R2,#-1		; decrement bit counter
 		BRnp START

 		ADD R4,R4,R0;
 		ADD R4,R4,#-9		; check if less than or = to 9
 		BRp LET			; check if letter
 		ADD R0,R0,R5 ;
 		OUT 

 		ADD R1,R1,#-1
 		BRnp LOOP5		; check if done
 		HALT

 	LET 	ADD R0,R0,R6
 		ADD R0,R0,#-10
 		OUT
 		ADD R1,R1,#-1
 		BRnp LOOP5		; check if done
		HALT

	DIGIT 		.FILL x30		
	LETTER	 	.FILL x41
	STORAGE1	.BLKW 1
	PRINTx		.FILL x78

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
		ADD R1, R7, #0
		AND R3, R3, #0
		AND R4, R4, #0
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR		; check underflow
		ADD R3, R0, #0
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR		; check underflow
		ADD R4, R0, #0

		ADD R0, R3, R4			; adds inputs
		JSR PUSH
		ADD R7, R1, #0
		RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MINUS	
;your code goes here
		ADD R1, R7, #0
		AND R3, R3, #0
		AND R4, R4, #0
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR		; check underflow
		ADD R3, R0, #0
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR		; check underflow
		ADD R4, R0, #0	
		NOT R3, R3
		ADD R3, R3, #1
		ADD R0, R3, R4
		JSR PUSH
		ADD R7, R1, #0
		RET
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MULT	
;your code goes here
		ADD R1, R7, #0
		AND R3, R3, #0
		AND R4, R4, #0
		AND R0, R0, #0
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR		; check underflow
		ADD R3, R0, #0			; R4 = operand
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR		; check underflow
		ADD R4, R0, #0
		AND R0, R0, #0			; R3 = operand`
		ADD R3, R3, #0
		BRz RET2
LOOP_MULT	ADD R0, R0, R4
		ADD R3, R3, #-1
		BRp LOOP_MULT
RET2		JSR PUSH
		ADD R7, R1, #0
		RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

DIVI	
;your code goes here
		
		ADD R1, R7, #0
		AND R3, R3, #0
		AND R4, R4, #0
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR	; check underflow
		ADD R4, R0, R4		; R4 = operand
		BRz DIV_ZERO	
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR	; check underflow
		ADD R3, R0, R3		; R3 = operand

		AND R0, R0, #0		; initialize counter
		ADD R0, R0, #-1
		NOT R4, R4		; performs R3 / R4	
		ADD R4, R4, #1
LOOP_DIV	ADD R0, R0, #1
		ADD R3, R3, R4
		BRzp LOOP_DIV
		JSR PUSH
		BRnzp FINISH3

DIV_ZERO  	LEA R0,INV_CHAR
            	PUTS
		HALT
FINISH3		ADD R7, R1, #0
		RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXPO
;your code goes here

		; initialize variables
		ADD R1, R7, #0
		AND R3, R3, #0		; 4^3
		ADD R3, R3, #-1
		AND R4, R4, #0
		AND R6, R6, #0
		AND R2, R2, #0	

		; pop values from stack
		JSR POP
		ADD R5, R5, #0
		BRp INVALID_CHAR	; check underflow
		ADD R4, R0, #0		; R4 = exp
		ADD R6, R4, #0		; R6 = counter
		JSR POP			; R0 = final value
		ADD R5, R5, #0
		BRp INVALID_CHAR	; check underflow
		ADD R3, R0, #0		; R3 = value
		ADD R2, R3, #0		; R2 = copy of value
					;    = exp counter
		ADD R0, R2, #0
      LOOP_EXP	ADD R0, R2, #0
		ADD R6, R6, #-1
		BRp LOOP_EXP
		ADD R6, R4, #0		; resetting counter to exp value
		ADD R2, R0, #0		; change value in R2
		AND R0, R0, #0
		BRp LOOP_EXP
		JSR PUSH
		ADD R7, R1, #0
		RET
				
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


NUM_ZERO 	.FILL x0030
NUM_DIGITS 	.FILL #9
INV_CHAR  	.STRINGZ "Invalid expression."
.END
