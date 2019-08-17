#!/bin/bash 

# Assemble the file
echo "Assemble prog.asm"
echo "------ Assemble prog.asm ------" > grade.txt
`lc3as ./prog.asm >> grade.txt` 
echo >> grade.txt
echo >> grade.txt 
echo >> grade.txt
echo >> grade.txt 



echo "************ Test 3 ************" >> grade.txt 
echo "[[[[ The input (R2) is 1 (x0001), the output (R3) should be 1 (x0001) ]]]]" >> grade.txt
echo "Running test3"
lc3sim -s test3 >> grade.txt
echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" >> grade.txt
echo >> grade.txt
echo >> grade.txt 
echo >> grade.txt
echo >> grade.txt 



echo "************ Test 4 ************" >> grade.txt 
echo "[[[[ The input (R2) is 27 (x001B), the output (R3) should be 25 (x0019) ]]]]" >> grade.txt
echo "Running test4"
lc3sim -s test4 >> grade.txt
echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" >> grade.txt
echo >> grade.txt
echo >> grade.txt 
echo >> grade.txt
echo >> grade.txt 


echo "************ Test 5 ************" >> grade.txt 
echo "[[[[ The input (R2) is 64 (x0040), the output (R3) should be 64 (x0040) ]]]]" >> grade.txt
echo "Running test5"
lc3sim -s test5 >> grade.txt
echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" >> grade.txt
echo >> grade.txt
echo >> grade.txt 


echo "Grade:" >> grade.txt
echo "******" >> grade.txt
echo "Summary: " >> grade.txt
echo "Total: " >> grade.txt
exit 0
