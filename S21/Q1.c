#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    printf("Files in the current directory:\n");

    // Loop through directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Exclude "." and ".." entries
        if (entry->d_type == DT_REG) {  // Check if entry is a regular file
            printf("%s\n", entry->d_name);
            file_count++;
        }
    }

    printf("Total number of files: %d\n", file_count);

    // Close the directory
    closedir(dir);
    return 0;
}
