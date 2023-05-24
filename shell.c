#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void display_prompt(void)
{
    printf("#cisfun$ ");
}

int main(void)
{
    char command[100];  // Buffer to store the user's command
    int ret;            // Return value of the execve system call

    while (1) {
        display_prompt();  // Display the prompt

        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Handle the end of file condition (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) {
            // Handle fork error
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            ret = execve(command, NULL, NULL);
            if (ret == -1) {
                // Handle command not found error
                perror(command);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            wait(NULL);  // Wait for the child process to finish
        }
    }

    return 0;
}

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 shell.c -o shell

./shell
