//Utilizza execv per eseguire /bin/echo e stampa il messaggio "Hello, World!".

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>


int main() {
    
    pid_t pid;
    char *args[] = {"echo", "Hello", "World", NULL };
    
    pid=fork();
    //gestione dell'errore del pid
    if(pid==-1)
        exit(EXIT_FAILURE);

    if(pid==0){
        if (execv("/bin/echo", args) == -1) {
            perror("execv failed");
            exit(EXIT_FAILURE);
    }
    }
}