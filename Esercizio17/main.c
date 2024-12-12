
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
printf("Prima");
pid=fork();
if(pid==0) {
  atexit(exit2);
  printf("Sono il figlio\n");
  write(1,array,5);
  _exit(0);
  }
wait(NULL);
printf("Sono il padre");
write(1,array,5);
printf("Fine esecuzione\n");
_exit(0);
}
void exit1(void) {
  printf("Sono il primo handler\n");
}
void exit2(void) {
  printf("Sono il secondo handler\n");
}