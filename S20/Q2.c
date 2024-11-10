#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Regular File");
    } else if (S_ISDIR(mode)) {
        printf("Directory");
    } else if (S_ISCHR(mode)) {
        printf("Character Device");
    } else if (S_ISBLK(mode)) {
        printf("Block Device");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (Pipe)");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link");
    } else if (S_ISSOCK(mode)) {
        printf("Socket");
    } else {
        printf("Unknown Type");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;

    if (stat(argv[1], &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Inode number: %ld\n", file_stat.st_ino);
    printf("File Type: ");
    print_file_type(file_stat.st_mode);
    printf("\n");

    return 0;
}
