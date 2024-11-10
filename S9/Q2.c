#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (Named Pipe)\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic link\n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown file type\n");
    }
}

int main() {
    struct stat file_stat;
    char filepath[256];

    // Ask user for the file path
    printf("Enter the file path: ");
    scanf("%s", filepath);

    // Get the status of the file
    if (stat(filepath, &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    // Determine and print the file type
    file_type(file_stat.st_mode);

    return 0;
}
