/*Scrivere un programma in linguaggio C che prenda come parametro sulla riga di
comando il nome di un file e stampi il numero di vocali contenute nel file.
Si   supponga   di   compilare   tale   programma   e   di   assegnargli   il   nome
CONTA_VOCALI*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>


int isV(char c) {
    // Controlla sia le minuscole che le maiuscole
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main(int argc, char*argv[]){
    if(argc!=2){
        printf("%s <nome file>\n",argv[0]);
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
    printf("%d\n",conta_vocali);
}