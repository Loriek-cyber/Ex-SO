#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void my_handler(int signo) {
    printf("tu stronzo osi usare CTRL+C su di me? Va bene me ne vado %d\n", signo);
    exit();
}

int main() {
    signal(SIGINT, my_handler); // Assigns SIGINT to the handler
    while (1) {
        pause(); // Waits for a signal
    }
    return 0;
}
