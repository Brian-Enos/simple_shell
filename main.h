#ifndef MAIN_H
#define MAIN_H


/* 
* main.h header file
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define MAX_ARGS 64

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


extern char **environ;

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \0, 0, 0}

int _strlen(char *);
char *_strcat(char *, char *);
char *starts_with(const char *, const char *);
int _strcmp(char *, char *);

int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char);
void _eputs(char *);

int loophsh(char **);


char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);


int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);


void find_cmd(info_t *);
void fork_cmd(info_t *);
int find_builtin(info_t *);
int hsh(info_t *, char **);



int _putchar(char);
void _puts(char *);
char *_strdup(const char *);
char *_strcpy(char *, char *);


char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);


char **strtow2(char *, char);
char **strtow(char *, char *);


void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
char *_memset(char *, char, unsigned int);


int _myalias(info_t *);
int _myhistory(info_t *);


int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);



void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);


int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);


int bfree(void **);


void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);


int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);


int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myenv(info_t *);
char *_getenv(info_t *, const char *);

void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);


int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);


int replace_alias(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);



ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
size_t print_list(const list_t *);

size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);


int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int write_history(info_t *info);
char *get_history_file(info_t *info);

#endif 

























