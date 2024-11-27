#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BSize 256

void println(char *str) {
    write(STDOUT_FILENO, str, strlen(str));
    write(STDOUT_FILENO, "\n", 1);
}

int read_line(int fd, char *Line1) {
    ssize_t nread;
    char BUFFER;
    int index1 = 0;

    while ((nread = read(fd, &BUFFER, 1)) > 0) {
        if (index1 < BSize - 1) { 
            Line1[index1] = BUFFER;
            index1++;
        }
        if (BUFFER == '\n') { 
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


void remove_duplicate(int fd, char *Line) {
    long int stime = lseek(fd, 0, SEEK_CUR); 
    long int nreaded;
    char Line1[BSize];
    
    while ((nreaded = read_line(fd, Line1)) > 0) {
        if (strcmp(Line, Line1) == 0) {
            lseek(fd, -nreaded, SEEK_CUR);
            for (int i = 0; i < nreaded ; i++)
            {
                write(fd, "\0", 1);
            }
        }
    }
    
    lseek(fd, stime, SEEK_SET); 
}

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