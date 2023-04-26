#include "main.h"
int status;





char **duplicateArray(char **previousArray, int createdArraySize)
{
	char **createdArray = NULL;
	char **arrayPointer;

	createdArray = malloc(sizeof(char **) * createdArraySize);

	arrayPointer = createdArray;
	while (*previousArray != NULL)
	{
		*arrayPointer = copyString(*previousArray);
		arrayPointer++;
		previousArray++;
	}
	*arrayPointer = NULL;

	return (createdArray);
}





int releaseArray(char **arguements)
{
	char **pointer = arguements;

	while (*pointer != NULL)
	{
		free(*pointer);
		pointer++;
	}

	free(arguements);

	return (POSITIVE);
}





char *findArrayElement(char **array, char *itemName)
{
  
	while (*array != NULL)
	{
    
		if (compareString(*array, itemName, PREFIX) == POSITIVE)
			return (*array);
    
    

		array++;
	}

	return (NULL);
}





char **createArray(char *string, char endOfListEntryChar, char **ifSemiColonPointer)
{
	char *stringPointer = string;
	unsigned int i = 2;
	char **array = NULL;
  

	while (*stringPointer != '\0')
	{
		if (*stringPointer == ';')
			break;
		if (*stringPointer == endOfListEntryChar && *(stringPointer + 1) != '\0')
			i++;

		stringPointer++;
	}

	array = malloc(i * sizeof(char **));
	if (array == NULL)
		exit(EXIT_FAILURE);

	array[0] = string;
	stringPointer = string;
	i = 1;

	while (*stringPointer != '\0')
	{
		if (*stringPointer == endOfListEntryChar)
		{
			*stringPointer = '\0';
			stringPointer++;
			if (*stringPointer == ';')
			{
				array[i] = NULL;
				if (*(stringPointer + 1) != '\0' && *(stringPointer + 2) != '\0')
					*ifSemiColonPointer = stringPointer + 2;
				break;
			}
			if (*stringPointer != '\0')
			{
				array[i] = stringPointer;
				i++;
			}
		}
		stringPointer++;
	}
	array[i] = NULL;

	return (array);
}
