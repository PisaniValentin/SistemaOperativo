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
	int i;
	while(1){
		
		i = msgrcv(queueId, &mensaje, SIZE_MSG, TYPE_1, IPC_NOWAIT); //lei de vip
		
		if(i > 0) {
			printf("Pedido vip\n");
			if(strcmp(mensaje.body, "Hamburguesa")==0){
				
				mensaje.type = TYPE_3;
			
			} else if (strcmp(mensaje.body, "Menu Vegano")==0) {
					mensaje.type = TYPE_4;
					
				} else if(strcmp(mensaje.body, "Papasfritas")==0) {
						mensaje.type = TYPE_5;
					}
				msgsnd(queueId, &mensaje, SIZE_MSG, 0);
					
			} else {
			i = msgrcv(queueId, &mensaje, SIZE_MSG, TYPE_2, 0); //leo de normal creo
		
			if(i > 0) {
				printf("Pedido normal\n");
				
					if(strcmp(mensaje.body, "Hamburguesa")==0){
						
						mensaje.type = TYPE_3;
					
				} else if (strcmp(mensaje.body, "Menu Vegano")==0) {
						mensaje.type = TYPE_4;
						
					} else if(strcmp(mensaje.body, "Papasfritas")==0) {
							mensaje.type = TYPE_5;
						}
			msgsnd(queueId, &mensaje, SIZE_MSG,0);
			}
			else { if(i==-1){
                printf("No tengo ningún pedido.\n");
					}	
            }
		}
		sleep(2);
		  
	}
	
}
