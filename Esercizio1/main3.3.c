#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


int glob = 10;

int main(void){
    int var = 100;
    pid_t pippo;
    printf("prima della fork\n");
    pippo = fork();
    if(pippo==0){glob++;var++;}
    else sleep(2);

    printf("pid=%d,glob=%d, var=%d\n",getpid(),glob,var);
    return 0;
}