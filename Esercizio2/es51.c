#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SEM_FILE "semaforo.tmp"

void RedSem() {
    while (open(SEM_FILE, O_CREAT | O_EXCL, 0644) == -1);
}

void GreenSem() {
    unlink(SEM_FILE);
}

int isVowel(char c) {
    c = (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void Consonant(int fd) {
    char s;
    int fd2 = open("consonant.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd2 == -1) {
        perror("Errore apertura consonant.txt");
        exit(1);
    }

    while (read(fd, &s, 1) > 0) {
        RedSem();
        if (!isVowel(s) && ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))) {
            write(fd2, &s, 1);
        }
        GreenSem();
    }

    close(fd2);
}

void Vocals(int fd) {
    char s;
    int fd2 = open("vocal.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd2 == -1) {
        perror("Errore apertura vocal.txt");
        exit(1);
    }

    while (read(fd, &s, 1) > 0) {
        RedSem();
        if (isVowel(s)) {
            write(fd2, &s, 1);
        }
        GreenSem();
    }

    close(fd2);
}

int main(void) {
    pid_t pd1, pd2;

    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Errore apertura file.txt");
        exit(1);
    }

    pd1 = fork();
    if (pd1 == -1) {
        perror("Errore fork");
        exit(1);
    }

    if (pd1 == 0) {
        Vocals(fd);
        close(fd);
        exit(0);
    }

    pd2 = fork();
    if (pd2 == -1) {
        perror("Errore fork 2");
        exit(1);
    }

    if (pd2 == 0) {
        Consonant(fd);
        close(fd);
        exit(0);
    }

    // Padre attende i figli
    close(fd);
    wait(NULL);
    wait(NULL);

    printf("Copia completata.\n");

    return 0;
}
