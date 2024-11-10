#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler function for SIGALRM
void handle_alarm(int sig) {
    printf("Alarm is fired.\n");
}

int main() {
    pid_t pid;

    // Set up the signal handler for SIGALRM in the parent process
    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        // Sleep for 2 seconds to ensure parent is waiting for the signal
        sleep(2);

        // Get parent process ID
        pid_t parent_pid = getppid();

        // Send SIGALRM signal to parent process
        if (kill(parent_pid, SIGALRM) == -1) {
            perror("Failed to send SIGALRM to parent");
            exit(EXIT_FAILURE);
        }

        printf("Child: Sent SIGALRM signal to parent.\n");
        exit(EXIT_SUCCESS);
    }
    else {
        // Parent process
        printf("Parent: Waiting for alarm signal...\n");

        // Parent waits for the signal
        // Using pause() will suspend the parent process until any signal is received
        pause();

        // Optionally, wait for the child process to terminate
        if (wait(NULL) == -1) {
            perror("Failed to wait for child");
            exit(EXIT_FAILURE);
        }

        printf("Parent: Child process has terminated.\n");
    }

    return 0;
}
