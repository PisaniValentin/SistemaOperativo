#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
//Declaracion semaforos
sem_t sem_renos, sem_renosListos, sem_preparados,
 sem_trabajando, sem_elfosListos, sem_elfos, sem_problemasSolucionados;

pthread_mutex_t mutex_renos,mutex_elfos;

void * renos(void *arg){
	while(1){
		srand(time(NULL));
		pthread_mutex_lock(&mutex_renos);
		sem_wait(&sem_renos);

		if(sem_trywait(&sem_renos) == -1 ){
				printf("-Reno: LLegue y soy el ultimo, voy a avisarle a santa que prepare el trineo. \n");
				printf("-Reno: *Esperando a que santa prepare el trineo.* \n");
				sem_post(&sem_renosListos);
				sem_wait(&sem_preparados);
				printf("-Reno: *El trineo está listo y partimos a repartir los regalos.* \n");
				sem_post(&sem_trabajando);
		}else{
			printf("-Reno: LLegué de mis vacaciones..\n");
			sem_post(&sem_renos);
			pthread_mutex_unlock(&mutex_renos);
		}
		int tiempo = rand() % 3;
		sleep(tiempo);
	}
}

void * santa(void *arg){
	while(1){
		if(sem_trywait(&sem_renosListos) != -1){
			//Atiendo a los renos
			printf("-Santa: *Comienza a preparar el trineo.*\n");
			sem_post(&sem_preparados);
			sem_wait(&sem_trabajando);
			printf("-Santa: Repartiendo los regalos.\n");
			printf("-Santa: Trabajo terminado, los renos se pueden ir de vacaciones.\n");
			for(int i = 0; i<9; i++){
				sem_post(&sem_renos);
			}
			pthread_mutex_unlock(&mutex_renos);
		}else{
			//Atiendo a los elfos
			if(sem_trywait(&sem_elfosListos) != -1){
				printf("-Santa: *Ayudando a los elfos con sus problemas.*\n");
				sleep(1);
				sem_post(&sem_problemasSolucionados);
				for(int i = 0; i<4; i++){
					sem_post(&sem_elfos);
				}
				pthread_mutex_unlock(&mutex_elfos);
			}
		}
		sleep(2);
	}
}

void * elfos(void *arg){
	while(1){
		srand(time(NULL));
		pthread_mutex_lock(&mutex_elfos);
		sem_wait(&sem_elfos);
		if(sem_trywait(&sem_elfos) == -1){
			printf("-Elfo: Soy el tercer elfo con problema.\n");
			sem_post(&sem_elfosListos);
			sem_wait(&sem_problemasSolucionados);
			printf("-Elfo: Problemas solucionados! A seguir trabajando.\n");
		}else{
			printf("-Elfo: Me surgio un problema.\n");
			sem_post(&sem_elfos);
			pthread_mutex_unlock(&mutex_elfos);
		}
	}
	int tiempo = rand() % 2;
	sleep(tiempo);
}

int main(){
	sem_init(&sem_renos,0,9);
	sem_init(&sem_elfos,0,3);
	sem_init(&sem_renosListos,0,0);
	sem_init(&sem_preparados,0,0);
	sem_init(&sem_trabajando,0,0);
	sem_init(&sem_elfosListos,0,0);
	sem_init(&sem_problemasSolucionados,0,0);
	
	pthread_t reno_thread[9];
	pthread_t elfos_thread[4];
	pthread_t santa_thread;

	for(int i=0; i<9; i++){
		pthread_create(&reno_thread[i], NULL, renos, NULL);
	}
	pthread_create(&santa_thread, NULL, santa, NULL);
	for(int i=0; i<4; i++){
		pthread_create(&elfos_thread[i], NULL, elfos, NULL);
	}

	for(int i=0; i<9; i++){
		pthread_join(reno_thread[i],NULL);
	}
	for(int i=0; i<4; i++){
		pthread_join(elfos_thread[i],NULL);
	}
	pthread_join(santa_thread,NULL);

  sem_destroy(&sem_renos);
  sem_destroy(&sem_preparados);
  sem_destroy(&sem_trabajando);
  sem_destroy(&sem_elfosListos);
  sem_destroy(&sem_elfos);
  sem_destroy(&sem_problemasSolucionados);
}
