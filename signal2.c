#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static volatile sig_atomic_t alarms_count = 0;
static time_t start_time;

void alarm_handler(int signum) {
    (void)signum;
    printf("Hello World!\n");
    alarms_count++;
    alarm(5);                      /* keep ticking every 5 seconds */
}

void sigint_handler(int signum) {
    (void)signum;
    time_t end_time = time(NULL);
    long secs = (long)(end_time - start_time);
    printf("\nTuring was right!\n");
    printf("Total alarms: %d\n", (int)alarms_count);
    printf("Total time: %ld seconds\n", secs);
    _exit(0);                      /* async-signal-safe exit */
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

    alarm(5);

    for (;;) {
        pause();                   /* sleep until a signal is handled */
    }
}