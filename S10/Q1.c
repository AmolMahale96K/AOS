#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];  // Pipe file descriptors
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork the first child for ls -l
    if ((pid1 = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        // First child: execute ls -l
        close(pipefd[0]);  // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);  // Execute ls -l
        perror("execlp");  // If exec fails
        return 1;
    }

    // Fork the second child for grep
    if ((pid2 = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        // Second child: execute grep
        close(pipefd[1]);  // Close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe
        close(pipefd[0]);

        execlp("grep", "grep", "filename", (char *)NULL);  // Execute grep "filename"
        perror("execlp");  // If exec fails
        return 1;
    }

    // Parent process: close both ends of the pipe and wait for children
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);  // Wait for first child
    wait(NULL);  // Wait for second child

    return 0;
}
