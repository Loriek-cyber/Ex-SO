#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BSize 1024

int strlen(char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;}
    return len;
}

void println(char *str) {
    write(STDOUT_FILENO,str,strlen(str));
    write(STDOUT_FILENO,"\n",1);
}


int main(int argc, char *argv[]) {
    

}