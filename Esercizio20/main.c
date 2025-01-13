#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(void){

    char *str = "dopo";
    write(1,str,4);
    write(1,str,4);
    _exit(0);

}