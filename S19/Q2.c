#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork the first child for "ls -l"
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {  // Child process for "ls -l"
        close(pipe_fd[0]);  // Close the read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to the pipe
        close(pipe_fd[1]);  // Close the write end after duplicating

        execlp("ls", "ls", "-l", (char *)NULL);  // Execute "ls -l"
        perror("execlp");
        exit(1);
    }

    // Fork the second child for "wc -l"
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {  // Child process for "wc -l"
        close(pipe_fd[1]);  // Close the write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect stdin from the pipe
        close(pipe_fd[0]);  // Close the read end after duplicating

        execlp("wc", "wc", "-l", (char *)NULL);  // Execute "wc -l"
        perror("execlp");
        exit(1);
    }

    // Parent process: Close both ends of the pipe and wait for child processes
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, NULL, 0);  // Wait for first child (ls -l)
    waitpid(pid2, NULL, 0);  // Wait for second child (wc -l)

    return 0;
}
