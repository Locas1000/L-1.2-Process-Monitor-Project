#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int main() {
    // Array of commands to execute
    char *commands[][3] = {
        {"ls", "-l", NULL}, //will run ls command with -l as an argument
        {"date", NULL, NULL}, // will run date command
        {"whoami", NULL, NULL}, // will run whoami command
        {"pwd", NULL, NULL}, // will run pwd command
        {"ps", "aux", NULL} //will run ps command with aux as an argument
    };

    int num_commands = 5; // we have 5 different commands we want to run
    pid_t child_pids[num_commands]; // will give us 1 PID per child

    for (int i = 0; i < num_commands; i++) { //runs code 5 times
        pid_t rc = fork(); //creates 1 child every loop

        if (rc < 0) {
            // Handle fork failure
            fprintf(stderr, "Fork failed for command %d\n", i);
            exit(1);
        } else if (rc == 0) {
            // Child process
            printf("Child %d (PID: %d) executing: %s\n", //runs second because it's slower than the else
                   i+1, getpid(), commands[i][0]);

            // Execute command
            execvp(commands[i][0], commands[i]);   //runs immediately if successful



            // If execvp returns, it failed
            fprintf(stderr, "Exec failed for command: %s\n", commands[i][0]);
            exit(1);
        } else {
            // Parent process
            child_pids[i] = rc;
            printf("Parent created child %d with PID: %d\n", i+1, rc); //this usually runs first because
                                                                             //it's faster than the process
                                                                             //that the child is running
                                                                             //but order is not guaranteed
        }
    }
    // Wait for all children and collect exit statuses
    for (int i = 0; i < num_commands; i++) {
        int status;
        pid_t wc = wait(&status);

        if (wc == -1) {
            fprintf(stderr, "Wait failed\n");
            continue;
        }

        // Find which child this was
        int child_index = -1;
        for (int j = 0; j < num_commands; j++) {    // find which child index corresponds to the PID that just finished
            if (child_pids[j] == wc) {
                child_index = j;
                break;
            }
        }

        // Display results
        if (WIFEXITED(status)) {    // check if the child exited normally
            printf("Child %d (PID: %d) completed with exit code: %d\n",
                   child_index, wc, WEXITSTATUS(status));
        } else {
            printf("Child %d (PID: %d) terminated abnormally\n",
                   child_index, wc);
        }
    }
    return 0;
}

