#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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
        printf("Unknown");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        struct stat file_stat;

        if (stat(argv[i], &file_stat) == -1) {
            perror("stat");
            continue;
        }

        printf("File: %s\n", argv[i]);
        printf("Inode number: %ld\n", file_stat.st_ino);
        printf("File Type: ");
        print_file_type(file_stat.st_mode);
        printf("\n\n");
    }

    return 0;
}
