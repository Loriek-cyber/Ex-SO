#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    int pipefd[2]; // Array per i file descriptor della pipe: pipefd[0] per leggere, pipefd[1] per scrivere
    pid_t pid;

    char buffer[256];

    // Creazione della pipe
    if (pipe(pipefd) == -1) {
        perror("Errore nella creazione della pipe");
        exit(EXIT_FAILURE);
    }

    // Creazione del processo figlio
    pid = fork();

    if (pid < 0) {
        perror("Errore nella fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo figlio
        char primo_file[100];
        char secondo_file[100];
        close(pipefd[1]); // Chiude l'estremità di scrittura della pipe

        char buffer[128];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("Errore nella lettura dalla pipe");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0'; // Assicura che la stringa sia terminata con null
        //continua  
        sscanf(buffer,"%s %s",primo_file,secondo_file);
        
        int fd1= open(secondo_file,O_CREAT  | O_WRONLY,0644);

        dup2(fd1,STDOUT_FILENO);
        execl("/bin/cat","cat",primo_file,NULL);



        close(pipefd[0]); // Chiude l'estremità di lettura della pipe
    } else { // Processo padre
        close(pipefd[0]); // Chiude l'estremità di lettura della pipe
        
        char secondo_file[100];

        printf("inserisci i seguenti file\n");
        scanf("%s",buffer);
        scanf("%s",secondo_file);
        
        strcat(buffer," ");
        strcat(buffer,secondo_file);
        

        write(pipefd[1], buffer, strlen(buffer));

        close(pipefd[1]); // Chiude l'estremità di scrittura della pipe

        // Aspetta che il processo figlio termini
        wait(NULL);
    }

    return 0;
}
