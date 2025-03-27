#!/bin/bash
clear

gcc -lpthread -c "mainPumper.c"
gcc -lpthread -o "mainPumper" "mainPumper.c"

gcc -lpthread -c "pedir.c"
gcc -lpthread -o "pedir" "pedir.c"

gcc -lpthread -c "pedir2.c"
gcc -lpthread -o "pedir2" "pedir2.c"

gcc -lpthread -c "d.c"
gcc -lpthread -o "d" "d.c"

gcc -lpthread -c "h.c"
gcc -lpthread -o "h" "h.c"

gcc -lpthread -c "v.c"
gcc -lpthread -o "v" "v.c"

gcc -lpthread -c "pp1.c"
gcc -lpthread -o "pp1" "pp1.c"

gcc -lpthread -c "pp2.c"
gcc -lpthread -o "pp2" "pp2.c"

./mainPumper
