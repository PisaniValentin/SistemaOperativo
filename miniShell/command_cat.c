#include <stdio.h>

int main(int argc, char * argv[]){

	char * nombre;
	nombre = argv[1];

	FILE * archi = fopen(nombre, "r");			///Abre el archivo a leer
	
	if ( archi == NULL )
		perror("Error al abrir archivo");
		else
		{
			char buff[255];
			
			fgets(buff, 255, archi);		///lee la primer linea del archivo
			
			while ( !feof(archi))		///si no llego al final del archivo continua
			{
				printf("%s",buff);			///imprime lo leido
				fgets(buff, 255, archi);
			}
			printf("%s", buff);
			
			fclose(archi);
		}
	

}
