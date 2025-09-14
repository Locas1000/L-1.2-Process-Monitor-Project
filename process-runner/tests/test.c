#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// Commands used for testing
char *valid_commands[][3] = {
    {"ls", "-l", NULL},
    {"date", NULL, NULL},
    {"whoami", NULL, NULL},
    {"pwd", NULL, NULL},
{"sh", "-c", "ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -n 6"}
};

char *invalid_commands[][2] = {
    {"invalid_command", NULL}
};

// Function to run commands and collect exit codes
int run_commands(char *commands[][3], int num_commands) {
    pid_t child_pids[num_commands];

    for (int i = 0; i < num_commands; i++) {
        pid_t rc = fork();
        if (rc < 0) {
            fprintf(stderr, "Fork failed for command %d\n", i);
            exit(1);
        } else if (rc == 0) {
            execvp(commands[i][0], commands[i]);
            fprintf(stderr, "Exec failed for command: %s\n", commands[i][0]);
            exit(1);
        } else {
            child_pids[i] = rc;
        }
    }

    int all_success = 1;
    for (int i = 0; i < num_commands; i++) {
        int status;
        pid_t wc = wait(&status);

        int child_index = -1;
        for (int j = 0; j < num_commands; j++) {
            if (child_pids[j] == wc) {
                child_index = j;
                break;
            }
        }

        if (WIFEXITED(status)) {
            printf("Child %d (PID: %d) exit code: %d\n", child_index, wc, WEXITSTATUS(status));
            if (WEXITSTATUS(status) != 0) all_success = 0;
        } else {
            printf("Child %d (PID: %d) terminated abnormally\n", child_index, wc);
            all_success = 0;
        }
    }
    return all_success;
}

// Basic Functionality Test
void test_basic_functionality() {
    printf("=== Basic Functionality Test ===\n");
    int success = run_commands(valid_commands, 5);
    if (success)
        printf("All valid commands executed successfully.\n\n");
    else
        printf("Some valid commands failed.\n\n");
}

// Error Handling Test
void test_error_handling() {
    printf("=== Error Handling Test ===\n");
    int success = run_commands((char * (*)[3])invalid_commands, 1);
    if (!success)
        printf("Error handling test passed (invalid command detected).\n\n");
    else
        printf("Error handling test failed.\n\n");
}

// Performance Test
void test_performance() {
    printf("=== Performance Test ===\n");
    clock_t start = clock();
    run_commands(valid_commands, 5);
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time to execute 5 commands: %.6f seconds\n\n", elapsed);
}

int main() {
    test_basic_functionality();
    test_error_handling();
    test_performance();
    return 0;
}

