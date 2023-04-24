#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* function prototypes */
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strlen(char *s);
char **_strtok(char *str, char *delim);
char *_getenv(char *name);
int execute(char **args, char **env);
char *getpath(char **env);
void sig_handler(int signum);
void prompt(void);

/* helper functions */
int count_words(char *str, char *delim);
void free_args(char **args);
int check_path(char **args, char **env, char *command);
int check_builtins(char **args, char **env);
void print_env(char **env);

#endif /* MAIN_H */

