#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid = -1;

// Handler for SIGCHLD (Child Termination)
void handle_sigchld(int sig) {
    int status;
    waitpid(child_pid, &status, WNOHANG);
    printf("Parent: Child process has terminated.\n");
    exit(0);
}

// Handler for SIGALRM (Alarm)
void handle_sigalrm(int sig) {
    printf("Parent: Child process timed out. Killing child process.\n");
    if (child_pid != -1) {
        kill(child_pid, SIGKILL);  // Forcefully kill the child process
    }
    exit(0);
}

int main() {
    // Set up the SIGCHLD handler to catch child termination
    signal(SIGCHLD, handle_sigchld);
    // Set up the SIGALRM handler to handle timeout
    signal(SIGALRM, handle_sigalrm);

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (child_pid == 0) {
        // Child process: Execute a command (e.g., sleep 10)
        execlp("sleep", "sleep", "10", (char *)NULL);
        perror("execlp failed");  // If execlp fails
        exit(1);
    } else {
        // Parent process: Start the timer for 5 seconds
        alarm(5);

        printf("Parent: Waiting for the child process to complete...\n");

        // Pause and wait for signals (either SIGCHLD or SIGALRM)
        while (1) {
            pause();  // Suspend until a signal is caught
        }
    }

    return 0;
}
