#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sighup(int sig) {
    printf("Child: Received SIGHUP signal.\n");
}

void handle_sigint(int sig) {
    printf("Child: Received SIGINT signal.\n");
}

void handle_sigquit(int sig) {
    printf("Child: My Papa has Killed me!!!\n");
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: Set up signal handlers
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        // Keep the child process running to catch signals
        while (1) {
            pause();  // Wait for signals
        }
    } else {
        // Parent process
        printf("Parent: Sending signals to child every 3 seconds...\n");

        // Send SIGHUP and SIGINT every 3 seconds
        for (int i = 0; i < 5; i++) {
            sleep(3);
            if (i % 2 == 0) {
                kill(pid, SIGHUP);  // Send SIGHUP signal
            } else {
                kill(pid, SIGINT);  // Send SIGINT signal
            }
        }

        // After 15 seconds, send SIGQUIT to terminate the child
        kill(pid, SIGQUIT);
        wait(NULL);  // Wait for the child to terminate
        printf("Parent: Child process has terminated.\n");
    }

    return 0;
}
