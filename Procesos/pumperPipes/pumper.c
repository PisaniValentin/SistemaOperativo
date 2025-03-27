#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include<pthread.h>
#include<string.h>
#include<sys/wait.h>

#include<fcntl.h>
#include<errno.h>

struct message{
	char body[12];
	};
typedef struct message tMessage;
#define SIZE_MSG sizeof(tMessage)

void pedir();
void derivarPedido();
void prepararHamburguesa();
void prepararMenuVegano();
void prepararPapas();
void despachar();

//---------------------------------

int pipeClienteNormal[2];
int pipeClienteVip[2];

int pipeCocinarHamburguesa[2];
int pipeCocinarPapasfritas[2];
int pipeCocinarVegano[2];

int pipeHamburguesaLista[2];
int pipePapasfritasListas[2];
int pipeVeganoListo[2];


int main(){
	pid_t pid;
	
	//Creo los pipes
	
	if(pipe(pipeClienteVip)== -1){
		perror("Pipe cliente normal.");
		exit(EXIT_FAILURE);
		}
		
	if (fcntl(pipeClienteVip[0], F_SETFL, O_NONBLOCK) < 0) exit(2);	// lectura del pipeclienteVip no bloqueante.
	
	//-------------------------------------------------------
		if(pipe(pipeClienteNormal)== -1){
		perror("Pipe cliente normal.");
		exit(EXIT_FAILURE);
		}
			
	//----------------------------------------------------


	if(pipe(pipeCocinarHamburguesa)== -1){
		perror("Pipe empleado hamburguesas.");
		exit(EXIT_FAILURE);
		}
		
    // -------------------------------------------------  
    
    if(pipe(pipeCocinarVegano)== -1){
		perror("Pipe empleado menu vegano.");
		exit(EXIT_FAILURE);
		}
	 
    // -------------------------------------------------  
    
    if(pipe(pipeCocinarPapasfritas)== -1){
		perror("Pipe empleado papas fritas.");
		exit(EXIT_FAILURE);
		}
	 
    // -------------------------------------------------  
    if(pipe(pipeHamburguesaLista)== -1){
		perror("Pipe hamburguesas listas.");
		exit(EXIT_FAILURE);
		}
			
	//-------------------------------
	
    if(pipe(pipeVeganoListo)== -1){
		perror("Pipe vegano listo.");
		exit(EXIT_FAILURE);
		}
	
	 // -------------------------------------------------  
    if(pipe(pipePapasfritasListas)== -1){
		perror("Pipe papas listas. ");
		exit(EXIT_FAILURE);
		}
    
	//Creacion de procesos
	
	pid = fork();				///Creo el proceso de cliente1
	if(pid < 0){
		perror("Cliente1.");
		exit(EXIT_FAILURE);
	}	else if(pid == 0) {
			
			pedir();
		}
		
		
		pid = fork();				///Creo el proceso de cliente2
	if(pid < 0){
		perror("Cliente2.");
		exit(EXIT_FAILURE);
	}	else if(pid == 0) {
			
			pedir();
		}
	pid = fork();				///Creo el proceso de empleado que deriva el pedido
	if(pid < 0){
		perror("EmpleadoCaja.");
		exit(EXIT_FAILURE);
	}	else if(pid == 0) {
			
			derivarPedido();
	}
	
	pid = fork();				///Creo el proceso de empleado hamburguesas
	if(pid < 0){
		perror("EmpleadoHamburguesa.");
		exit(EXIT_FAILURE);
	}	else if(pid == 0) {
		
			prepararHamburguesa();
		}
		
	pid = fork();				///Creo el proceso de empleado menu vegano
	if(pid < 0){
		perror("EmpleadoMenuVegano.");
		exit(EXIT_FAILURE);
	}	else if(pid == 0) {
			
			prepararMenuVegano();
		}
		
	pid = fork();				///Creo el proceso de empleado1 papasfritas
	if(pid < 0){
		perror("Empleado1Papasfritas.");
		exit(EXIT_FAILURE);
	}	else if(pid == 0) {
			
			prepararPapas();
		}
		
	pid = fork();				///Creo el proceso de empleado2 papasfritas
	if(pid < 0){
		perror("Empleado2Papasfritas.");
		exit(EXIT_FAILURE);
	}	else if(pid == 0) {
			
			prepararPapas();
		}
	
	for(int i=0; i<7; i++){
		wait(NULL);
		}
		
}

void pedir(){	
	//cierro pipes para lectura
	close(pipeCocinarHamburguesa[0]);
	close(pipeCocinarVegano[0]);
	close(pipeCocinarPapasfritas[0]);
	close(pipeClienteVip[0]);
	close(pipeClienteNormal[0]);
		
	//cierro pipes para escritura
	close(pipeCocinarHamburguesa[1]);
	close(pipeCocinarVegano[1]);
	close(pipeCocinarPapasfritas[1]);
	
	close(pipeHamburguesaLista[1]);
	close(pipeVeganoListo[1]);
	close(pipePapasfritasListas[1]);
	
	tMessage mensaje;
	int tipoPedido ;
	int tipoCliente;
	
	int intpedido;
	char buffer [SIZE_MSG];

	while(1){

		srand(time(NULL));
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
		
        if (tipoCliente == 0) {
            write(pipeClienteVip[1], &mensaje, SIZE_MSG); 
        } else {
           write(pipeClienteNormal[1], &mensaje, SIZE_MSG);
            }
        sleep(1);
      
		if (strcmp(mensaje.body, "Hamburguesa") == 0) {
			
			intpedido = read(pipeHamburguesaLista[0], buffer, SIZE_MSG);
			if (intpedido > 0) {
			printf("Recibi mis %s \n",buffer);
			}
			else printf("no recibi h");
				
		} else if (strcmp(mensaje.body, "Menu Vegano") == 0) {
			
			intpedido = read(pipeVeganoListo[0], buffer, SIZE_MSG);
			if (intpedido > 0) {
			printf("Recibi mi %s \n",buffer);
			}
			else printf("no recibi v");
			
		} else if (strcmp(mensaje.body, "Papasfritas") == 0) {
				intpedido = read(pipePapasfritasListas[0], buffer, SIZE_MSG);
						if (intpedido > 0) {
					printf("Recibi mis %s \n",buffer);
				 }
				 else printf("no recibi p");
			}
		
		sleep(2); 
	}

	close(pipeClienteVip[1]);
	close(pipeClienteNormal[1]);
	
	close(pipeHamburguesaLista[0]);
	close(pipeVeganoListo[0]);
	close(pipePapasfritasListas[0]);
}

void derivarPedido(){
	//Cierro pipes para escritura
	close(pipeClienteVip[1]);
	close(pipeClienteNormal[1]);
	
	//cierro pipes de lectura
	close(pipeCocinarHamburguesa[0]);
	close(pipeCocinarVegano[0]);
	close(pipeCocinarPapasfritas[0]);
	
	close(pipeHamburguesaLista[0]);
	close(pipeVeganoListo[0]);
	close(pipePapasfritasListas[0]);
	
	//cierro pipes escritura
	close(pipeHamburguesaLista[1]);
	close(pipeVeganoListo[1]);
	close(pipePapasfritasListas[1]);
	
	char buf [SIZE_MSG];
	int pedidoRead ;

	while(1){
		
		pedidoRead= read(pipeClienteVip[0], buf, SIZE_MSG);
		
		if (pedidoRead > 0) {
			printf("Pedido vip\n");
			
        		if(strcmp(buf, "Hamburguesa")==0){
			
				write(pipeCocinarHamburguesa[1], buf, SIZE_MSG); }
				
				else { if(strcmp(buf, "Menu Vegano")==0){
						write(pipeCocinarVegano[1], buf, SIZE_MSG);}
						
						else { if(strcmp(buf, "Papasfritas")==0){
								write(pipeCocinarPapasfritas[1], buf, SIZE_MSG);}
								else {
									printf("llego aca por vip\n");
								}
							}
					}
        	
        } else if (errno == EAGAIN) {  
          
            pedidoRead = read(pipeClienteNormal[0], buf, SIZE_MSG);

            if (pedidoRead > 0) {
			    printf("Pedido normal\n");            
                if(strcmp(buf, "Hamburguesa")==0){
				
				write(pipeCocinarHamburguesa[1], buf, SIZE_MSG); }
				
				else { if(strcmp(buf, "Menu Vegano")==0){
						write(pipeCocinarVegano[1], buf, SIZE_MSG);}
						
						else { if(strcmp(buf, "Papasfritas")==0){
								write(pipeCocinarPapasfritas[1], buf, SIZE_MSG);}
							
							else {
									printf("llego aca por normal\n");
								}
							}
					}
					
            } else {
                // Si no hay pedido normal tampoco
                printf("No tengo ningún pedido.\n");
            }
        }
        sleep(2);
	}
	//cierro pipes para escritura
	close(pipeCocinarHamburguesa[1]);
	close(pipeCocinarVegano[1]);
	close(pipeCocinarPapasfritas[1]);
	
	//cierro pipe para lectura
	close(pipeClienteNormal[0]);
	close(pipeClienteVip[0]);
}
void prepararHamburguesa(){
	
	//Cierro pipes para escritura
	close(pipeCocinarHamburguesa[1]);
	
	//Cierro pipes para lectura

	close(pipeCocinarVegano[0]);
	close(pipeCocinarPapasfritas[0]);
	close(pipeClienteNormal[0]);
	close(pipeClienteVip[0]);
	
	close(pipeHamburguesaLista[0]);
	close(pipeVeganoListo[0]);
	close(pipePapasfritasListas[0]);
	
	//cierro pipes para escritura;
	
	close(pipeCocinarVegano[1]);
	close(pipeCocinarPapasfritas[1]);
	close(pipeClienteNormal[1]);
	close(pipeClienteVip[1]);
	
	close(pipeVeganoListo[1]);
	close(pipePapasfritasListas[1]);
	
	char buf [SIZE_MSG] ; 
	int nread1;
		
	while(1) {
		
		 nread1= read(pipeCocinarHamburguesa[0], buf, SIZE_MSG ) ;
		
		if(nread1 >0) {
			printf("Cocino hamburguesa\n");
			sleep(1);
			printf("Hamburguesa lista\n");
			write(pipeHamburguesaLista[1], buf, SIZE_MSG);	
		}
		else {
			if (errno == EAGAIN) {
					printf("error en hamb");
				}	
		}	
	sleep(1);
	}
		//cierro pipe para lectura
	close(pipeCocinarHamburguesa[0]);
	close(pipeHamburguesaLista[1]);
}

void prepararMenuVegano(){
	
	//Cierro pipes para escritura
	close(pipeCocinarVegano[1]);
	
	//Cierro pipes para lectura
	
	close(pipeCocinarHamburguesa[0]);
	close(pipeCocinarPapasfritas[0]);
	close(pipeClienteNormal[0]);
	close(pipeClienteVip[0]);
	
	close(pipeHamburguesaLista[0]);
	close(pipeVeganoListo[0]);
	close(pipePapasfritasListas[0]);
	
	//cierro pipes para escritura;
	close(pipeCocinarHamburguesa[1]);
	close(pipeCocinarPapasfritas[1]);
	close(pipeClienteNormal[1]);
	close(pipeClienteVip[1]);
	
	close(pipeHamburguesaLista[1]);
	close(pipePapasfritasListas[1]);
	
	char buf [SIZE_MSG] ; 
	int nread2;
	while(1) {
		
		 nread2= read(pipeCocinarVegano[0], buf, SIZE_MSG ) ;
		
		if(nread2 >0) {				
			printf("Preparovegano\n");		
			sleep(1);
			printf("Vegano listo\n");
			write(pipeVeganoListo[1], buf, SIZE_MSG);
		}
		else {
				if (errno == EAGAIN) {
					printf("error en veg");
				}	
		}	
	sleep(1);
	}
		//cierro pipe para lectura
	close(pipeCocinarVegano[0]);
	close(pipeVeganoListo[1]);
}

void prepararPapas(){
	
	//Cierro pipes para 	
	close(pipeCocinarPapasfritas[1]);
	
	//Cierro pipes para lectura
	
	close(pipeCocinarHamburguesa[0]);
	close(pipeCocinarVegano[0]);
	close(pipeClienteNormal[0]);
	close(pipeClienteVip[0]);
	
	close(pipeHamburguesaLista[0]);
	close(pipeVeganoListo[0]);
	
	//cierro pipes para escritura;
	close(pipeCocinarHamburguesa[1]);
	close(pipeCocinarVegano[1]);
	close(pipeClienteNormal[1]);
	close(pipeClienteVip[1]);
	
	close(pipeHamburguesaLista[1]);
	close(pipeVeganoListo[1]);
	
	char buf [SIZE_MSG] ; 
	
	while(1) {
		
		int nread3 = read(pipeCocinarPapasfritas[0], buf, SIZE_MSG ) ;
		
		if(nread3 >0) {
			printf("Soy proceso: (PID: %d), preparo papas\n", getpid());
			printf("Preparo papas\n");
			sleep(1);
			printf("Papas listas\n");
			write(pipePapasfritasListas[1], buf, SIZE_MSG);				
		}
		else {
			if (errno == EAGAIN) {
					printf("error en papas");
				}	
		}	
			sleep(1);
	
	}
	//cierro pipe para lectura
	close(pipeCocinarPapasfritas[0]);
	close(pipePapasfritasListas[1]);
}
