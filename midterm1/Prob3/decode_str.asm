.ORIG x3000

;;YOUR CODE STARTS HERE
  AND R0, R0, #0
  AND R1, R1, #0
  AND R2, R2, #0
  AND R3, R3, #0
  AND R4, R4, #0
  AND R5, R5, #0
  AND R6, R6, #0
  AND R7, R7, #0

	LEA R1, STRING_START	; R1 contains address being looked at

READ	LDR R1, R1, #0		; R6 contains data in address being looked at
	LDR R6, R1, #0
	BRnp CH_NUM
	HALT

CH_NUM  LD R2, ASCII_ZERO
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R6, R2
	BRn CH_AST
	LD R2, ASCII_NINE
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R6, R2
	BRp CH_AST
	;R6 is now confirmed to be a number. Counter.
	ADD R1, R1, x0001
	BRnzp READ

CH_AST  LD R2, ASCII_NEG_ASTERISK  
        ADD R2, R6, R2
	BRz F_AST
	;Ast not found. Must be word.
	ST R1, WORD_START	; Store address of start of word 
	ADD R3, R1, x0001
	LDR R6, R3, #0		; R6 contains data in address being looked at
	BRnzp CH_AST
	
F_AST	ST R3, WORD_END
	LD R0, WORD_START
	PUTS
	ADD R1, R1, x0001
	BRnzp READ




;;;;; Labels
WORD_START		.BLKW #1
WORD_END		.BLKW #1

NUM_ZERO		.FILL x0030
NUM_DIGITS		.FILL #9
ASCII_ZERO		.FILL x0030		;ASCII value of Zero
ASCII_NINE		.FILL x0039		;ASCII value of Nine
ASCII_NEG_ASTERISK   	.FILL xFFD6  		;negative of ascii value of *
ASCII_NEG_ZERO    	.FILL xFFD0		;negative of ascii value of 0
STRING_START 		.FILL x4000		;starting address of string
.END
