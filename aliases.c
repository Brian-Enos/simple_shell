#include "shell.h"

int status;

/**
 * commandAliasProcessing - deals with command aliases
 * @arguements: arguments from command line
 * @to_free: indicated if aliases need to be freed (exiting shell);
 *
 * Return: POSITIVE if exiting, NEGATIVE if the command is not "alias" or an alias,
 * DONT_CREATE_NEW_CHILD_PROCESS if success
 */

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

/**
 * replaceIfAlias - if the alias command is not called, this will check if the
 * command is an alias, and if so replace it with it's value
 * @arguements: argument to be checked
 * @aliasPointer: points to list of aliases to be checked against
 *
 * Return: POSITIVE
 */
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

/**
 * releaseAlias - frees all aliases
 * @aliasPointer: pointer to headNode of alias list
 *
 * Return: POSITIVE
 */
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

/**
 * displayAliases - prints all aliases in list
 * @aliasPointer: points to list of aliases
 *
 * Return: DONT_CREATE_NEW_CHILD_PROCESS
 */
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


/**
 * displayAliasValue - prints the value of a particular alias
 * @arg: name of alias
 * @aliasPointer: points to list of aliases
 *
 * Return: POSITIVE if valid alias, NEGATIVE if not
 */
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

/**
 * configureAlias - initializes an alias or resets its value if it exists
 * @arg: name of alias
 * @aliasPointer: pointer to list of aliases
 * @setValue: value of alias to be set
 *
 * Return: POSITIVE
 */
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
