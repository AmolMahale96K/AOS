#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    // Get file information
    if (stat(argv[1], &fileStat) == -1) {
        perror("Error retrieving file info");
        return 1;
    }

    // Display the inode number
    printf("Inode number of '%s': %ld\n", argv[1], fileStat.st_ino);

    // Determine and display the file type
    printf("File type: ");
    if (S_ISREG(fileStat.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(fileStat.st_mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(fileStat.st_mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(fileStat.st_mode)) {
        printf("FIFO or pipe\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("Symbolic link\n");
    } else if (S_ISSOCK(fileStat.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown type\n");
    }

    return 0;
}
