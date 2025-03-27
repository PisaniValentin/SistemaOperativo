#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define max_car 120		///Numero maximo de caracteres

int main(int argc, char * args[]){
	int estado;
	if(args[1]!=NULL){	///chequea que se ingrese un nombre
		char ruta[max_car];
		char directorioActual[max_car];
		
		getcwd(directorioActual,max_car);
		strcpy(ruta,directorioActual);
		strcat(ruta,"/");
		strcat(ruta,args[1]);		///Ruta final del directorio a crear
		
		estado = mkdir(ruta,0777);		/// crea el directorio con todos los permisos para todos los usuarios
		if(estado!=0){
			printf("Se produjo un error al intentar crear el directorio\n");
		}
	}
	else{
		printf("Error, debe ingresar un directorio valido\n");
	}		
}
