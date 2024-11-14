#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(void){
    
    //variabili per i due processi
    pid_t p1 = fork();
    pid_t p2;

    
    

    if (p1 > 0){
        p2 = fork();}
}