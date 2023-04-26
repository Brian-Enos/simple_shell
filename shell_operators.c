#include "main.h"
int status;




char *nameOfShell;





int and_or(char **arguements, char operator, int last_compare)
{
	int i;

	if (last_compare == NONE)
	{
		i = runCommand(arguements);
		if (i == TERMINATE_PROCESS_EXECUTION)
			return (TERMINATE_PROCESS_EXECUTION);
		if (i == POSITIVE)
			return (POSITIVE);

		return (NEGATIVE);
	}
	if (last_compare == POSITIVE && operator == '&')
	{
		i = runCommand(arguements);
		if (i == TERMINATE_PROCESS_EXECUTION)
			return (TERMINATE_PROCESS_EXECUTION);
		if (i == POSITIVE)
			return (POSITIVE);

		return (NEGATIVE);
	}

	if (last_compare == NEGATIVE && operator == '|')
	{
		i = runCommand(arguements);
		if (i == TERMINATE_PROCESS_EXECUTION)
			return (TERMINATE_PROCESS_EXECUTION);
		if (i == POSITIVE)
			return (POSITIVE);

		return (NEGATIVE);
	}

	if (last_compare == POSITIVE && operator == '|')
		return (POSITIVE);

	return (NEGATIVE);
}
