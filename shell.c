#include "shell.h"

/**
 * main - simple shell program entry point
 * Description: simple shell program written in C
 * for UNIX based systems. Program written by
 * Antony Muga and Nicholas Oyengo
 * Return:Status code 0 if successful
 */

int main(void)
{
	pid_t process_id;
	char buffer[BUFFER_SIZE];
	char *args[MAXIMUM_ARGUEMENTS + 1];

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		buffer[strcspn(buffer, "\n")] = 0;
		process_id = fork();

		if (process_id == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (process_id == 0)
		{
			int index = 0;
			char *token = strtok(buffer, " ");

			while (token != NULL && index < MAXIMUM_ARGUEMENTS)
			{
				args[index++] = token;
				token = strtok(NULL, " ");
			}

			args[index] = NULL;
			execvp(args[0], args);
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			int status;

			if (waitpid(process_id, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (0);
}
