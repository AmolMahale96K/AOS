#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int i;

    pid = fork();  // Create a child process

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process started, PID: %d\n", getpid());
        for (i = 0; i < 5; i++) {
            printf("Child working: %d\n", i);
            sleep(1);  // Simulate work
        }
        printf("Child process exiting.\n");
    } else {
        // Parent process
        sleep(2);  // Let the child process work for 2 seconds

        printf("Parent suspending child process...\n");
        kill(pid, SIGSTOP);  // Suspend the child process

        sleep(3);  // Wait for 3 seconds

        printf("Parent resuming child process...\n");
        kill(pid, SIGCONT);  // Resume the child process

        wait(NULL);  // Wait for child process to finish
    }

    return 0;
}
