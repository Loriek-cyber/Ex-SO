//Crea un programma che esegue `cp` per copiare un file in un'altra directory.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc!=3){
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return -1;
    }

    return execl("/bin/cp","cp",argv[1],argv[2],NULL);
}