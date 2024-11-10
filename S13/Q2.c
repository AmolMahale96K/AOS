#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void list_files_with_prefix(const char *prefix) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");  // Open the current directory
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check if the file name starts with the prefix
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
            printf("Found: %s\n", entry->d_name);
        }
    }

    closedir(dir);  // Close the directory
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    const char *prefix = argv[1];
    list_files_with_prefix(prefix);

    return 0;
}
