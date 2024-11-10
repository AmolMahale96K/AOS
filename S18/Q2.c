#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char message1[] = "Hello World";
    char message2[] = "Hello SPPU";
    char message3[] = "Linux is Funny";

    // Create an unnamed pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();  // Create a child process
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {  // Child process
        close(pipe_fd[0]);  // Close read end of the pipe

        // Write messages to the pipe
        write(pipe_fd[1], message1, strlen(message1) + 1);
        write(pipe_fd[1], message2, strlen(message2) + 1);
        write(pipe_fd[1], message3, strlen(message3) + 1);

        close(pipe_fd[1]);  // Close write end after writing
        exit(0);
    } else {  // Parent process
        close(pipe_fd[1]);  // Close write end of the pipe

        // Read messages from the pipe and display
        char buffer[100];
        wait(NULL);  // Wait for child process to complete

        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        close(pipe_fd[0]);  // Close read end after reading
    }

    return 0;
}
