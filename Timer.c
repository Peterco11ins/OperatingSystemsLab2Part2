#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signum) {
    (void)signum;
    printf("Hello World!\n");
    alarm(5);                      /* schedule the next one */
}

int main(void) {
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    alarm(5);

    /* wait for signals forever; after each SIGALRM, print from main */
    for (;;) {
        pause();                   /* returns after a signal is handled */
        printf("Turing was right!\n");
        fflush(stdout);
    }
    /* not reached */
}