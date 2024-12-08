//Usa `fork` per creare due processi figli che eseguono comandi diversi con `execlp`.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(void){
    pid_t pid = fork(); //integrazione con due processi
    if(pid==0)
        execlp("/bin/ls","ls",NULL);
    wait(NULL);
    execlp("/bin/echo","echo","hello",NULL);
}