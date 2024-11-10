#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();  // Create a child process

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process: Exiting with status 42\n");
        exit(42);  // Exit with status 42
    } else {
        // Parent process
        wait(&status);  // Wait for the child process to terminate

        if (WIFEXITED(status)) {
            // If the child process exited normally
            printf("Parent process: Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            // If the child process did not exit normally
            printf("Parent process: Child did not exit normally\n");
        }
    }

    return 0;
}
