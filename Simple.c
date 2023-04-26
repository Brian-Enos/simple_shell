#include "main.h"

void print_prompt() {
    printf("$ ");
}

void read_command(char* buffer, int buffer_size) {
    fgets(buffer, buffer_size, stdin);
}

void execute_command(char* command) {
    int result = system(command);
    if (result == -1) {
        printf("Command not found\n");
    }
}

int main() {
    char buffer[1024];
    while (1) {
        print_prompt();
        read_command(buffer, sizeof(buffer));
        if (feof(stdin)) {
            printf("\n");
            exit(0);
        }
        execute_command(buffer);
    }
    return 0;
}

