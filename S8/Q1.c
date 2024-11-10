#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open the output file with write-only permission. Create it if it doesn't exist.
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate file descriptor to standard output (stdout)
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Error duplicating file descriptor");
        return 1;
    }

    // Now, printf will write to output.txt instead of the console
    printf("This message will be written to output.txt.\n");
    printf("Another message to demonstrate output redirection.\n");

    // Close the file descriptor
    close(fd);

    return 0;
}
