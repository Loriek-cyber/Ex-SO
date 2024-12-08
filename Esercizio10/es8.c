//Esegui `rm` per eliminare un file creato in precedenza.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc!=2){
        printf("Usage: %s <nome_file>\n", argv[0]);
        return -1;
    }
    return execl("/bin/rm","rm",argv[1],NULL);
}