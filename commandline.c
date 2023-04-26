#include "main.h"



int status;
char *nameOfShell;


char *checkIfNotBuiltIn(char **arguements)
{
	char *commandBuffer;
	char *fullBuffer;
	char *environmentPathString = NULL;
	char *environmentPathPointer;
	char *temporaryEnvironmentPath;
	char **environmentPathVariable;
	char **environmentPathVariablePointer;

	if (access(*arguements, X_OK) == 0)
		return (copyString(*arguements));

	if (findArrayElement(environ, "PATH") != NULL)
		environmentPathString = copyString(findArrayElement(environ, "PATH") + 5);

	environmentPathPointer = environmentPathString;

	if (environmentPathString != NULL)
	{
		if (*environmentPathString == ':')
		{
			commandBuffer = string_concat("./", *arguements);
			if (access(commandBuffer, X_OK) == 0)
			{
				free(environmentPathString);
				return (commandBuffer);
			}
			else
			{
				free(commandBuffer);
				environmentPathPointer = copyString(environmentPathString + 1);
				free(environmentPathString);
				environmentPathString = environmentPathPointer;
			}
		}
		while (*environmentPathPointer != '\0')
		{
			if (*environmentPathPointer == ':' && *(environmentPathPointer + 1) == ':')
			{
				*(environmentPathPointer + 1) = '\0';
				temporaryEnvironmentPath = (string_concat(environmentPathString, ".:"));
				environmentPathPointer = string_concat(temporaryEnvironmentPath, environmentPathPointer + 2);
				free(environmentPathString);
				free(temporaryEnvironmentPath);
				environmentPathString = environmentPathPointer;
			}
			environmentPathPointer++;
		}
	}

	environmentPathVariable = createArray(environmentPathString, ':', NULL);
	environmentPathVariablePointer = environmentPathVariable;

	commandBuffer = string_concat("/", *arguements);

	fullBuffer = copyString(commandBuffer);

	while (*environmentPathVariablePointer != NULL && access(fullBuffer, X_OK) != 0)
	{
		free(fullBuffer);
		fullBuffer = string_concat(*environmentPathVariablePointer, commandBuffer);
		environmentPathVariablePointer++;
	}

	free(commandBuffer);
	free(environmentPathString);
	free(environmentPathVariable);

	if (access(fullBuffer, X_OK) != 0)
	{
		displayErrorMessage(arguements[0], NULL);
		free(fullBuffer);
		return (NULL);
	}

	return (fullBuffer);
}



int commandRuntimeHandler(char **arguements)
{
	char **arguementsPointer = arguements;
	int prev_eval = NONE;
	int no_err = POSITIVE;
	char prev_op = 'c';
	char next_op = 'c';
	int what_do;

  
  
	while (*arguements != NULL && prev_eval != TERMINATE_PROCESS_EXECUTION)
	{
		while (*arguementsPointer != NULL && **arguementsPointer != '&'
		       && **arguementsPointer != '|')
			arguementsPointer++;

		if (compareString(*arguementsPointer, "||", EQUAL) == POSITIVE)
		{
			*arguementsPointer = NULL;
			arguementsPointer++;
			next_op = '|';
		}
    
    
    
		if (compareString(*arguementsPointer, "&&", EQUAL) == POSITIVE)
		{
			*arguementsPointer = NULL;
			arguementsPointer++;
			next_op = '&';
		}
    
    
    
    
		if (next_op == 'c')
			break;

		prev_eval = and_or(arguements, prev_op, prev_eval);
		if (prev_eval == NEGATIVE)
			no_err = NEGATIVE;
		prev_op = next_op;
		arguements = arguementsPointer;
	}

  
  
  
	if (next_op == 'c')
	{
		what_do = runCommand(arguements);

		if (what_do == TERMINATE_PROCESS_EXECUTION)
			return (TERMINATE_PROCESS_EXECUTION);
	}
  
  
  
  
  
  

	if (no_err == NEGATIVE || what_do == NEGATIVE)
		return (NEGATIVE);

	return (POSITIVE);
}



int changeDirectory(char *name)
{
	char *home;
	char *pwd;
	char path_buffer[PATH_MAX];
	size_t buffer_size = PATH_MAX;
	int i;

	getcwd(path_buffer, buffer_size);

	if (name == NULL || compareString("~", name, PREFIX) == POSITIVE
	    || compareString("$HOME", name, EQUAL) == POSITIVE)
	{
		if (name != NULL && *name == '~' && *(name + 1) != '\0'
		    && *(name + 1) != '/')
		{
			status = 2;
			displayErrorMessage("cd", name);
      
      
      
			return (DONT_CREATE_NEW_CHILD_PROCESS);
		}

		home = findArrayElement(environ, "HOME");
		if (home == NULL)
		{
			status = 2;
      
			displayErrorMessage("cd", name);
      
			return (DONT_CREATE_NEW_CHILD_PROCESS);
		}

		while (*home != '=')
			home++;

		home++;
		i = chdir((const char *)home);
    
		if (i != -1)
			configureEnvironmentVariable("PWD", (const char *)home);
    

		if (name != NULL && compareString("~/", name, PREFIX) == POSITIVE)
			name += 2;
	}
	if (compareString("-", name, EQUAL) == POSITIVE)
	{
		pwd = findArrayElement(environ, "OLDPWD");
    
		if (pwd == NULL)
      
			return (2);
    

		while (*pwd != '=')
		{
			pwd++;
		}
		pwd++;

		i = chdir((const char *)pwd);
		if (i != -1)
		{
			write(STDOUT_FILENO, pwd, getStringLength(pwd));
			write(STDOUT_FILENO, "\n", 1);
			configureEnvironmentVariable("PWD", (const char *)pwd);
		}
	}
	if (name != NULL && compareString("~", name, EQUAL) == NEGATIVE
	    && compareString("$HOME", name, EQUAL) == NEGATIVE && i != -1
	    && *name != '\0' && compareString("-", name, EQUAL) != POSITIVE)
	{
		i = chdir((const char *)name);
		if (i != -1)
			configureEnvironmentVariable("PWD", (const char *)name);
	}
	if (i == -1)
	{
		status = 2;
		displayErrorMessage("cd", name);
    
		return (DONT_CREATE_NEW_CHILD_PROCESS);
	}

	status = 0;
	configureEnvironmentVariable("OLDPWD", (const char *)path_buffer);

	return (DONT_CREATE_NEW_CHILD_PROCESS);
}


int runCommand(char **arguements)
{
	char *buffer_pointer = *arguements;
	char *command_name;
	pid_t pid;
	int what_do = checkIfCommandInbuilt(arguements);

	if (what_do == LAUNCH_RUNTIME_PROCESS)
	{
		command_name = checkIfNotBuiltIn(arguements);
		if (command_name == NULL)
			return (NEGATIVE);

		pid = fork();
		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(command_name, arguements, environ);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		free(command_name);
		fflush(stdin);
	}

	if (compareString("NEGATIVE", *arguements, EQUAL) == POSITIVE)
		status = 1;

	if (*arguements != buffer_pointer)
		free(*arguements);
	arguements++;

	while (*arguements != NULL)
	{
		while (*buffer_pointer != '\0')
		{
			buffer_pointer++;
		}
		buffer_pointer++;

		if (*arguements != buffer_pointer)
			free(*arguements);

		arguements++;
	}

	if (what_do == TERMINATE_PROCESS_EXECUTION)
		return (TERMINATE_PROCESS_EXECUTION);

	if (status != 0)
		return (NEGATIVE);

	return (POSITIVE);
}
