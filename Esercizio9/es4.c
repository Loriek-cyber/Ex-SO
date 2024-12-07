//Scrivi un programma che utilizza `execvp` per eseguire `date`.
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//execvp -> prende ovvimente il path file del programma da eseguire, in seguito prende un array di argomenti contenti pure
//i nomi dei file da passare al programma da eseguire

int main(void){
    char *argv[] = {"date", NULL};
    execvp("/bin/date",argv);
    return 0;
}