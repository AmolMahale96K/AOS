#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void display_file_properties(const char *file_name) {
    struct stat file_stat;

    // Get the file properties using stat system call
    if (stat(file_name, &file_stat) == -1) {
        perror("stat");
        return;
    }

    // Displaying file properties
    printf("File: %s\n", file_name);
    printf("Inode number: %ld\n", file_stat.st_ino);
    printf("Number of hard links: %ld\n", file_stat.st_nlink);
    printf("File size: %ld bytes\n", file_stat.st_size);

    // Displaying file permissions
    printf("File permissions: ");
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-"); // Directory or not
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-"); // Owner read
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-"); // Owner write
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-"); // Owner execute
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-"); // Group read
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-"); // Group write
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-"); // Group execute
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-"); // Others read
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-"); // Others write
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-"); // Others execute
    printf("\n");

    // Displaying access, modification and change time
    printf("Last access time: %s", ctime(&file_stat.st_atime));
    printf("Last modification time: %s", ctime(&file_stat.st_mtime));
    printf("Last status change time: %s", ctime(&file_stat.st_ctime));
}

int main() {
    char file_name[100];

    printf("Enter the file name: ");
    scanf("%s", file_name);

    display_file_properties(file_name);

    return 0;
}
