#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid = 0; // Global variable to store child process ID

void handle_sigchld(int sig) {
    int status;
    waitpid(child_pid, &status, 0); // Wait for the child process to terminate
    if (WIFEXITED(status)) {
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child was terminated by signal %d\n", WTERMSIG(status));
    }
    exit(0); // Parent process exits after handling child termination
}

void handle_sigalrm(int sig) {
    printf("Child process exceeded time limit. Killing child process.\n");
    kill(child_pid, SIGKILL); // Terminate child if it exceeds 5 seconds
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    // Set up signal handlers
    signal(SIGCHLD, handle_sigchld); // Handle child termination
    signal(SIGALRM, handle_sigalrm); // Handle alarm signal

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process: execute the command
        execvp(argv[1], &argv[1]);
        perror("execvp"); // Only reached if execvp fails
        exit(1);
    } else {
        // Parent process: set alarm and wait
        alarm(5); // Set an alarm for 5 seconds

        // Wait for child process to finish
        pause(); // Wait for any signal (SIGCHLD or SIGALRM)
    }

    return 0;
}
