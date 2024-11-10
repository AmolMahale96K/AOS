#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];  // Pipe file descriptors
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork to create a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process: read from pipe
        close(pipefd[1]);  // Close the write end of the pipe
        read(pipefd[0], read_msg, sizeof(read_msg));  // Read from pipe
        printf("Child process received: %s\n", read_msg);
        close(pipefd[0]);  // Close the read end after reading
    } else {
        // Parent process: write to pipe
        close(pipefd[0]);  // Close the read end of the pipe
        write(pipefd[1], write_msg, strlen(write_msg));  // Write to pipe
        close(pipefd[1]);  // Close the write end after writing
        wait(NULL);  // Wait for the child to finish
    }

    return 0;
}
