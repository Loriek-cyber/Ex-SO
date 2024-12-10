#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void exit1(void);
void exit2(void);

int main(void) {
    int pid;
    char array[]="Dopo\n";
    atexit(exit1);
    write(1,"Prima",5);
    if((pid=fork())<0)
        exit(1);
    if(pid==0) {
        atexit(exit2);
        printf("Sono il figlio\n");
        write(1,array,5);
        exit(0);
    }
    wait(NULL);
    write(1,array,5);
    exit(0);
}

void exit1(void) {
printf("Sono il primo handler\n"); 
}
void exit2(void) {
printf("Sono il secondo handler\n"); }