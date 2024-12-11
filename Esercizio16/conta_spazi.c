#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Syntax Error:%s <filename>",argv[0]);
        exit(-1);
    }

    int n_spazi = 0;
    char c;
    int fd = open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("File not found or dosn't exist\n");
        exit(-1);
    }

    while(read(fd,&c,1)){
        if(c==' ')
            n_spazi++;
    }
    printf("%d\n",n_spazi);
}