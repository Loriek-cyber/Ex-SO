//Esegui `whoami` usando `execlp` e cattura eventuali errori.

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    execlp("/bin/whoami","whoami",NULL);
}