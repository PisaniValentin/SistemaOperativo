#!/bin/bash
clear

gcc -lpthread -c "pumper.c"
gcc -lpthread -o "pumper" "pumper.c"

./pumper