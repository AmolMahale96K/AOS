#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void block_signals() {
    // Block SIGINT and SIGQUIT
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // First child process for "ls -l"
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        // In child process 1 (ls -l)
        block_signals(); // Block Ctrl-C and Ctrl-\ signals

        // Redirect standard output to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]); // Close unused read end
        close(pipefd[1]); // Close the write end after redirecting

        execlp("ls", "ls", "-l", NULL); // Execute "ls -l"
        perror("execlp"); // Only reached if execlp fails
        exit(1);
    }

    // Second child process for "wc -l"
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        // In child process 2 (wc -l)
        block_signals(); // Block Ctrl-C and Ctrl-\ signals

        // Redirect standard input to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]); // Close unused write end
        close(pipefd[0]); // Close the read end after redirecting

        execlp("wc", "wc", "-l", NULL); // Execute "wc -l"
        perror("execlp"); // Only reached if execlp fails
        exit(1);
    }

    // In parent process
    close(pipefd[0]); // Close read end of the pipe
    close(pipefd[1]); // Close write end of the pipe

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
