#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void display_file_permissions(mode_t mode) {
    printf("File Permissions: ");
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    struct stat file_stat;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &file_stat) == -1) {
        perror("Could not retrieve file information");
        return 1;
    }

    printf("File Properties for %s:\n", argv[1]);
    printf("Inode Number: %lu\n", (unsigned long) file_stat.st_ino);
    printf("Number of Hard Links: %lu\n", (unsigned long) file_stat.st_nlink);
    display_file_permissions(file_stat.st_mode);
    printf("File Size: %ld bytes\n", (long) file_stat.st_size);
    printf("Last Access Time: %s", ctime(&file_stat.st_atime));
    printf("Last Modification Time: %s", ctime(&file_stat.st_mtime));
    printf("Last Status Change Time: %s", ctime(&file_stat.st_ctime));

    return 0;
}
