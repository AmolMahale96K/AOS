#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) == -1) {
        perror("Error retrieving file information");
        return 1;
    }

    printf("File Type: %s\n", get_file_type(file_stat.st_mode));
    printf("Inode Number: %lu\n", (unsigned long) file_stat.st_ino);

    return 0;
}
