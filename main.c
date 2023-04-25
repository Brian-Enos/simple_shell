
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

void handle_sigint(int sig);
void print_prompt();
int parse_input(char* input, char** args);
void execute_command(char** args);
void free_args(char** args, int num_args);

int main(int argc, char** argv) {
    char input[MAX_INPUT_LENGTH];
    char* args[MAX_ARGS];
    int status;

    /*
    * Register a signal handler for SIGINT (interrupt signal)
    */
    signal(SIGINT, handle_sigint);

    while (1) {
        print_prompt(); // Print the shell prompt
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n"); // Print a newline character
                exit(EXIT_SUCCESS); // Exit the shell gracefully
            } else {
                perror("fgets"); // Print an error message if fgets() fails
                exit(EXIT_FAILURE);
            }
        }
        input[strcspn(input, "\n")] = '\0'; /*Remove trailing newline*/

        /* 
        *Parse the input into individual arguments
        */
        int num_args = parse_input(input, args);
        if (num_args == -1) {
            fprintf(stderr, "Error: Too many arguments\n");
            continue;
        } else if (num_args == -2) {
            fprintf(stderr, "Error: Empty command\n");
            continue;
        }

        /*
        * Execute the command
        */
        execute_command(args);

        /* 
        *Free memory allocated for argument strings
        */
        free_args(args, num_args);
    }

    return 0;
}

void handle_sigint(int sig) {
    printf("\n"); // Print a newline character
    print_prompt(); /*
                    * Printing the shell prompt
                    */
}

void print_prompt() {
    printf("$ "); /* 
                   * Print the shell prompt
                   */
    fflush(stdout); /* 
                    * Flush stdout to ensure prompt is printed immediately
                    */
}

int parse_input(char* input, char** args) {
    int num_args = 0;
    char* token = strtok(input, " ");
    while (token != NULL && num_args < MAX_ARGS) {
        if (strlen(token) > MAX_INPUT_LENGTH) {
            fprintf(stderr, "Error: Argument too long\n");
            return -1;
        }
        args[num_args] = malloc(strlen(token) + 1); /*
                                                     * Allocate memory for argument string
                                                     */
        if (args[num_args] == NULL) {
            perror("malloc"); /* 
                               * Print an error message if malloc() fails
                               */
            exit(EXIT_FAILURE);
        }
        strcpy(args[num_args], token);
        num_args++;
        token = strtok(NULL, " ");
    }
    if (num_args == 0) {
        return -2;
    } else if (num_args == MAX_ARGS && token != NULL) {
        return -1;
    }
    args[num_args] = NULL; /* 
                            * Add a NULL terminator to the argument list
                            */
    return num_args;
}
    
void execute_command(char** args) {
    pid_t pid = fork(); /* 
                         *Create a child proces
                         */
if (pid == -1) {
perror("fork"); /
* Print an error message if fork() fails
/
exit(EXIT_FAILURE);
} else if (pid == 0) {
/ This is the child process
*
/
int ret = execvp(args[0], args); // Execute the command
if (ret == -1) {
perror("execvp"); /
* Print an error message if execvp() fails
/
exit(EXIT_FAILURE);
}
} else {
/
* This is the parent process
/
int status;
waitpid(pid, &status, 0); /
* Wait for the child process to complete
*/
}
free_args(args, MAX_ARGS);
}

void handle_sigint(int sig) {
printf("\n");
print_prompt();
}

void print_prompt() {
printf("$ ");
fflush(stdout);
}

int parse_input(char* input, char** args) {
int num_args = 0;
char* token = strtok(input, " ");
while (token != NULL && num_args < MAX_ARGS) {
args[num_args] = malloc(strlen(token) + 1);
strcpy(args[num_args], token);
num_args++;
token = strtok(NULL, " ");
}
args[num_args] = NULL;
return num_args;
}

void free_args(char** args, int num_args) {
for (int i = 0; i < num_args; i++) {
free(args[i]);
}
}

int main(int argc, char** argv) {
char input[MAX_INPUT_LENGTH];
char* args[MAX_ARGS];
int status;
/*
* Register a signal handler for SIGINT (interrupt signal)
*/
signal(SIGINT, handle_sigint);

while (1) {
    print_prompt();
    if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
        if (feof(stdin)) {
            printf("Exiting...\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
    }
    input[strcspn(input, "\n")] = '\0';

    /* 
    *Parse the input into individual arguments
    */
    int num_args = parse_input(input, args);
    if (num_args == -1) {
        fprintf(stderr, "Error: Too many arguments\n");
        continue;
    } else if (num_args == -2) {
        fprintf(stderr, "Error: Empty command\n");
        continue;
    }

    /*
    * Execute the command
    */
    execute_command(args);
}

return 0;
}
