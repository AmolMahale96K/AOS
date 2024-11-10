#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int sigint_count = 0;

void handle_sigint(int sig) {
    sigint_count++;
    if (sigint_count == 1) {
        printf("\nCtrl-C caught. Press again to exit.\n");
    } else {
        printf("Exiting...\n");
        exit(0);
    }
}

int main() {
    // Set up the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl-C to trigger SIGINT.\n");

    // Infinite loop to keep the program running until Ctrl-C is pressed twice
    while (1) {
        // Optionally sleep for a bit to reduce CPU usage
        sleep(1);
    }

    return 0;
}
