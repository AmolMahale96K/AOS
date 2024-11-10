#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_sighup(int sig) {
    printf("Child received SIGHUP signal\n");
}

void handle_sigint(int sig) {
    printf("Child received SIGINT signal\n");
}

void handle_sigquit(int sig) {
    printf("Child received SIGQUIT signal. My DADDY has Killed me!!!\n");
    exit(0);  // Child terminates after receiving SIGQUIT
}

int main() {
    pid_t pid;

    // Create the child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process: Set up signal handlers
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        // Child waits for signals
        while (1) {
            pause();  // Wait for signals
        }
    } else {
        // Parent process: Send signals to child at specific intervals
        sleep(3);  // Wait for 3 seconds
        kill(pid, SIGHUP);  // Send SIGHUP to child

        sleep(3);  // Wait for 3 seconds
        kill(pid, SIGINT);  // Send SIGINT to child

        sleep(24);  // Wait for 24 seconds
        kill(pid, SIGQUIT);  // Send SIGQUIT to child

        // Wait for the child to terminate
        wait(NULL);
    }

    return 0;
}
