//Usa `execve` per eseguire `/bin/uname` con l'argomento `-a`.
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void){
    char *argv[] = {"uname"};
    char *arg[] = {"-a",NULL}; // -> quando metto gli argomenti devo sempre inserire NULL alla fine
    execve("/bin/uname", argv,arg);
}