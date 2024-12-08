//Usa `fork` e `execvp` per creare un processo figlio che esegue il comando `date`.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>


int main(void){
    pid_t pid;
    char *arg[] = {"date", NULL};
    pid = fork(); //crea un processo figlio -> senza controllo visto che sono nell'ambiente princiiapele
    if(pid == 0){
        //figlio
        execvp(arg[0], arg); //esegue il comando date
    }
    wait(NULL);
    printf("processo pradre\n");
}