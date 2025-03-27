///Ejercicio 2.1
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

int existe(char * path);

int main(int argc, char * argv[]){
	char forma[26]="chmod [archivo] [permisos]";
	if(argc!= 3){
		printf("Argumentos invalidos, %s \n",forma);	///se controla la cantidad de argumentos validos
		exit(1);
		}
	if(existe(argv[1])){							/// se controla que el archivo al cual se hace referencia exista
		printf("Archivo invalido.\n");
		exit(1);
		}
	char permisos[5];								/// se determinan los permisos a setear en el archivo
	permisos[0]='0';
	permisos[4]='\0';
	
	if(!strcmp(argv[2],"r")){
		permisos[1]='4';permisos[2]='4';permisos[3]='4';
		}
	else
	if(!strcmp(argv[2],"w")){
		permisos[1]='2';permisos[2]='2';permisos[3]='2';
		}
	else
	if(!strcmp(argv[2],"x")){
		permisos[1]='1';permisos[2]='1';permisos[3]='1';
		}
	else
	if(!strcmp(argv[2],"rx")||!strcmp(argv[2],"xr")){
		permisos[1]='5';permisos[2]='5';permisos[3]='5';
		}
	else
	if(!strcmp(argv[2],"rw")||!strcmp(argv[2],"wr")){
		permisos[1]='6';permisos[2]='6';permisos[3]='6';
		}
	else
	if(!strcmp(argv[2],"xw")||!strcmp(argv[2],"wx")){
		permisos[1]='3';permisos[2]='3';permisos[3]='3';
		}
	else
	if(!strcmp(argv[2],"rwx")||!strcmp(argv[2],"rxw")||
		!strcmp(argv[2],"xrw")||!strcmp(argv[2],"xwr")||
		!strcmp(argv[2],"wrx")||!strcmp(argv[2],"wxr")){
		permisos[1]='7';permisos[2]='7';permisos[3]='7';
		}
	else{
		printf("Permisos invalidos.\n");
		exit(1);
	}
	int i= strtol(permisos,0,8);						/// convierte el string de pemirsos en un byte
	if(chmod(argv[1],i)<0){								///Cambia los permisos
		printf("Error al intentar cambiar permisos.\n");
		exit(1);
		}
return 0;
}

int existe(char * path){
	int toret;;
	struct stat fs;
	if(stat(path,&fs)<0){
		toret=1;
		}
	else 
		if(S_ISREG(fs.st_mode))
			toret=0;
			else
				toret=1;
	return toret;
	}
