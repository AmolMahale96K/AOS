#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILES 100

// Function to compare file sizes for sorting
int compare(const void *a, const void *b) {
    struct stat statA, statB;
    const char *fileA = *(const char **)a;
    const char *fileB = *(const char **)b;

    // Get file stats
    if (stat(fileA, &statA) == -1) {
        perror("stat");
        return 0;
    }
    if (stat(fileB, &statB) == -1) {
        perror("stat");
        return 0;
    }

    // Compare file sizes
    return statA.st_size - statB.st_size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    // Sort the files by their sizes
    qsort(&argv[1], argc - 1, sizeof(char *), compare);

    // Print the sorted filenames with their sizes
    for (int i = 1; i < argc; i++) {
        struct stat statBuf;
        if (stat(argv[i], &statBuf) == -1) {
            perror("stat");
            continue;
        }

        printf("File: %s, Size: %ld bytes\n", argv[i], statBuf.st_size);
    }

    return 0;
}
