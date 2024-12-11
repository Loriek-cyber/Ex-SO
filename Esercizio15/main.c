/*
Successivamente scrivere un secondo programma in linguaggio C che in sequenza:
    •crei   2   pipe   e   un   figlio   (le   2   pipe   saranno   utilizzate   per   una   comunicazione
    bidirezionale tra padre e figlio);
    •dopo la creazione del figlio, il padre prenda in input dall’utente un nome di file
    e lo invii al figlio utilizzando la prima pipe; dopo aver ricevuto la risposta del
    figlio, la stampi e completi la sua esecuzione;
    •faccia   eseguire   al   figlio,   utilizzando   una   delle   funzioni   exec,   il   comando
    “CONTA_VOCALI” utilizzando come argomento il nome del file e utilizzando
    la seconda pipe per inviare al padre il numero di vocali contenute nel file.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>


int main(void){
    int fd1[2];
    int fd2[2];
    
    
    if(pipe(fd1)<0){
        perror("Errore nella creazione della pipe n1.\n");
        exit(EXIT_FAILURE);
    }
    
    if(pipe(fd2)<0){
        perror("Errore nella creazione della pipe n1.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    char rs[20];

    pid_t pid = fork();
    if(pid<0){
        perror("Errore nella creazione dei processi.\n");
    }

    if(pid>0){
        close(fd1[0]); //closing first read pipe
        scanf("%s",buffer);
        write(fd1[1],buffer,sizeof(buffer));

        wait(NULL);
        read(fd2[0],rs,20);
        printf("il numero di vocale al quale è arrivato secondo il figlio %s\n",rs);
    }

    if(pid ==0){
        close(fd1[1]); //closing reading pipe on the child process
        close(fd2[0]); //closing reading pipe;
        read(fd1[0],buffer,sizeof(buffer));
        dup2(fd2[1],STDOUT_FILENO);
        execl("./conta","conta","text.txt",NULL);
    }

    exit(0);

}