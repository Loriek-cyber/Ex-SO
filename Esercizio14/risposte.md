# Esercizio 1 Risposta

int main()
{
pid_t p;
fork();
p=fork();
if (p==0) p=fork();
if (p>0) printf("%d\n", getpid());
exit(0);
}

-> Questo è un semplice codice che ci da il professore

Allora andremmo passo a passo, nella prima riga specifichiamo una variabile di tipo *pid_t*(che sarebbe un un long int),
con il primo fork (Raddopiamo i processi) quindi da 1 passano a due, però non salviamo il codice.

allora visto che p non è inizializzato avrà un valore casuale quindi:

<fork()> [(p1) p = casuale] [(p2) p = casuale] 
<p = fork()> [(p1) p>0]/[(p2) p==0]              [(p3) p>0]/[(p4) p==0]

allora avremmo due processi con il pid che è uguale a 0, quindi ci saranno due processi che eseguirano il fork

quindi da quattro diventeranno 6, però ci saranno sempre due processi con il valore 0 e gli altri 4 avranno un valore maggiore di 0, visto che non conosciamo l'algoritmo di scheduling non sappiamo di preciso in che ordine saranno stampati

# Esercizio 2 Risposta

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
    write(1,"Prima",5);
    if((pid=fork())<0)
        exit(1);
    if(pid==0) {
        atexit(exit2);
        printf("Sono il figlio\n");
        write(1,array,5);
        exit(0);
    }
    wait(NULL);
    write(1,array,5);
    exit(0);
}

static void exit1(void) {
printf("Sono il primo handler\n"); }
static void exit2(void) {
printf("Sono il secondo handler\n"); }


Allora andiamo sempre passo dopo passo, creiamo un'array "Dopo\n", inseriamo nello stack degli exit exit1.
Con la write inseriamo la stringa "Prima" all'interno del buffer per l'stdout (Facciamo cosi poiche la stringa non contiene il carrattere \n).

Poi abbiamo un Error Handler per la fork, se la fork non è riuscita a creare un'altro processo allora restituira -1 uscendo cosi dal processo, Stampando a video "Sono il primo handler\n"

Andiamo oltre se il pid del processo attuale è uguale a 0 significa che è il figlio, allora, aggiungiamo allo
stack degli exit 'exit2', stampiamo a schermo "Sono il figlio\n", visto che nel buffer c'era "Prima", avremmo che:

<output>PrimaSono il figlio

In seguito scriveremo nel stdout l'array "Dopo\n", stampando 

<output>Dopo

con l'exit eseguiremo i due handler quindi

<output> Sono il secondo handler
<output> Sono il primo handler

visto che il secondo è alla cima dello stack sarà il primo ad essere eseguito. quindi il processo figlio
è terminato.

con wait(NULL) il processo padre aspetta che il processo figlio manda il segnale di terminazione.

stamperemo a terminale l'array un'altra volta quindi

<outpud>Dopo

con l'exit sara eseguito solamente il primo handler visto che quando è avvenuta la dupplicazione dei processi
solo quello c'era nello stack degli exit handler

<output> Sono il primo handler

allora l'output finale sarà:

<output>PrimaSono il figlio
<output>Dopo
<output> Sono il secondo handler
<output> Sono il primo handler
<outpud>Dopo
<output> Sono il primo handler



# Esercizio 3

Si consideri il seguente sorgente C attesa.c

int main(void){
    pause();
}

e si compili con il comando gcc attesa.c -o attesa
Si consideri il seguente codice C


<file> attesa , main.c

<main.c>
void handler(int);
int main(void){
    pid_t pid;
    signal(SIGTERM,handler);
    pid=fork();
    if(pid==0) {
        
        signal(SIGINT,handler);
        execl("./attesa", "attesa",NULL); }
    else 
        pause();
}


void handler(int signum){
    printf("Eccomi\n"); 
}

### Descrivere cosa accade compilando il programma ed eseguendo ./a.out nella shell:

Allora nella compilazione non ci sono problemi, il programma sarà eseguito senza errori, entrerrano in gioco entrambe le pause.

Però il problema sta nella gestione dei segnali del figlio visto che sono stati sostituiti con quelli di <attesa>, che non ha nessun gestore, quindi vengono ripristinati a default.

### (b) Supponendo che il processo padre abbia come pid 1237 ed il processo figlio abbia pid 1238,
### descrivere cosa accade se da una seconda shell si esegue, rispettivamente:

1) kill -SIGTERM 1237
2) kill -SIGTERM 1238
3) kill -SIGINT 1237
4) kill -SIGINT 1238


Allora 1237 è il pid del padre mentre 1238 è il pid del figlio

1) se mandiamo un -SIGTERM al padre sarà stampato a video la parola "Eccomi" poiche il padre possiede 
un signal handler per -SIGTERM.

2) il figlio che adesso avra lo stesso codice di attesa.c non avra più un signal handler per -SIGTERM
quindi sarà terminato senza fare niente.

3) il padre non possiede un segnal handler per -SIGINT quindi terminera senza fare niente

4) il figlio che prima teneva un segnal handler, non c'è l'ha più dopo la exec quindi non verà stampato niente




