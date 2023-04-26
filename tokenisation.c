#include "main.h"

/*
* tokenisation file
*/

char **strtow(char *str, char *delims)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!delims)
		delims = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delims) && (is_delim(str[i + 1], delims) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delims))
			i++;

		k = 0;
		while (!is_delim(str[i + k], delims) && str[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];
		words[j][m] = 0;
	}

	words[j] = NULL;
	return (words);
}


int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);

		string1++;
		string2++;
	}

	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}




char **strtow2(char *str, char delim)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			numwords++;

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delim && str[i] != '\0')
			i++;

		k = 0;
		while (str[i + k] != delim && str[i + k] != '\0')
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];

		words[j][m] = '\0';
	}

	words[j] = NULL;
	return (words);
}




char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}




int _strlen(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}












