#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc<2){
        printf("Usage: %s <command>\n", argv[0]);
        return -1;
    }
    return execvp(argv[1],&argv[1]);
}