.ORIG x3000
AND R0, R0, #0;
AND R1, R1, #0
ADD R1, R1, #2
JSR BITSWAP
LEA R0, RETURNED
PUTS
HALT

RETURNED .STRINGZ "Successfully Returned\n"
; x3000

LD R2, STRSTART

LOOP
LDR R0, R2, #0
BRz FINISH		; We are done when we hit NULL
LD R1, BITMASK
JSR BITSWAP		; Do the bitswap
STR R0, R2, #0		; Writes back to the original location
ADD R2, R2, #1
BRnzp LOOP 
FINISH 
HALT

STRSTART .FILL x4000
BITMASK .FILL x0003	; set n = 3

;Do not touch or change and code above this line
;---------------------------------------------
;You must not change the separation line above
;Please write ALL your code for BITSWAP in between the separations lines,
;including all the labels, code, and .FILL commands

 
;Subroutine to swap bits
;Input: 
;R0: the ascii that to be swapped 
;R1: the number of bits to be swapped
; You can assume R1 is always 0, 1, 2, or 3
;Output: R0, the swapped ascii
BITSWAP
;;YOUR CODE STARTS HERE
		

CHECK_N						; n value = R2
		AND R1, R1,  #0
				
		ADD R3, R2, #0
		BRz NUM_0

		ADD R3, R3, #-1
		BRz NUM_1

		ADD R3, R3, #-1
		BRz NUM_2
		
		ADD R3, R3, #-1
		BRz NUM_3
		
		ADD R3, R3, #-1
		BRz NUM_4

NUM_0		ADD R1, R1, #0

NUM_1		ADD R1, R1, #1

NUM_2		ADD R1, R1, #2

NUM_3		ADD R1, R1, #3

NUM_4 		ADD R1, R1, #4


RET

;You must not change the separation line below.
;Write all your code for BITSWAP above this line
;=============================================


;DO NOT CHANGE THE GIVEN CODE BELOW
;=============================================
;;EXTRACT Subroutine (Given Code) 
;;Input: R0 - ASCII value
;;       R1 - n (between 0 and 4) bits to be extracted
EXTRACT
ST R0, SAVER1
ST R7, SAVER3
LEA R0, EXCALLED
PUTS
LD R0, SAVER1
LD R7, SAVER3
RET
EXCALLED .STRINGZ "\nEXTRACT CALLED\n"
SAVER1 .FILL #0
SAVER2 .FILL #0
SAVER3 .FILL #0
.END
