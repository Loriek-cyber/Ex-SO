//Crea un programma che utilizza `pipe` per collegare due processi e `execvp` per eseguire comandi.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//colleghiamo pwd e ls

int main() {
    //Creamo le due Pipe
    int pipefd[2];
    pipe(pipefd); 

    //Creamo i processi
    pid_t pid;
    pid = fork();

    if(pid == 0){
        //Processo figlio
        close(pipefd[0]); //Chiudiamo la lettura
        dup2(pipefd[1], STDOUT_FILENO); //Ridireziona la scrittura
        execvp("pwd",NULL);
        close(pipefd[1]); //Chiudiamo la Scrittura
    }

    wait(NULL);
    close(pipefd[1]); //Chiudiamo la Scrittura
    char buffer[1024];
    long int readedc = read(pipefd[0], buffer, 1024);
    buffer[readedc-1] = '\0';
    execl("/bin/ls","ls",buffer,NULL);
}


