#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define max_args 10		///Numero maximo de argumentos
#define max_car 120		///Numero maximo de caracteres

#define CYN "\x1B[36m"
#define RESET  "\x1B[0m"


char linea[max_car];
char *args[max_args];
char *comando;

char salir[4]="exit";

char path[max_car];
char home[max_car];
char pwd[max_car];

void limpiarlinea(){
	int i;
	for(i=0;i<max_car;i++)
		linea[i]='\0';
	}
void separarArgs(char * c){
	int i;
	for(i=0;i<(max_args-1);i++) ///borra argumentos previos
		args[i]=NULL;
	i = 0;
	args[i] = strtok(linea," ");
	while((args[i]!=NULL)&&(i<(max_args-1))) {
		i++;
		args[i]=strtok(NULL," ");
		}	
	}

int main(){
	int pid,ret,control=1;
	strcpy(path,getenv("PATH"));	///Directorio path
	getcwd(pwd,max_car);			///Direccion de ruta actual
	strcpy(home,getenv("HOME"));	///Direccion home
	
	while(control){
		printf( CYN "miniShell@so:~$ " RESET);
		__fpurge(stdin);
		limpiarlinea();
		scanf("%[^\n]s",linea);
		
		if(strlen(linea)>0){		///controla si ingreso algun comando
			separarArgs(linea);
			comando=args[0];
		
			if(strcmp(comando,"exit")==0)			/// comando EXIT para salir de minishell
				control = 0;
			
			else if(strcmp(comando,"ls")==0)		/// comando ls para listar contenido
				{
					pid = fork();
				if (pid==0)
					{
						ret= execv("command_ls", args);
						if(ret==(-1))
						{
							perror("Error al llamar excev\n");
							exit(0);
						}
					}
					else
						wait(NULL);
				}
				
			else if(strcmp(comando,"mkdir")==0)		/// comando mkfile para crear directorio
				{
					pid = fork();
				if (pid==0)
					{
						ret= execv("command_mkdir", args);
						if(ret==(-1))
						{
							perror("Error al llamar excev\n");
							exit(0);
						}
					}
					else
						wait(NULL);
				}
			
			else if(strcmp(comando,"chmod")==0)		/// comando chmod para cambiar permisos de un archivo
				{
					pid = fork();
				if (pid==0)
					{
						ret= execv("command_chmod", args);
						if(ret==(-1))
						{
							perror("Error al llamar excev\n");
							exit(0);
						}
					}
					else
						wait(NULL);
				}	
			
			else if(strcmp(comando,"mkfile")==0)		/// comando mkfile para crear archivo
				{
					pid = fork();
				if (pid==0)
					{
						ret= execv("command_mkfile", args);
						if(ret==(-1))
						{
							perror("Error al llamar excev\n");
							exit(0);
						}
					}
					else
						wait(NULL);
				}	
				
			else if(strcmp(comando,"rmdir")==0)			/// comando rmdir para elminar directorio 
				{
					pid = fork();
				if (pid==0)
					{
						ret= execv("command_remove", args);
						if(ret==(-1))
						{
							perror("Error al llamar excev\n");
							exit(0);
						}
					}
					else
						wait(NULL);
				}
							
			else if(strcmp(comando,"help")==0)  		/// comando help para mostrar funciones disponibles
			{
					pid = fork();
				if (pid==0)
					{
						ret= execv("command_ayuda", args);
						if(ret==(-1))
						{
							perror("Error al llamar excev\n");
							exit(0);
						}
					}
					else
						wait(NULL);
				}
				
			else if(strcmp(comando,"cat")==0)  		/// comando cat para mostrar contenido de un archivo
			{
					pid = fork();
				if (pid==0)
					{
						ret= execv("command_cat", args);
						if(ret==(-1))
						{
							perror("Error al llamar excev\n");
							exit(0);
						}
					}
					else
						wait(NULL);
				}
			
			else if(strcmp(comando,"pwd")==0)  		/// comando pwd muestra el directorio actual
			{
				printf("%s\n",pwd);
				}

	
					}///Fin then control de ingreso de comandos
		}	///Fin while control
	return 0;
}
