.ORIG x3000
AND R0, R0, #0;
AND R1, R1, #0
ADD R1, R1, #2
JSR BITSWAP
LEA R0, RETURNED
PUTS
HALT

RETURNED .STRINGZ "Successfully Returned\n"
