#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file_fd;

    // Open the file "output.txt" with write permissions
    file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor to standard output (fd 1)
    if (dup2(file_fd, STDOUT_FILENO) == -1) {
        perror("Error redirecting stdout");
        close(file_fd);
        return 1;
    }

    // Now, any output to stdout goes to "output.txt" instead of the console
    printf("This text will be written to output.txt\n");
    printf("Redirection of standard output using dup and open successful!\n");

    // Close the file descriptor
    close(file_fd);

    return 0;
}
