#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;

    dir = opendir(".");  // Open the current directory
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files in current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        // Skip the special entries "." and ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);  // Print file name
            file_count++;
        }
    }

    printf("\nTotal number of files: %d\n", file_count);

    closedir(dir);  // Close the directory
    return 0;
}
