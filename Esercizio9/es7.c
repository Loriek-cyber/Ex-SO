//Implementa un programma che esegue `/bin/ls` usando `execl`, passando il flag `-l`.

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    execl("/bin/ls","ls","-l",NULL);
}