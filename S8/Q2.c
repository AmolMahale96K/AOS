#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];  // File descriptors for the pipe
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork the first child process for ls -l
    if ((pid1 = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        // First child: exec ls -l
        close(pipefd[0]);  // Close read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to the pipe
        close(pipefd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);  // Execute ls -l
        perror("execlp");  // If exec fails
        return 1;
    }

    // Fork the second child process for wc -l
    if ((pid2 = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        // Second child: exec wc -l
        close(pipefd[1]);  // Close write end of the pipe
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to the pipe
        close(pipefd[0]);

        execlp("wc", "wc", "-l", (char *)NULL);  // Execute wc -l
        perror("execlp");  // If exec fails
        return 1;
    }

    // Parent: Close both ends of the pipe and wait for children
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);  // Wait for the first child
    wait(NULL);  // Wait for the second child

    return 0;
}
