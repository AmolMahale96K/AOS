#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files_greater_than_n_bytes(long n) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    dir = opendir(".");  // Open the current directory
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Check if the file size is greater than 'n' bytes
        if (file_stat.st_size > n) {
            printf("File: %s, Size: %ld bytes\n", entry->d_name, file_stat.st_size);
        }
    }

    closedir(dir);  // Close the directory
}

int main() {
    long n;

    printf("Enter the size threshold in bytes: ");
    scanf("%ld", &n);

    list_files_greater_than_n_bytes(n);

    return 0;
}
