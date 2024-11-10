#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &file_stat) == 0) {
            printf("File '%s' is present in the current directory.\n", argv[i]);
        } else {
            printf("File '%s' is NOT present in the current directory.\n", argv[i]);
        }
    }

    return 0;
}
