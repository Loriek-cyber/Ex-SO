#   Esercizio 1.1

Scrivere un programma in linguaggio C che prenda come parametro sulla riga di
comando il nome di un file e stampi il numero di vocali contenute nel file.
Si   supponga   di   compilare   tale   programma   e   di   assegnargli   il   nome
CONTA_VOCALI

'''
int isV(char c) {
    // Controlla sia le minuscole che le maiuscole
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main(int argc, char*argv[]){
    if(argc!=2){
        printf("%s <nome file>",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int conta_vocali = 0;
    int fd = open(argv[1],O_RDONLY);
    char c;

    if(fd==-1){
        perror("Errore nell'appertura del file o file innesistente\n");
        exit(EXIT_FAILURE);
    }

    while(read(fd, &c,1)){
        conta_vocali+=isV(c);
    }
    printf("%d",);
}
'''

Un semplice codice per contare le vocali con la read:

# Esercizio 1.2

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
        execl("./conta","conta",buffer,NULL);
    }

    exit(0);

}


# Esercizio 2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void exit1(void);
void exit2(void);
int main(void) {
int pid;
char array[]="Dopo\n";
atexit(exit1);
printf("Prima");
pid=fork();
if(pid==0) {
  atexit(exit2);
  printf("Sono il figlio");
  write(1,array,5);
  _exit(0);
  }
wait(NULL);
printf("Sono il padre\n");
write(1,array,5);
printf("Fine esecuzione");
exit(0);
}
void exit1(void) {
  printf("Sono il primo handler\n");
}
void exit2(void) {
  printf("Sono il secondo handler\n");
}
Spiegare quale sarà l'output del programma, distinguendo tra processo padre e 
processo figlio, giustificando in maniera esaustiva la risposta.


---------------------------------------

Allora per prima cosa definiamo una variabile pit_t(long int) di nome pid, inseriamo nello stack degli exit la funzione exit2, visto che la stringa da stampare non contine il carrattere \n, la inseriamo nel buffer del processo, allora cloniamo i processi con la fork, 

Il processo figlio con pid = 0, aggiungera alla sua stack degli exit la funzione exit2, poi stampera quello che era nel buffer in più la stringa "Sono il figlio", in seguito stampera sempre poiche, la string "Dopo\n", ha il carattere  \n.

Con la _exit(0) eseguira tutti gli exit nello stack, prima di terminare.


Passiamo il padre che fino a questo momento aveva aspettato suo figlio che finiva con la wait(NULL), anche lui 
avra nel buffer la frase "Prima", con la printf("SOno il padre\n"), stampera anche lui la stringa nel buffer e l'altra.

Stampera anche la stringa "Dopo\n", in seguito inserira nel buffer "Fine esecuzione", poi eseguira l'unica
exit che stava nel suo stack quindi exit1, allora il risultato finale dell'output sarà:
