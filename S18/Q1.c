#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char file_name[100];
    int file_found = 0;

    // Accept the file name from the user
    printf("Enter the file name to search: ");
    scanf("%s", file_name);

    dir = opendir(".");  // Open the current directory
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Traverse through the directory entries
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, file_name) == 0) {
            printf("File %s is present in the current directory.\n", file_name);
            file_found = 1;
            break;
        }
    }

    if (!file_found) {
        printf("File %s is not present in the current directory.\n", file_name);
    }

    closedir(dir);  // Close the directory
    return 0;
}
