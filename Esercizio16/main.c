#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int main(void){
    int fd[2];
    char buffer[256];
    if(pipe(fd)<0){
        perror("Errore nella creazione del file\n");
        exit(-1);
    }
    int n;
    pid_t pid = fork();

    if(pid == 0){
        close(fd[1]); // chiudiamo la read
        n = read(fd[0],buffer,sizeof(buffer));
        buffer[n-1]='\0';
        close(fd[0]);
        execl("./conta","conta",buffer,NULL);
    }
    
    close(fd[0]); //chiudiamo la pipe di scrittura;
    read(STDIN_FILENO,buffer,sizeof(buffer));
    write(fd[1],buffer,strlen(buffer));
    close(fd[1]);

    exit(0);

}