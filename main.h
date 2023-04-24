#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

void handle_sigint(int sig);
void print_prompt();
int parse_input(char* input, char** args);
void execute_command(char** args);
/*
* The end of main.h file
*/
#endif 

