#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

#define max_car 120		///Numero maximo de caracteres
#define YEL "\x1B[33m"
#define RESET  "\x1B[0m"

int main(int argc, char * args[])
{
	char ruta[max_car];		///direccion a listar
	int cantArch; 
	struct dirent **listaArchs;		///lista de archivos y directorios encontrados
	char pwd[max_car];
	char * directory;
	int len;
	char * buf;
	
	getcwd(pwd,max_car);
	strcpy(ruta,pwd);			///Listar contenido de carpeta actual
 	
  	if(args[1]!=NULL){		///Listar contenido de otra carpeta
		directory = args[1];
		if(directory[0] == '/')
			strcpy(ruta, args[1]);
		else{
			strcat(ruta,"/"),
			strcat(ruta,args[1]);
			}
		}
	
	cantArch = scandir(ruta, &listaArchs, NULL, alphasort);
    if (cantArch < 0){
        perror("Error al intentar listar el contenido del directorio");
	}else {
		if(cantArch == 2){///Error, solo encontró directorio actual y el directorio padre
			printf("El directorio <%s> esta vacio.\n",ruta);
		}else{
			int cont=0;
			struct stat statbuf;
			while(cont<cantArch){///Imprimo los archivos y directorios distintos del actual y el padre
				len = strlen(ruta);
				if(strcmp(listaArchs[cont]-> d_name,".")!=0 && strcmp(listaArchs[cont]->d_name,"..")!=0)	///Compara para no listar la direccioin del directorio actual y la del padre
				{
					len = len + strlen(listaArchs[cont]-> d_name) + 2;
					buf = malloc(len);
					
					snprintf(buf, len, "%s/%s", ruta, listaArchs[cont]-> d_name);		///arma la cadena de caracteres completa de la carpeta de la cual se quiere listar su contenido
					
					if ( !stat(buf, &statbuf) )											/// cargo en statbuf el estado del directorio buf
					{
						if ( S_ISDIR( statbuf.st_mode ) )
							printf(YEL "%s\n" RESET,listaArchs[cont]-> d_name);			/// Si es una carpeta imprime el nombre en amarillo

						else
							printf("%s\n",listaArchs[cont]-> d_name);					///Si no es una carpeta lo imprime en color normal
					}
					
					free(buf);
				}
				cont++;
			}
		}
    }
}
