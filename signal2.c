// signal2.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* set by handler when an alarm fires */
static volatile sig_atomic_t ready_to_print = 0;

void alarm_handler(int signum) {
    (void)signum;                  /* unused */
    printf("Hello World!\n");
    fflush(stdout);
    ready_to_print = 1;            /* tell main to print Turing message */
}

int main(void) {
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    /* first alarm after 5 seconds */
    alarm(5);

    /* run forever */
    for (;;) {
        /* wait for a signal (SIGALRM) */
        pause();

        if (ready_to_print) {
            printf("Turing was right!\n");
            fflush(stdout);
            ready_to_print = 0;

            /* schedule the next alarm in 5 seconds */
            alarm(5);
        }
    }

    return 0;
}