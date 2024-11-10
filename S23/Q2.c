#include <stdio.h>
#include <sys/stat.h>

int main() {
    char filename[256];
    struct stat fileStat;

    // Prompt the user for a filename
    printf("Enter the filename to check: ");
    scanf("%s", filename);

    // Get file information
    if (stat(filename, &fileStat) == -1) {
        perror("Error retrieving file info");
        return 1;
    }

    // Identify and display the file type
    printf("File type of '%s': ", filename);
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
