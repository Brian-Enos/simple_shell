#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>

#define LAUNCH_RUNTIME_PROCESS 7
#define DONT_CREATE_NEW_CHILD_PROCESS 6
#define TERMINATE_PROCESS_EXECUTION 5
#define PREFIX 4
#define EQUAL 3
#define NONE 2
#define POSITIVE 1
#define NEGATIVE 0

extern char **environ;

extern int status;

extern int line_num;

extern char *nameOfShell;

/**
 * struct Alias - singly linked list
 * @node_name: name of alias
 * @nodeValue: command that alias calls
 * @nextNode: points to nextNode node
 */
typedef struct Alias
{
	char *node_name;
	char *nodeValue;
	struct Alias *nextNode;
} alias;



int commandRuntimeHandler(char **arguements);

int checkIfCommandInbuilt(char **arguements);

int and_or(char **arguements, char operator, int last_compare);

char *checkIfNotBuiltIn(char **arguements);

int runCommand(char **arguements);

char *input_san(char *old_buf, size_t *old_size);

int input_err_check(char *pointer);

void displayErrorMessage(char *arg0, char *arg1);

void *_realloc(void *pointer, unsigned int old_size, unsigned int createdArraySize);

int _getline(char **line_pointer, size_t *n, int file);

char *checkIfArgumentIsVariable(char *arg);

int getStringLength(char *string);

char *copyString(char *src);

char *string_concat(char *s1, char *s2);

int compareString(char *s1, char *s2, int pref_or_match);

char *findArrayElement(char **array, char *itemName);

char **createArray(char *string, char endOfListEntryChar, char **ifSemiColonPointer);

int list_len(char **list, char *entry);

char **duplicateArray(char **previousArray, int createdArraySize);

int releaseArray(char **arguements);

int configureEnvironmentVariable(const char *name, const char *value);

int deleteEnvironmentVariable(const char *name);

int changeDirectory(char *name);

int commandAliasProcessing(char **arguements, int free);

int releaseAlias(alias *aliasPointer);

int replaceIfAlias(char **arguements, alias *aliasPointer);

int displayAliases(alias *aliasPointer);

int displayAliasValue(char *arg, alias *aliasPointer);

int configureAlias(char *arg, alias *aliasPointer, char *setValue);

int displayEnvironMentVariable(void);

char *_itoa(int n);

int stringToInteger(char *s);

#endif
