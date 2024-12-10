#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


void handler(int);
int main(void){
    pid_t pid;
    signal(SIGTERM,handler);
    pid=fork();
    
    printf("%d\n",getpid());

    if(pid==0) {
        signal(SIGINT,handler);
        execl("./attesa", "attesa",NULL); }
    else 
        pause();
}
void handler(int signum)
{printf("Eccomi\n"); }