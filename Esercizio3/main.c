#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define FILENAME "file.txt"

int main(void){
    int fd;
    long int count=0;
    char buffer[1];
    struct stat buf;
    struct dirent *de;
    DIR* dir;
    dir = opendir(".");
    if(dir==NULL)
        perror("opendir");
    
    while(de = readdir(dir)){
        if(stat(de->d_name,&buf)){
            perror("stat");
        }
        if(strcmp(de->d_name,"a.out")==0)
            continue;
        if(S_ISREG(buf.st_mode)){
            fd = open(de->d_name,O_RDONLY);
            if(fd==-1){
                perror("open");
                }
            while(read(fd,buffer,1)){
                if(*buffer=='\n')
                    count ++;
            }
            close(fd);
        }
    }
    printf("Il numero di  \\n è %ld\n",count);
    closedir(dir); 
}

