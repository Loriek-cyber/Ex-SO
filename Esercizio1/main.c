#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void){
    char c, cwd[100];
    int fd;
    struct stat buf;
    struct dirent *drn;
    DIR *dp;

    getcwd(cwd,sizeof(cwd));

    if((dp = opendir(cwd))==NULL){
        perror("Non è stato possibile aprire la cartella\n");
    }

    while (drn = readdir(dp)){
        
    }
     

}