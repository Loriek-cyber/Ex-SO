//Usa `execlp` per eseguire il comando `pwd` (senza specificare il percorso assoluto).
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t pid;
    
    pid = fork();

    if(pid==0)
        execlp("/bin/pwd","pwd",NULL);
    wait(NULL);
    printf("All worked as intented");
    return 0;
}