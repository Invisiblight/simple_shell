#include <stdio.h>
#include "funcs.h"
#include "prototypes.h"

/**
 * main- Entry Point
 *
 * Return: Always (0)
 */
int main(void)
{
	char *buffer;
	char **args, **args_cpy;
	int status = 0;

	do {
		if (isatty(0) == 1)
			printf("$: ");

		buffer = read_line();
		args = tokenize(buffer);
		args_cpy = args;

		/* Check for exit */
		while (*args)
		{
			if (strcmp(*args, "exit") == 0)
				exit(1);
		args++;
		}

		/* Reset args pointer back to original */
		args = args_cpy;

		/* Check for status based on return of proc_exe() */
		if (proc_exe(args) == 0)
			status = 1;
		else
			status = 0;

	} while (status);
	
	/* Free memory */
	free(buffer);
	free(args);

	return (0);
}
