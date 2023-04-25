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
void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_launch(char **args);
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_execute(char **args);
int lsh_num_builtins();

// List of builtin commands, followed by their corresponding functions.
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit
};

int main(int argc, char **argv) {
    // Loop through all command-line arguments
    for (int i = 1; i < argc; i++) {
        // Check if argument is a valid file path
        if (access(argv[i], F_OK) != -1) {
            // Open file
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            
            // Read and execute commands from file
            char input[MAX_INPUT_LENGTH];
            while (fgets(input, MAX_INPUT_LENGTH, fp) != NULL) {
                // Remove newline character
                input[strcspn(input, "\n")] = '\0';
                char **args = lsh_split_line(input);
                execute_command(args);
                free_args(args, MAX_ARGS);
            }
            
            // Close file
            fclose(fp);
        } else {
            printf("Error: %s is not a valid file path\n", argv[i]);
        }
    }
    
    // Run shell loop if no command-line arguments were provided
    if (argc == 1) {
        lsh_loop();
    }
    
    return EXIT_SUCCESS;
}

