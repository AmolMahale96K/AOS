#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char filename[256];
    long size;
} FileInfo;

// Comparison function for sorting
int compareFileSize(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;
    return (fileA->size - fileB->size);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filenames>\n", argv[0]);
        return 1;
    }

    FileInfo files[argc - 1];
    struct stat fileStat;
    int i;

    // Read file sizes
    for (i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStat) == -1) {
            perror("Error reading file info");
            return 1;
        }
        strcpy(files[i - 1].filename, argv[i]);
        files[i - 1].size = fileStat.st_size;
    }

    // Sort files by size
    qsort(files, argc - 1, sizeof(FileInfo), compareFileSize);

    // Display filenames in ascending order by size
    printf("Filenames in ascending order by size:\n");
    for (i = 0; i < argc - 1; i++) {
        printf("%s (%ld bytes)\n", files[i].filename, files[i].size);
    }

    return 0;
}
