.ORIG x3000

  AND R0, R0, #0
  AND R1, R1, #0
  AND R2, R2, #0
  AND R3, R3, #0
  AND R4, R4, #0
  AND R5, R5, #0
  AND R6, R6, #0

		LEA R0, OPEN
		PUTS

READCHAR	GETC		;read character from keyboard
		OUT		;print character to console

CHECKSEMI	LD R1, SEMICOL
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R1, R0
		BRz PRINTSUM
	 	
CHECKPLUS	LD R1, PLUS
		NOT R1, R1
		ADD R1, R1, #1
                ADD R1, R1, R0
		BRnp CHECKNUM
		JSR ADDITION
		BRnzp READCHAR

CHECKNUM	LD R6, THIRTY
		NOT R6, R6
		ADD R6, R6, #1
		ADD R6, R6, R0
		BRn ERROR
		ADD R0, R6, #0
		LD R6, NINE
		NOT R6, R6
		ADD R6, R6, #1
		ADD R6, R6, R0
		BRp ERROR
		JSR PUSH
		BRnzp READCHAR

ADDITION	ADD R5, R7, #0
		JSR POP
		ADD R1, R0, #0
		JSR POP
		ADD R0, R1, R0
		OUT
		JSR PUSH
		ADD R7, R5, #0
		RET
			
ERROR		LEA R0, INV
		PUTS
		BRnzp READCHAR

PRINTSUM	JSR POP
		OUT
		HALT		

PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACk_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        ADD R5, R5, #1          ;
DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
        RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;

POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;




SEMICOL .FILL		x3B
THIRTY	.FILL		x30
NINE	.FILL		x9
PLUS	.FILL		x002B
OPEN	.STRINGZ	"PLEASE ENTER YOUR CALCULATION."
INV	.STRINGZ	"INVALID ENTRY, TRY AGAIN."
.END
