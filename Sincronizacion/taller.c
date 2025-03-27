#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

//Secuencia: RRCM(Verde o Rojo) RRCM(Verde o Rojo)E
// LISTOOOOO
sem_t semR, semC, semM, semAux, semExt ;

void * operarioRuedas(void * dato){
		
	while(1){
		sem_wait(&semR);
	
		printf("Rueda \n");
		sleep(1);
		
		sem_post(&semC);
		}
}

void * operarioChasis(void * dato){
		
	while(1){
		sem_wait(&semC);
		sem_wait(&semC);
	
		printf("Chasis\n");
		sleep(1);
		
		sem_post(&semM);
		}
}

void * operarioMotor(void * dato){
		
	while(1){
		sem_wait(&semM);
	
		printf("Motor \n");
		sleep(1);
		
		sem_post(&semAux);
		}
}

void * pintorVerde(void * dato){
		
	while(1){
		sem_wait(&semAux);
	
		printf("Verde \n");
		sleep(1);
		
		sem_post(&semExt);
		}
}
void * pintorRojo(void * dato){
		
	while(1){
		sem_wait(&semAux);
	
		printf("Rojo \n");
		sleep(1);
		
		sem_post(&semExt);
		}
}
void * extra(void * dato){
	while(1){
		sem_wait(&semExt);
		
		sem_post(&semR);
		sem_post(&semR);
		
		sem_wait(&semExt);
		
		printf("Extra \n");
		sleep(1);
		
		sem_post(&semR);
		sem_post(&semR);
	}
}

int main(){
	
	sem_init(&semR,0,2);
	sem_init(&semC,0,0);
	sem_init(&semM,0,0);
	sem_init(&semAux,0,0);
	sem_init(&semExt,0,0);
	
	pthread_t hilo1;
	pthread_t hilo2;
	pthread_t hilo3;
	pthread_t hilo4;
	pthread_t hilo5;
	pthread_t hilo6;
					
	
	int ret;
	
	ret = pthread_create(&hilo1, NULL, operarioRuedas,NULL);
		
	if(ret != 0)
			printf("No se pudo crear el hilo 1\n");
			
	
	ret = pthread_create(&hilo2, NULL, operarioChasis,NULL);
		
	if(ret != 0)
			printf("No se pudo crear el hilo 2\n");
			
			
	ret = pthread_create(&hilo3, NULL, operarioMotor,NULL);
		
	if(ret != 0)
			printf("No se pudo crear el hilo 3\n");
			
			
	ret = pthread_create(&hilo4, NULL, pintorVerde,NULL);
		
	if(ret != 0)
			printf("No se pudo crear el hilo 4\n");
			
			
	ret = pthread_create(&hilo5, NULL, pintorRojo,NULL);
		
	if(ret != 0)
			printf("No se pudo crear el hilo 5\n");
			
	ret = pthread_create(&hilo6, NULL, extra,NULL);
		
	if(ret != 0)
			printf("No se pudo crear el hilo 6 \n");
			
	pthread_join(hilo1, NULL);	
	pthread_join(hilo2, NULL);	
	pthread_join(hilo3, NULL);	
	pthread_join(hilo4, NULL);	
	pthread_join(hilo5, NULL);	
	pthread_join(hilo6, NULL);	
	
	return 0;
}
