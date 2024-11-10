#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

// Function to determine and return file type as a string
const char* get_file_type(mode_t mode) {
    if (S_ISREG(mode)) return "Regular File";
    if (S_ISDIR(mode)) return "Directory";
    if (S_ISLNK(mode)) return "Symbolic Link";
    if (S_ISCHR(mode)) return "Character Device";
    if (S_ISBLK(mode)) return "Block Device";
    if (S_ISFIFO(mode)) return "FIFO (Named Pipe)";
    if (S_ISSOCK(mode)) return "Socket";
    return "Unknown";
}

int main(int argc, char *argv[]) {
    struct stat file_stat;
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("File\t\tInode Number\tFile Type\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &file_stat) == -1) {
            fprintf(stderr, "Error accessing '%s': %s\n", argv[i], strerror(errno));
            continue;
        }

        printf("%-15s\t%lu\t\t%s\n", argv[i], (unsigned long)file_stat.st_ino, get_file_type(file_stat.st_mode));
    }

    return 0;
}
