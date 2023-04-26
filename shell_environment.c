#include "main.h"
int status;




int displayEnvironMentVariable(void)
{
	char **pointer = environ;

	while (*pointer != NULL)
	{
		write(STDOUT_FILENO, *pointer, getStringLength(*pointer));
		write(STDOUT_FILENO, "\n", 1);
		pointer++;
	}

	status = 0;

	return (DONT_CREATE_NEW_CHILD_PROCESS);
}




int configureEnvironmentVariable(const char *name, const char *value)
{
	char **new_environ;
	char *buffer;
	char *buffer_temporary;
	char *element_pointer = findArrayElement(environ, (char *) name);
	int len;

	if (value == NULL)
	{
		write(STDERR_FILENO, "setenv: no value given\n", 23);
		status = 2;
		return (DONT_CREATE_NEW_CHILD_PROCESS);
	}

	buffer = string_concat((char *)name, "=");
  
	buffer_temporary = string_concat(buffer, (char *)value);
  
	free(buffer);
  
	buffer = buffer_temporary;

	if (element_pointer == NULL)
	{
		len = list_len(environ, NULL);
		new_environ = duplicateArray(environ, len + 1);
		new_environ[len - 1] = buffer;
		new_environ[len] = NULL;
		releaseArray(environ);
		environ = new_environ;
    
    
		return (DONT_CREATE_NEW_CHILD_PROCESS);
	}

	len = list_len(environ, (char *)name);
	free(environ[len]);
	environ[len] = buffer;

	status = 0;

	return (DONT_CREATE_NEW_CHILD_PROCESS);
}



int deleteEnvironmentVariable(const char *name)
{
	char **env_pointer;
	int len = list_len(environ, (char *)name);

	if (len == -1)
	{
		write(STDERR_FILENO, "unsetenv: variable not found\n", 29);
		status = 2;
		return (DONT_CREATE_NEW_CHILD_PROCESS);
	}

	env_pointer = environ + len;
	free(*env_pointer);
	while (*(env_pointer + 1) != NULL)
	{
		*env_pointer = *(env_pointer + 1);
		env_pointer++;
	}
	*env_pointer = NULL;
	status = 0;

	return (DONT_CREATE_NEW_CHILD_PROCESS);
}
