/*
Scrivere un programma in linguaggio C che in sequenza:
    a) crei   2   pipe   e   un   figlio   (le   2   pipe   saranno   utilizzate   per   una   comunicazione
        bidirezionale tra padre e figlio);
    b)  dopo la creazione del figlio, il padre prenda in input dall’utente una stringa e la
        invii al figlio utilizzando la prima pipe; dopo aver ricevuto le risposte del figlio, le
        stampi e completi la sua esecuzione;
    c)  faccia controllare al figlio se esista una directory nella current working directory
        con   lo   stesso   nome   (si   utilizzino   le   system   call   che   permettono   di   leggere   il
        contenuto di una directory) ed invii al padre tale informazione.
    d)  Nel  caso  la directory esista,  faccia contare al  figlio il  numero di  file standard
        contenuti ed invii al padre la risposta;
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
 



int main(void){
    //creo le due pipe

    pid_t pid;

    int pd1[2];
    int pd2[2];

    char buffer[256];
    size_t nread;

    if(pipe(pd1)==-1 && pipe(pd2)==-1 ){
        perror("Errore nella creazione delle pipe\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid==-1){
        perror("Errore nella creazione nella fork\n");
        exit(EXIT_FAILURE);
    }

    if(pid>0){
        int count;
        close(pd1[0]);
        close(pd2[1]);
        scanf("%s",buffer);
        write(pd1[1],buffer,strlen(buffer));
        close(pd1[1]);
        wait(NULL);
        read(pd2[0],&count,sizeof(int));
        close(pd2[0]);

        printf("<%d>\n",count);

    }
    else{
        close(pd1[1]);
        close(pd2[0]);
        struct dirent *de;
        struct stat buf;
        int found= 0;
        DIR *dir;
        //siamo sicuri che c'è il carrattere di fine stringa
        nread = read(pd1[0],buffer,sizeof(buffer));
        buffer[nread] = '\0';
        close(pd1[0]);
        
        int count = 0;

        dir = opendir(".");
        while(de = readdir(dir)){
            stat(de->d_name,&buf);
            if(S_ISDIR(buf.st_mode)){
                if(strcmp(de->d_name,buffer)==0){
                    found = 1;
                    break;
                }
            }
            

        }

        dir = opendir(de->d_name);
        chdir(de->d_name);
        while(de = readdir(dir)){
            printf("%s\n",de->d_name);
            stat(de->d_name,&buf);
            if(S_ISREG(buf.st_mode)){
                count++;
            }
            
        }
        printf("count:<%d>\n",count);
        
        write(pd2[1],&count,sizeof(int));
        close(pd2[1]);
    }

    exit(0);

}