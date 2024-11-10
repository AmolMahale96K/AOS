#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main() {
    char filename[256];
    DIR *dir;
    struct dirent *entry;
    int found = 0;

    // Prompt the user for a filename
    printf("Enter the filename to search: ");
    scanf("%s", filename);

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    // Search for the file in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            found = 1;
            break;
        }
    }

    // Close the directory
    closedir(dir);

    // Display the result
    if (found) {
        printf("File '%s' is present in the current directory.\n", filename);
    } else {
        printf("File '%s' is not found in the current directory.\n", filename);
    }

    return 0;
}
