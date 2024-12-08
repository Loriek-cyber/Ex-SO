//Scrivi un programma che usa `execve` per modificare l'ambiente e poi eseguire `env`
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>


int main(void){

    char *new_env[] = {
        "MYVAR1=Hello",
        "MYVAR2=World",
        "PATH=/usr/bin:/bin",
        NULL
    };

    char *argv[] = {"env",NULL};
    return execve("/bin/env",argv,new_env);
}