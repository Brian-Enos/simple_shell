#include "main.h"

/**
 * main - simple shell implementation
 *
 * Return: Always 0.
 */
int main(void)
{
        char *line = NULL, **args = NULL, **env = NULL;
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
                args = split_line(line);

                /* check for empty input */
                if (args == NULL)
                        continue;

                /* check for built-in commands */
                if (is_builtin(args, env))
                        continue;

                /* check for commands in PATH */
                if (!search_path(args, env))
                        printf("%s: command not found\n", args[0]);

                free_args(args);

        } while (n_read != -1);

        free(line);
        exit(EXIT_SUCCESS);
}

/**
 * search_path - checks for commands in PATH
 * @args: array of arguments passed to shell
 * @env: environment variables
 *
 * Return: 1 if successful, 0 otherwise
 */
int search_path(char **args, char **env)
{
        char *path, *dir, *full_path = NULL;
        struct stat st;

        /* get PATH variable */
        path = get_path(env);
        if (path == NULL)
                return (0);

        /* tokenize PATH */
        dir = split_path(path);
        while (dir != NULL)
        {
                /* construct full path to command */
                full_path = join_path(dir, args[0]);

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
                dir = split_path(NULL);
        }

        free(path);
        return (0);
}

/**
 * is_builtin - checks for built-in commands
 * @args: array of arguments passed to shell
 * @env: environment variables
 *
 * Return: 1 if successful, 0 otherwise
 */
int is_builtin(char **args, char **env)
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

        if (_strcmp(args[0], "cd") == 0)
        {
                if (args[1] == NULL)
                        chdir(getenv("HOME"));
                else if (chdir(args[1]) != 0)
                        perror("cd error");
                return (1);
        }

        return (0);
}
