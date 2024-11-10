#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char month_input[10];
    int target_month;

    printf("Enter the month (1-12): ");
    scanf("%d", &target_month);

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open current directory");
        return 1;
    }

    printf("Files created in month %d:\n", target_month);

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Get file information
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("Could not get file information");
            continue;
        }

        // Check if it's a regular file
        if (S_ISREG(file_stat.st_mode)) {
            // Extract the creation month
            struct tm *timeinfo = localtime(&file_stat.st_ctime);
            int file_month = timeinfo->tm_mon + 1;

            // Print file name if it matches the target month
            if (file_month == target_month) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
