#include <stdio.h>

void crearArchivo(char * filename){
		FILE * archi = fopen(filename, "w");
		if ( archi != NULL)
			printf("Se creo con exito\n");
		else 
			perror("Error al crear archivo\n");
	
	}

int main(int argc, char * argv[])
{
	char * nombre;
	nombre = argv[1];
	
	FILE * archi = fopen(nombre, "r");	///primero intento abrir un archivo para lectura (r) con el nombre pasado por parametro para ver si ya existe
	char c;
	
	if ( archi == NULL)
		crearArchivo(nombre);		///si no existe lo creo
		
	else
	{								///si existe lo cierro y pregunto si desea sustituirlo
		fclose(archi);
		printf("El archivo ya existe desea sustituirlo?\n");	
		printf( "Y o N ?\n");
		scanf("%c",&c);
		if ( c == 'y' || c == 'Y' )
			crearArchivo(nombre);
	} 
}
