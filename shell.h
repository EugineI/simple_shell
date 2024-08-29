#ifndef SHELL_H
#define SHELL_H
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#define BUFFER_SIZE 1024;
extern char **environ;
void exit_shell(char **argv, char *mes);
void end_file(char *mes);
void print_error(char *pro_name, char *command);
void shell_env(void);
void prompt(void);
#endif
