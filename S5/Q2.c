#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process: Write messages to the pipe
        close(pipefd[0]);  // Close unused read end

        char *message1 = "Hello World\n";
        char *message2 = "Hello SPPU\n";
        char *message3 = "Linux is Funny\n";

        write(pipefd[1], message1, strlen(message1));
        write(pipefd[1], message2, strlen(message2));
        write(pipefd[1], message3, strlen(message3));

        close(pipefd[1]);  // Close write end after writing
        exit(0);
    }
    else {
        // Parent process: Read messages from the pipe
        close(pipefd[1]);  // Close unused write end

        printf("Messages from the child process:\n");
        while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {
            printf("%s", buffer);
        }

        close(pipefd[0]);  // Close read end after reading
        wait(NULL);  // Wait for child process to finish
    }

    return 0;
}
