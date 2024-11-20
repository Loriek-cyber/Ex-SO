#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BSize 256

// Funzione per stampare una stringa seguita da una nuova riga
void println(char *str) {
    write(STDOUT_FILENO, str, strlen(str));
    write(STDOUT_FILENO, "\n", 1);
}

// Funzione per leggere una riga dal file
// Restituisce il numero di caratteri letti nella riga
int read_line(int fd, char *Line1) {
    ssize_t nread;
    char BUFFER;
    int index1 = 0;

    while ((nread = read(fd, &BUFFER, 1)) > 0) {
        if (index1 < BSize - 1) { // Protezione contro il buffer overflow
            Line1[index1] = BUFFER;
            index1++;
        }
        if (BUFFER == '\n') { // Fine della riga
            break;
        }
    }

    if (nread == -1) {
        perror("Errore lettura file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    Line1[index1] = '\0'; // Terminazione della stringa
    return index1; // Numero di caratteri letti
}

// Funzione per gestire l'apertura del file
int open_file(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Errore apertura file");
        exit(EXIT_FAILURE);
    }
    return fd;
}

// Funzione per rimuovere righe duplicate
void remove_duplicate(int fd, char *Line) {
    long int stime = lseek(fd, 0, SEEK_CUR); // Salva la posizione corrente
    long int nreaded;
    char Line1[BSize];
    
    // Creiamo un buffer per la lettura delle righe
    while ((nreaded = read_line(fd, Line1)) > 0) {
        // Se la riga letta è uguale a quella da rimuovere
        if (strcmp(Line, Line1) == 0) {
            // Spostiamo il puntatore indietro per sovrascrivere la riga duplicata
            lseek(fd, -nreaded, SEEK_CUR);
            // Scriviamo uno spazio per "rimuovere" la riga
            for (int i = 0; i < nreaded ; i++)
            {
                write(fd, "\0", 1);
            }
            
             // Scriviamo un carattere nullo per rimuovere la riga
            // Possiamo anche voler ripristinare il puntatore per continuare la lettura
        }
    }
    
    lseek(fd, stime, SEEK_SET); // Ripristina la posizione iniziale
}

// Funzione per leggere e stampare fino a 100 righe
void process_file(int fd) {
    char Line1[BSize];
    
    for (int i = 0; i < 100; i++) {
        memset(Line1, 0, sizeof(Line1)); // Inizializza il buffer
        int chars_read = read_line(fd, Line1);
        if (chars_read == 0) {
            break; // Fine del file
        }
        println(Line1); // Stampa la riga
        remove_duplicate(fd, Line1); // Rimuove le righe duplicate
    }
}

// Funzione principale
int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Numero di argomenti errato");
        exit(EXIT_FAILURE);
    }

    int fd = open_file(argv[1]); // Apre il file
    process_file(fd);            // Legge e stampa le righe
    close(fd);                   // Chiude il file

    return 0;
}