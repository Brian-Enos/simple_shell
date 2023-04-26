#include "main.h"

int status = 0;

int line_num = 1;

char *nameOfShell = NULL;





int main(__attribute__((unused))int ac, char **av)
{
	int bytes_read;
	int is_separated = NEGATIVE;
	int i;
	size_t buffer_size = 1;
	char *buf = NULL;
	char *buffer_pointer;
	char *buffer_temporary;
	char **arguements = NULL;

	nameOfShell = copyString(*av);

	environ = duplicateArray(environ, list_len(environ, NULL));

	signal(SIGINT, SIG_IGN);

	buf = malloc(1);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		if (is_separated == NEGATIVE)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "alx_shell$", 10);

			bytes_read = getline(&buf, &buffer_size, stdin);

			if (bytes_read == -1)
				break;
			if (bytes_read == 1)
			{
				line_num++;
				continue;
			}
			buf[bytes_read - 1] = '\0';
			buf = input_san(buf, &buffer_size);
			if (buffer_size == 0)
			{
				line_num++;
				continue;
			}
			buffer_pointer = buf;
		}
		else
			buffer_pointer = buffer_temporary;

		buffer_temporary = NULL;
		arguements = createArray(buffer_pointer, ' ', &buffer_temporary);
		if (buffer_temporary != NULL)
			is_separated = POSITIVE;
		else
			is_separated = NEGATIVE;

		i = commandRuntimeHandler(arguements);

		free(arguements);

		if (is_separated == NEGATIVE)
			line_num++;

		if (i == TERMINATE_PROCESS_EXECUTION)
			break;
	}
	free(buf);
	commandAliasProcessing(NULL, POSITIVE);
	releaseArray(environ);
	free(nameOfShell);

	return (status % 256);
}
