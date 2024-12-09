//Implementa un programma che usa `fork` per eseguire `ls` e `pwd` in due processi distinti.

#include<unistd.h>
#include<sys/wait.h>

int main(void){
	
	int pid = fork();
	if(pid==0){
		execl("/bin/pwd","pwd",NULL);
		write(STDOUT_FILENO,"\n",1);
	}
	wait(NULL);
	execl("/bin/ls","ls",NULL);
}
