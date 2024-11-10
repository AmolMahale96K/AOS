#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open current directory");
        return 1;
    }

    printf("Files in the current directory:\n");

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip directories like "." and ".."
        if (entry->d_type == DT_REG) {  // Only count regular files
            printf("%s\n", entry->d_name);
            file_count++;
        }
    }

    // Close the directory
    closedir(dir);

    printf("Total number of files: %d\n", file_count);

    return 0;
}
