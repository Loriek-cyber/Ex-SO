//Implementa un programma che esegue `grep` su un file specificato.
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>


int main(int argc, char*argv[]){
    if(argc!=3){
        printf("Syntax Erorr: %s <pattern> <file>\n",argv[0]);
        return -1;
        }
    return execl("/bin/grep","grep",argv[1],argv[2],NULL);
}