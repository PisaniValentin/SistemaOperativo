#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

/// Funcion recursiva para eliminar una carpeta junto con su contenido
int deleteDirectory(const char *path)
{
	DIR *d = opendir(path);		///Abre la direccion del directorio y la carga en d
	int path_len = strlen(path);
	int r = -1;					///variable de control para eliminar el directorio luego de recorrer la direccion path
	
	if ( d )
	{
		struct dirent *p;
		
		r=0;
		int r2;
		char * buf;
		int len;
		while( !r && ( p=readdir(d) ) ) ///si la direccion actual es una carpeta y hay mas entradas de directorio
		{
			r2 = -1;
			
			if ( !strcmp(p->d_name,".") || !strcmp(p->d_name,"..") ) /// Control para no entrar en la direccion del directorio actual "." o en la direccion del directorio padre ".."
				continue;
			
			len = path_len + strlen(p->d_name) + 2;
			buf = malloc(len);
			
			if(buf)
			{
				struct stat statbuf;
				snprintf(buf, len, "%s/%s", path, p->d_name); /// Armo la cadena de caracteres de la entrada de directorio que quiero analizar
				
				if ( !stat(buf, &statbuf) )				///cargo en statbuf el estado del directorio buf
				{
					if ( S_ISDIR( statbuf.st_mode ) )		///Si es un directorio llamo a la funcion deleteDirectory para que lo elimine, si no es un directorio lo elimino
						r2 = deleteDirectory(buf);
					else
						r2 = unlink(buf); ///elimina el archivo 
				}
				
				free(buf);  ///Luego libero el espacio que habia reservado para la direccion del directorio que acabo de eliminar
			}
			
			r = r2;
			
		}
		
		closedir(d);  /// Cierro el directorio asociado a d
	}
	
	if(!r)			/// si todas las eliminaciones del contenido del directorio path fueron exitosas lo elimino
		r = rmdir(path);
	return r;
}

int main(int argc, char * args[]){
	char * dir = args[1];
	deleteDirectory(dir);
}
