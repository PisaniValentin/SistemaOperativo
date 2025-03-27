#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<time.h>
#include "SharedPumper.h"

#include<string.h>
#include<sys/wait.h>

int main(){
	
	pid_t pid;
	char * args[] = { NULL };
	
	
	pid = fork();
	if(pid < 0){
		perror("Proceso Cliente");
		exit(EXIT_FAILURE);
	}	else if(pid == 0){
			execv("pedir", args);
	}
	
	pid = fork();
	if(pid < 0){
		perror("Proceso Cliente2");
		exit(EXIT_FAILURE);
	}	else if(pid == 0){
			execv("pedir", args);
	}
	
	pid = fork();
	if(pid < 0){
		perror("Proceso derivar");
		exit(EXIT_FAILURE);
	}	else if(pid == 0){
			execv("d", args);
	}
	pid = fork();
	if(pid < 0){
		perror("Empleado hamburguesa");
		exit(EXIT_FAILURE);
	}	else if(pid == 0){
			execv("h", args);
	}
	
	pid = fork();
	if(pid < 0){
		perror("Empleado Vegano");
		exit(EXIT_FAILURE);
	}	else if(pid == 0){
			execv("v", args);
	}
	
	pid = fork();
	if(pid < 0){
		perror("Empleado Papas fritas1");
		exit(EXIT_FAILURE);
	}	else if(pid == 0){
			execv("pp1", args);
	}
	
	pid = fork();
	if(pid < 0){
		perror("Empleado Papas fritas2");
		exit(EXIT_FAILURE);
	}	else if(pid == 0){
			execv("pp2", args);
	}
	
		
	for(int i=0; i<5; i++){
	wait(NULL);
	}

}
