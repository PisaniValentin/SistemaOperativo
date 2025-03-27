#!/bin/bash
clear

gcc -lpthread -c "taller.c"
gcc -lpthread -o "taller" "taller.c"

./taller
