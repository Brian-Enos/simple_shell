#include "main.h"

/**
 * main - simple shell implementation
 *
 * Return: Always 0.
 */
int main(void)
{
        char *line = NULL, *command = NULL, **args = NULL, **env = NULL;
        size_t bufsize = 0;
        ssize_t n_read = 0;
        int interactive = 1;

        /* check if shell is interactive */
        if (!isatty(STDIN_FILENO))
                interactive = 0;

        /* setup signal handler */
        signal(SIGINT, sig_handler);

        /* main shell loop */
        do {
                /* print prompt */
                if (interactive)
                        prompt();

                /* get input from user */
                n_read = getline(&line, &bufsize, stdin);
                if (n_read == -1)
                        break;

                /* tokenize input */
                args = _strtok(line, " \n\t\r");

                /* check for empty input */
                if (args == NULL)
                        continue;

                /* check for built-in commands */
                if (check_builtins(args, env))
                        continue;

                /* check for commands in PATH */
                command = args[0];
                if (!check_path(args, env, command))
                        printf("%s: command not found\n", command);

                free_args(args);

        } while (n_read != -1);

        free(line);
        exit(EXIT_SUCCESS);
}

/**
 * check_path - checks for commands in PATH
 * @args: array of arguments passed to shell
 * @env: environment variables
 * @command: command to search for in PATH
 *
 * Return: 1 if successful, 0 otherwise
 */
int check_path(char **args, char **env, char *command)
{
        char *path, *dir, *full_path = NULL;
        struct stat st;

        /* get PATH variable */
        path = getpath(env);
        if (path == NULL)
                return (0);

        /* tokenize PATH */
        dir = _strtok(path, ":");
        while (dir != NULL)
        {
                /* construct full path to command */
                full_path = malloc(_strlen(dir) + _strlen(command) + 2);
                if (full_path == NULL)
                        perror("malloc error");
                full_path = _strcat(full_path, dir);
                full_path = _strcat(full_path, "/");
                full_path = _strcat(full_path, command);

                /* check if file exists */
                if (stat(full_path, &st) == 0)
                {
                        /* execute command */
                        if (access(full_path, X_OK) == 0)
                        {
                                if (execute(args, env))
                                        return (1);
                        }
                        else
                                printf("%s: Permission denied\n", args[0]);

                        free(full_path);
                        free(path);
                        return (1);
                }

                free(full_path);
                dir = _strtok(NULL, ":");
        }

        free(path);
        return (0);
}

/**
 * check_builtins - checks for built-in commands
 * @args: array of arguments passed to shell
 * @env: environment variables
 *
 * Return: 1 if successful, 0 otherwise
 */
int check_builtins(char **args, char **env)
{
        int i = 0;

        /* compare args to built-in commands */
        if (_strcmp(args[0], "exit") == 0)
                exit(EXIT_SUCCESS);

        if (_strcmp(args[0], "env") == 0)
        {
                print_env(env);
                return (1);
        }

        if (_strcmp(args[

