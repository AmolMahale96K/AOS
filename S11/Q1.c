#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit rl;

    // Get the current limit for the number of open files (RLIMIT_NOFILE)
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit");
        exit(1);
    }

    printf("Current file descriptor limit: soft = %ld, hard = %ld\n", rl.rlim_cur, rl.rlim_max);

    // Set a new soft limit for the number of open files
    rl.rlim_cur = 100; // Set soft limit to 100

    if (setrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("setrlimit");
        exit(1);
    }

    printf("File descriptor limit successfully set to: soft = %ld\n", rl.rlim_cur);

    // Get the current memory limit (RLIMIT_DATA)
    if (getrlimit(RLIMIT_DATA, &rl) == -1) {
        perror("getrlimit");
        exit(1);
    }

    printf("Current memory limit: soft = %ld, hard = %ld\n", rl.rlim_cur, rl.rlim_max);

    // Set a new soft limit for the memory
    rl.rlim_cur = 1024 * 1024 * 100;  // Set soft limit to 100MB

    if (setrlimit(RLIMIT_DATA, &rl) == -1) {
        perror("setrlimit");
        exit(1);
    }

    printf("Memory limit successfully set to: soft = %ld bytes\n", rl.rlim_cur);

    return 0;
}
