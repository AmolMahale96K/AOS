#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

pid_t child_pid; // To store the child's PID

// Signal handler for SIGCHLD (child process termination)
void child_handler(int signum) {
    int status;
    waitpid(child_pid, &status, 0);  // Wait for the child to terminate
    printf("Child process terminated. Exit status: %d\n", WEXITSTATUS(status));
}

// Signal handler for SIGALRM (timeout)
void alarm_handler(int signum) {
    printf("Timeout! Child process did not complete in time. Killing child...\n");
    kill(child_pid, SIGKILL);  // Kill the child process if it didn't complete in time
}

int main() {
    pid_t pid;
    char *command[] = {"/bin/ls", "-l", NULL};  // Example command to run (ls -l)

    // Set up signal handler for child termination (SIGCHLD)
    signal(SIGCHLD, child_handler);

    // Set up signal handler for timeout (SIGALRM)
    signal(SIGALRM, alarm_handler);

    pid = fork();  // Create a child process

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process started with PID %d\n", getpid());
        execvp(command[0], command);  // Replace the child process with the command
        perror("execvp");  // If execvp fails
        exit(1);
    } else {
        // Parent process
        child_pid = pid;  // Store the child's PID
        alarm(5);  // Set alarm for 5 seconds

        // Wait for the child process to terminate or be killed
        printf("Parent waiting for child to complete...\n");
        pause();  // Wait for signals
    }

    return 0;
}
