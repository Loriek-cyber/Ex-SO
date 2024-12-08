//Utilizza `execv` per eseguire `echo` e stampa una sequenza di tre parole.


#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void){
    char *argv [] = {"echo", "Ciao", "Mondo","Come", "va?", NULL};
    execv("/bin/echo",argv);
}