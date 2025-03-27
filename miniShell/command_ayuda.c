#include <stdio.h>


int main(){
	printf("\tMini Shell\n");
	printf("Funciones disponibles:\n");
	
	printf("mkdir [dir]		Crea una nueva carpeta con nombre dir en el area de trabajo actual\n");

	
	printf("rmdir [dir]		Elimina la carpeta dir con todo su contenido.\n");
	
	printf("mkfile [filename.ext]	Crea un archivo con nombre filename y extension ext.\n");
	
	printf("ls [dir]		Lista el contenido del directorio actual o del directorio dir.\n");
	
	printf("cat [filename]		Muestra el contenido de un archivo.\n");
	
	printf("help			Muestra las funciones disponibles.\n");
	
	printf("chmod [file] [permisos]	    Cambia los permisos del archivo file a los pasados por parametro.\n");
	
	printf("pwd 			Muestra la direccion del directorio actual.\n");
	
	printf("exit			Finaliza la ejecucion del terminal.\n");
	
}
