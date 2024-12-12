#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int pipefd[2]; // Array per i file descriptor della pipe: pipefd[0] per leggere, pipefd[1] per scrivere
    pid_t pid;

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
        close(pipefd[1]); // Chiude l'estremità di scrittura della pipe

        char buffer[128];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("Errore nella lettura dalla pipe");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0'; // Assicura che la stringa sia terminata con null
        printf("Il figlio ha ricevuto: %s\n", buffer);

        close(pipefd[0]); // Chiude l'estremità di lettura della pipe
    } else { // Processo padre
        close(pipefd[0]); // Chiude l'estremità di lettura della pipe

        const char *message = "Ciao dal processo padre!";
        write(pipefd[1], message, strlen(message));

        close(pipefd[1]); // Chiude l'estremità di scrittura della pipe

        // Aspetta che il processo figlio termini
        wait(NULL);
    }

    return 0;
}
