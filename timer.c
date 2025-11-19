// timer.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static volatile sig_atomic_t ready_to_print = 0;
static volatile sig_atomic_t alarms_count = 0;
static time_t start_time;

/* called every second */
void alarm_handler(int signum) {
    (void)signum;
    printf("Hello World!\n");
    fflush(stdout);

    alarms_count++;
    ready_to_print = 1;

    /* schedule next alarm in 1 second */
    alarm(1);
}

/* called on Ctrl-C */
void sigint_handler(int signum) {
    (void)signum;
    time_t end_time = time(NULL);
    long secs = (long)(end_time - start_time);

    printf("Turing was right!\n");
    printf("Total alarms: %d\n", (int)alarms_count);
    printf("Total time: %ld seconds\n", secs);

    _exit(0);   /* async-signal-safe exit */
}

int main(void) {
    start_time = time(NULL);

    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal SIGALRM");
        return 1;
    }
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal SIGINT");
        return 1;
    }

    /* first alarm after 1 second */
    alarm(1);

    for (;;) {
        pause();                    /* sleep until SIGALRM or SIGINT */

        if (ready_to_print) {
            printf("Turing was right!\n");
            fflush(stdout);
            ready_to_print = 0;
        }
    }

    return 0;
}