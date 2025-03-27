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
	
	tMessage mensaje;
	
	key_t key = ftok(PATH, 1);
	
	if(key<0){
		perror("Error al crear la clave\n");
		exit(EXIT_FAILURE);
		}
	
	int queueId = msgget(key, 0666 | IPC_CREAT);
	
	if(queueId<0){
		perror("Error al crear la cola de mensaje\n");
		exit(EXIT_FAILURE);
	}
	
	while(1){
		int i =	msgrcv(queueId, &mensaje, SIZE_MSG, TYPE_4,0); // leo
		
		if( i > 0){ 
			printf("Cocino Vegano\n");
			sleep(1);
			printf("Vegano listo\n");
			mensaje.type = TYPE_8;
			msgsnd(queueId, &mensaje, SIZE_MSG,0);
		}
		else {
			printf("error en veg\n");
		}
		sleep(1);
	}
}
