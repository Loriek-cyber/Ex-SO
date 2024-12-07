//Scrivi un programma che utilizza execl per eseguire il comando /bin/ls senza argomenti.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

void exit1(){}


int main(int argc, char *argv[]) {
    
    atexit(exit1);
    if(argc != 1){
        printf("Errore: numero di argomenti non corretto\n");
        exit(EXIT_FAILURE);}
    
    pid_t pid;
    
    //Gestione errori della creazione del processo 
    pid=fork();
    if(pid==-1)
        exit(EXIT_FAILURE);
    
    if(pid==0)
        execl("/bin/ls","ls",NULL);
    wait(NULL);

    printf("Il programma è terminato\n");
    exit(0);
}