#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* use a flag set by the handler to let main know the alarm fired */
volatile sig_atomic_t done = 0;

void alarm_handler(int signum) {
    (void)signum;                  /* unused */
    printf("Hello World!\n");
    done = 1;                      /* signal main loop to continue */
}

int main(void) {
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    alarm(5);                      /* deliver SIGALRM in 5 seconds */

    /* busy-wait or you can use pause(); here we stick to spec */
    while (!done) { /* spin until handler runs */ }

    printf("Turing was right!\n");
    return 0;
}