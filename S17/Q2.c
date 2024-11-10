#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);  // Block Ctrl-C (SIGINT)
    sigaddset(&set, SIGQUIT); // Block Ctrl-\ (SIGQUIT)
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    if (pipe(pipe_fd) == -1) {  // Create pipe
        perror("pipe");
        exit(1);
    }

    // Block Ctrl-C and Ctrl-\ signals
    block_signals();

    // Create the first child process for "ls -l"
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {  // First child: "ls -l"
        close(pipe_fd[0]);  // Close read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to the pipe
        close(pipe_fd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);  // Execute "ls -l"
        perror("execlp");  // If execlp fails
        exit(1);
    }

    // Create the second child process for "wc -l"
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {  // Second child: "wc -l"
        close(pipe_fd[1]);  // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect stdin from the pipe
        close(pipe_fd[0]);

        execlp("wc", "wc", "-l", (char *)NULL);  // Execute "wc -l"
        perror("execlp");  // If execlp fails
        exit(1);
    }

    // Parent process: Wait for both child processes to finish
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, NULL, 0);  // Wait for first child
    waitpid(pid2, NULL, 0);  // Wait for second child

    return 0;
}
