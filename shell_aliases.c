#include "main.h"
int status;



int commandAliasProcessing(char **arguements, int to_free)
{
	static alias headNode = {NULL, NULL, NULL};
	int no_error = POSITIVE;

	if (to_free)
		return (releaseAlias(headNode.nextNode));

	if (!compareString("alias", *arguements, EQUAL))
		return (replaceIfAlias(arguements, headNode.nextNode));

	if (!arguements[1])
		return (displayAliases(headNode.nextNode));

	while (*arguements)
	{
		char *characterPointer = *arguements;
		while (*characterPointer && *characterPointer != '=')
			characterPointer++;

		if (*characterPointer == '\0' || characterPointer == *arguements)
			no_error &= displayAliasValue(*arguements++, &headNode);
		else
		{
			*characterPointer++ = '\0';
			configureAlias(*arguements++, &headNode, characterPointer);
			*(characterPointer - 1) = '=';
		}
	}

	status = 0;
	return (DONT_CREATE_NEW_CHILD_PROCESS);
}




int replaceIfAlias(char **arguements, alias *aliasPointer)
{
	while (aliasPointer != NULL)
	{
		if (compareString(*arguements, aliasPointer->nodeValue, EQUAL) == POSITIVE)
		{
			*arguements = copyString(aliasPointer->nodeValue);
			return (LAUNCH_RUNTIME_PROCESS);
		}
		aliasPointer = aliasPointer->nextNode;
	}
	return (POSITIVE);
}




int releaseAlias(alias *aliasPointer)
{
	alias *temporary;

	while (aliasPointer != NULL)
	{
		temporary = aliasPointer;
		aliasPointer = aliasPointer->nextNode;
		free(temporary->nodeValue);
		free(temporary->nodeValue);
		free(temporary);
	}

	return (POSITIVE);
}






int displayAliases(alias *aliasPointer)
{
	while (aliasPointer != NULL)
	{
		write(STDOUT_FILENO, aliasPointer->nodeValue, getStringLength(aliasPointer->nodeValue));
		write(STDOUT_FILENO, "=\'", 2);
		write(STDOUT_FILENO, aliasPointer->nodeValue,
		      getStringLength(aliasPointer->nodeValue));
		write(STDOUT_FILENO, "\'\n", 2);
		aliasPointer = aliasPointer->nextNode;
	}
	return (DONT_CREATE_NEW_CHILD_PROCESS);
}







int displayAliasValue(char *arg, alias *aliasPointer)
{
	while (aliasPointer != NULL)
	{
		fflush(stdin);
		if (compareString(arg, aliasPointer->nodeValue, EQUAL) == POSITIVE)
		{
			write(STDOUT_FILENO, arg, getStringLength(arg));
			write(STDOUT_FILENO, "=\'", 2);
			write(STDOUT_FILENO, aliasPointer->nodeValue,
			      getStringLength(aliasPointer->nodeValue));
			write(STDOUT_FILENO, "\'\n", 2);
			return (POSITIVE);
		}
		aliasPointer = aliasPointer->nextNode;
	}

	status = 1;
	write(STDERR_FILENO, "alias: ", 7);
	write(STDERR_FILENO, arg, getStringLength(arg));
	write(STDERR_FILENO, " not found\n", 11);

	return (NEGATIVE);
}







int configureAlias(char *arg, alias *aliasPointer, char *setValue)
{
	while (aliasPointer->nextNode != NULL
	       && compareString(aliasPointer->nodeValue, arg, EQUAL) != POSITIVE)
	{
		aliasPointer = aliasPointer->nextNode;
	}

	if (compareString(aliasPointer->nodeValue, arg, EQUAL) == POSITIVE)
	{
		free(aliasPointer->nodeValue);
	}
	else
	{
		aliasPointer->nextNode = malloc(sizeof(alias *));
		aliasPointer = aliasPointer->nextNode;
		if (aliasPointer == NULL)
			exit(EXIT_FAILURE);

		aliasPointer->nodeValue = copyString(arg);
		aliasPointer->nextNode = NULL;
	}
	aliasPointer->nodeValue = copyString(setValue);

	return (POSITIVE);
}
