#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    
    // Open the output.txt file for writing
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Redirect the standard output (stdout) to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return 1;
    }

    // Now the output will be written to output.txt
    printf("This will be written to output.txt instead of the terminal.\n");

    // Close the file descriptor
    close(fd);

    return 0;
}
