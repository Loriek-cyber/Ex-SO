//Scrivi un programma che esegue `touch` per creare un nuovo file.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc!=2){
        printf("Usage: %s <nome_file>\n", argv[0]);
        return -1;
    }

    return execl("/bin/touch", "touch", argv[1], NULL);
}