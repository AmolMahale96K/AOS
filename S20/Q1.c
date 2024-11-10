#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Fork to create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        printf("Child process (PID: %d) is running.\n", getpid());
        sleep(5);  // Simulating work
        printf("Child process (PID: %d) is about to be suspended.\n", getpid());

        // Suspend the process (This is effectively paused)
        kill(getpid(), SIGSTOP);
        
        // This line will not be executed until the child is resumed
        printf("Child process (PID: %d) has been resumed.\n", getpid());
    } else {  // Parent process
        printf("Parent process (PID: %d) is running.\n", getpid());
        sleep(2);  // Parent allows child to run for a short time
        
        printf("Parent process (PID: %d) is sending SIGSTOP to suspend the child.\n", getpid());
        kill(pid, SIGSTOP);  // Send SIGSTOP to the child to suspend it
        sleep(3);  // Parent waits for a while
        
        printf("Parent process (PID: %d) is sending SIGCONT to resume the child.\n", getpid());
        kill(pid, SIGCONT);  // Send SIGCONT to resume the child
        sleep(2);  // Parent waits for the child to resume

        // Wait for the child to complete
        wait(NULL);
    }

    return 0;
}
