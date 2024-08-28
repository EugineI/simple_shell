#ifndef SHELL_H
#define SHELL_H
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

extern char **environ;
void exit_shell(char **argv, char *mes);
void end_file(void);
void print_error(char *pro_name, char *command);
void shell_env(void);
#endif
