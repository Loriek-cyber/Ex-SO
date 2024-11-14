#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int isVowel(char c) {
    c = (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; 
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}



int main(void){
    char buffer [1024];
    char *p;

    long int rb;
    
    pid_t pd1;
    pid_t pd2;

    int fd2,fd3;

    int fd = open("file.txt",O_RDWR);
    if(fd<0)
        exit(-1);

    

    //variabili per i due processi
    if(fork()>0){
        if(fork()==0){
            pd2 = getpid();    // Processo figlio 2
            printf("Questo è il processo figlio 2\n");
            fd2 =open("consonanti.txt",O_CREAT|O_RDWR,0644);
            while(rb = read(fd,buffer,1)){
                p = buffer;
                while(*p++){
                    if(!isVowel(*p))
                        write(fd2,p,1);
            }    
            }       
        }
        
    }
    else{
        pd1 = getpid();         // Processo figlio 1
        printf("Questo è il processo figlio 1\n");
        fd2 =open("vocali.txt",O_CREAT|O_RDWR,0644);
        while(rb = read(fd,buffer,1)){
            p = buffer;
            while(*p++){
                if(isVowel(*p))
                    write(fd2,p,1);
            }
        } 
    }



    exit(0);
    
}