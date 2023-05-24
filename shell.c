#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    int ret;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        ret = fork();
        if (ret == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (ret == 0) {
            char* args[] = {command, NULL};
            ret = execve(command, args, NULL);
            if (ret == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }
    }

    return 0;
}
