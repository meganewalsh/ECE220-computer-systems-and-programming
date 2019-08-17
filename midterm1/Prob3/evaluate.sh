#!/bin/bash
lc3as decode_str.asm
lc3as test1.asm
lc3as test2.asm
lc3as test3.asm
lc3as test4.asm
lc3as test5.asm
lc3as test6.asm
lc3sim -s script > grade.txt
sed -i "/PC=/,/Loaded/d" grade.txt
sed -i '/^$/d' grade.txt
sed -i '100,$ d' grade.txt
echo "Grade: " >>grade.txt
echo "Manual Check: " >> grade.txt
