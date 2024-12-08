//Implementa un programma che esegue `cat` su un file specifico utilizzando `execv`.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc!=2){
        printf("Usage: %s <file>\n", argv[0]);
        return -1;
    }
    char *args[] = {"cat", argv[1], NULL};
    return execv("/bin/cat", args);
}
