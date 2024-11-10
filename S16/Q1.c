#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void list_files_created_in_month(int month) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    struct tm *file_time;

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

        // Get the file creation time
        file_time = localtime(&file_stat.st_ctime);

        // Check if the file was created in the specified month
        if (file_time->tm_mon + 1 == month) {
            printf("File: %s, Created on: %s", entry->d_name, asctime(file_time));
        }
    }

    closedir(dir);  // Close the directory
}

int main() {
    int month;

    printf("Enter the month (1-12): ");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("Invalid month. Please enter a month between 1 and 12.\n");
        return 1;
    }

    list_files_created_in_month(month);

    return 0;
}
