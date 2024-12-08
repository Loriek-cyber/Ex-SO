//Crea un programma che utilizza `execlp` per eseguire un comando passato come argomento al programma.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //mi serve solo come commando
    if(argc!=2){
        printf("Usage: %s <command>\n",argv[0]);
        return -1;
    }

    char env[20] = "/bin/";
    strcat(env,argv[1]);
    return execlp(env,argv[1],NULL);
}