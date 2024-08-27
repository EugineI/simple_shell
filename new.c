#include<stdio.h>
#include"shell.h"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void)
{
    char **argv, *token, *mes = NULL;
    size_t line, len = 0;
    pid_t child_pid;
    int status, i = 0;
    char *path, *dir, *cmd_path;
    int cmd_found;

    while (1)
    {
        write(1, "#cisfun$ ", 9);
        line = getline(&mes, &len, stdin);
        if (line == -1)
        {
            if (feof(stdin))
                write(1, "\n", 1);
            break;
        }
        else if (line == 1)
            continue;

        token = strtok(mes, " \t|\n"); 
        argv = malloc(sizeof(char *) * 1024);
        i = 0;
        while (token != NULL)
        {
            argv[i] = token;
            token = strtok(NULL, "\t| \n");
            i++;
        }
        argv[i] = NULL;

        // Check if the command exists in the PATH
        path = getenv("PATH");
        dir = strtok(path, ":");
        cmd_found = 0;
        while (dir != NULL)
        {
            cmd_path = malloc(strlen(dir) + strlen(argv[0]) + 2); // +2 for '/' and '\0'
            strcpy(cmd_path, dir);
            strcat(cmd_path, "/");
            strcat(cmd_path, argv[0]);

            if (access(cmd_path, F_OK) == 0)
            {
                argv[0] = cmd_path; // Replace argv[0] with the full path to the command
                cmd_found = 1;
                break;
            }

            free(cmd_path);
            dir = strtok(NULL, ":");
        }

        if (!cmd_found)
        {
            printf("./shell: %s: command not found\n", argv[0]);
            free(argv);
            continue;
        }

        // If command is found, proceed with forking and executing
        child_pid = fork();
        if (child_pid == 0)
        {
            if (execve(argv[0], argv, (char *const *)environ) == -1)
                perror("./shell: ");
            exit(EXIT_FAILURE);
        }
        else if (child_pid > 0)
        {
            wait(&status);
        }
        else
        {
            perror("./shell: ");
        }

        free(argv);
        free(cmd_path); // Free the allocated memory for cmd_path
    }
    free(mes);
    return (0);
}

