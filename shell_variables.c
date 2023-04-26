#include "main.h"

int status;
int line_num;
char *nameOfShell;

char *checkIfArgumentIsVariable(char *arg)
{
	char *clone = NULL;
	char *pointer = arg;
	char *nextNode;
	char *temporary;
	int is_var;
	int i;

	while (*pointer != '\0')
	{
		if (*pointer == '$')
		{
			if (clone == NULL)
			{
				clone = copyString(arg);
        
				i = pointer - arg;
        
				pointer = clone + i;
			}
			nextNode = pointer + 1;
			while (*nextNode != '\0' && *nextNode != '$' && *nextNode != '#')
				nextNode++;
			if (*nextNode == '$' && nextNode > pointer + 1)
				is_var = POSITIVE;
			else if (*nextNode == '#')
				is_var = NONE;
			else
				is_var = NEGATIVE;

			*nextNode = '\0';

			if (compareString("$?", pointer, EQUAL) == POSITIVE)
				temporary = _itoa(status);
      
			else if (compareString("$0", pointer, EQUAL) == POSITIVE)
				temporary = copyString(nameOfShell);
      
			else if (findArrayElement(environ, pointer + 1) != NULL)
				temporary = copyString(findArrayElement
                               
					      (environ, pointer + 1)
                               
					      + getStringLength(pointer));
			else
				temporary = copyString("");

			*pointer = '\0';
			pointer = string_concat(clone, temporary);
      
			free(temporary);
			if (is_var == NEGATIVE)
			{
				free(clone);
				clone = pointer;
				break;
			}
			if (is_var == POSITIVE)
				*nextNode = '$';
			else if (is_var == NONE)
				*nextNode = '#';
			temporary = string_concat(pointer, nextNode);
			free(pointer);
			pointer = temporary;
			free(clone);
			clone = pointer;
			if (is_var == NONE)
			{
				while (*pointer != '#')
					pointer++;
			}
		}
    
    
    
		pointer++;
    
	}
	if (clone != NULL)
		return (clone);
  
  
  

	return (arg);
}
