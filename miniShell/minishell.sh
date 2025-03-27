#!/bin/bash
clear

cc -lpthread -c "command_ls.c"
gcc -lpthread -o "command_ls" "command_ls.c" 

gcc -lpthread -c "command_remove.c" 
gcc -lpthread -o "command_remove" "command_remove.c" 

gcc -lpthread -c "command_ayuda.c"
gcc -lpthread -o "command_ayuda" "command_ayuda.c" 

gcc -lpthread -c "command_mkfile.c" 
gcc -lpthread -o "command_mkfile" "command_mkfile.c" 

gcc -lpthread -c "command_mkdir.c" 
gcc -lpthread -o "command_mkdir" "command_mkdir.c" 

gcc -lpthread -c "command_chmod.c" 
gcc -lpthread -o "command_chmod" "command_chmod.c" 

gcc -lpthread -c "command_cat.c" 
gcc -lpthread -o "command_cat" "command_cat.c" 

gcc -lpthread -c "minishell.c" 
gcc -lpthread -o "minishell" "minishell.c"

./minishell
