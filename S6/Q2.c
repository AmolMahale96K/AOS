#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

int main() {
    int n, i;
    pid_t pid;
    struct tms tms_start, tms_end;
    clock_t start, end;
    double user_time = 0, system_time = 0;

    printf("Enter the number of child processes to create: ");
    scanf("%d", &n);

    // Record the start time
    start = times(&tms_start);

    for (i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process: Simulate some work with sleep
            sleep(1);  // Each child sleeps for 1 second
            exit(0);   // Child process terminates
        }
    }

    // Parent process: Wait for all child processes to finish
    for (i = 0; i < n; i++) {
        wait(NULL);
    }

    // Record the end time
    end = times(&tms_end);

    // Calculate total time spent by children in user and kernel modes
    user_time = (double)(tms_end.tms_cutime - tms_start.tms_cutime) / sysconf(_SC_CLK_TCK);
    system_time = (double)(tms_end.tms_cstime - tms_start.tms_cstime) / sysconf(_SC_CLK_TCK);

    printf("Total cumulative time spent by children:\n");
    printf("User time: %.2f seconds\n", user_time);
    printf("System (kernel) time: %.2f seconds\n", system_time);

    return 0;
}
