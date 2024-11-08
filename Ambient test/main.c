//questo è un codice per testare l'ambiente di sviluppo il classico hello world scritto con le system calls


#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int strlen(char *s){
    int i = 0;
    while(*s++)i++;
    return i;
}

int println(char *s){
    return write(STDOUT_FILENO,s,strlen(s));
}


int perror(char *s){
    return write(STDERR_FILENO,s,strlen(s));
}


int main(void){
    if(println("hello World!\n")==-1)
        perror("Il programma non è riuscito a scrivere niente");
}