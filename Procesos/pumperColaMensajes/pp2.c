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

		int i =	msgrcv(queueId, &mensaje, SIZE_MSG, TYPE_5, 0); // leo
		
		if( i > 0){
			printf("Soy papas2\n");
			printf("Cocino papas\n");
			sleep(1);
			printf("Papas listas\n");
			mensaje.type = TYPE_7;
			msgsnd(queueId, &mensaje, SIZE_MSG,0);
		}
		else {
			printf("error en papas2\n");
		}
		sleep(1);
	}
}
