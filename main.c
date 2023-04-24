#include "main.h"

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
        fgets(input, MAX_INPUT_LENGTH, stdin); /*Read input from stdin*/
        input[strcspn(input, "\n")] = '\0'; /*Remove trailing newline*/

        /* 
        *Parse the input into individual arguments
        */
        int num_args = parse_input(input, args);

        /*
        * Execute the command
        */
        execute_command(args);

        /* 
        *Free memory allocated for argument strings
        */
        for (int i = 0; i < num_args; i++) {
            free(args[i]);
        }
    }

    return 0;
}

void handle_sigint(int sig) {
    printf("\n"); / Print a newline character
    print_prompt(); // Print the shell prompt
}

void print_prompt() {
    printf("$ "); // Print the shell prompt
    fflush(stdout); // Flush stdout to ensure prompt is printed immediately
}

int parse_input(char* input, char** args) {
    int num_args = 0;
    char* token = strtok(input, " ");
    while (token != NULL && num_args < MAX_ARGS) {
        args[num_args] = malloc(strlen(token) + 1); // Allocate memory for argument string
        strcpy(args[num_args], token);
        num_args++;
        token = strtok(NULL, " ");
    }
    args[num_args] = NULL; // Add a NULL terminator to the argument list
    return num_args;
}

void execute_command(char** args) {
    pid_t pid = fork(); // Create a child process
    if (pid == -1) {
        perror("fork"); // Print an error message if fork() fails
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // This is the child process
        int ret = execvp(args[0], args); // Execute the command
        if (ret == -1) {
            perror("execvp"); // Print an error message if execvp() fails
            exit(EXIT_FAILURE);
        }
    } else {
        // This is the parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to complete
    }
}

