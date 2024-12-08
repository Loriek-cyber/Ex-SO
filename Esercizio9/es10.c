//Scrivi un programma che usa `execvp` per eseguire `man` e visualizzare la pagina del comando `ls`.

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
	char *argv[]={"man","ls",NULL};
	return execvp("/bin/man",argv);	
}

