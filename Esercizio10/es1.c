//Usa `fork` per creare un processo figlio che esegue `/bin/ls` con `execl`.

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(void){
	
	pid_t id = fork();
	if(id==0)
		execl("/bin/ls","ls",NULL);
	wait(NULL);
	printf("Il commando ls è stato eseguito con successo nel figlio\n");
}
