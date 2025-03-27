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

	int tipoPedido ;
	int tipoCliente;
	srand(time(NULL));
	
	while (msgrcv(queueId, &mensaje, SIZE_MSG, 0, IPC_NOWAIT) != -1) {
       //printf("Vacio la cola para comenzar\n", mensaje.type, mensaje.body);
	}

	while(1){		
		tipoPedido = rand() % 3;
		memset(mensaje.body, 0, sizeof(mensaje.body));
		switch(tipoPedido) {
			
			case 0: strcat(mensaje.body,"Hamburguesa");
			break;
			
			case 1: strcat(mensaje.body,"Menu Vegano");
			break;
			
			case 2: strcat(mensaje.body,"Papasfritas");
			break;
					
			default: printf("Error");
		}
		
		tipoCliente= rand() % 2;
		
        if (tipoCliente == 0) { //vip
         	mensaje.type = TYPE_1;
         
        } else { //normal
		mensaje.type = TYPE_2;		
            }
	msgsnd(queueId, &mensaje, SIZE_MSG, 0);

      	sleep(2);
	
	if (strcmp(mensaje.body, "Hamburguesa") == 0) {

		int h = msgrcv(queueId, &mensaje, SIZE_MSG,TYPE_6, IPC_NOWAIT);
		if(h > 0) {
			printf("Recibi mi %s \n",mensaje.body);
		}

	}else if (strcmp(mensaje.body, "Menu Vegano") == 0) {
		
		int v= msgrcv(queueId, &mensaje, SIZE_MSG,TYPE_7, IPC_NOWAIT);
		if(v > 0) {
			printf("Recibi mi %s \n",mensaje.body);
		}
		
	}else if (strcmp(mensaje.body, "Papasfritas") == 0) {
		
		int p= msgrcv(queueId, &mensaje, SIZE_MSG,TYPE_8,IPC_NOWAIT);
		if(p > 0) {
			printf("Recibi mis %s \n",mensaje.body);
		}
	}
    }
}
