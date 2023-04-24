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
nt access(const char *pathname, int mode);
int chdir(const char *path);
int close(int fd);
int closedir(DIR *dirp);
int execve(const char *filename, char *const argv[], char *const envp[]);
void exit(int status);
void _exit(int status);
int fflush(FILE *stream);
pid_t fork(void);
void free(void *ptr);
char *getcwd(char *buf, size_t size);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
pid_t getpid(void);
int isatty(int fd);
int kill(pid_t pid, int sig);
void *malloc(size_t size);
int open(const char *pathname, int flags, mode_t mode);
DIR *opendir(const char *name);
void perror(const char *s);
ssize_t read(int fd, void *buf, size_t count);
struct dirent *readdir(DIR *dirp);
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
char *strtok(char *str, const char *delim);
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);

/* helper functions */
int count_words(char *str, char *delim);
void free_args(char **args);
int check_path(char **args, char **env, char *command);
int check_builtins(char **args, char **env);
void print_env(char **env);

#endif /* MAIN_H */

