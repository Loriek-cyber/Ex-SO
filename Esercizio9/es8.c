//Usa `execl` per eseguire `ls` su una directory specifica.
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc!=2){
        printf("Errore nell'utilizzo del programma \n");
        return -1;
    }

    if(execl("/bin/ls","ls",argv[1],NULL)==-1){
        printf("Errore nell'esecuzione del comando \n");
    }
    return -1;
    
}