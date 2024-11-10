#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2]; // Pipe file descriptors
    pid_t pid1, pid2;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork first child for ls -l
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        // Child process 1: ls -l
        close(pipefd[0]);  // Close read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);  // Execute ls -l
        perror("execlp");  // If exec fails
        exit(1);
    }

    // Fork second child for wc -l
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        // Child process 2: wc -l
        close(pipefd[1]);  // Close write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe
        close(pipefd[0]);

        execlp("wc", "wc", "-l", (char *)NULL);  // Execute wc -l
        perror("execlp");  // If exec fails
        exit(1);
    }

    // Parent process: close pipe and wait for children to finish
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);  // Wait for child 1
    wait(NULL);  // Wait for child 2

    return 0;
}
