#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

extern char **environ;
/**
 * main - entry point
 * Description: simple shell, takes no arguments
 * Return: 0
 */
int main(void)
{
	char *token, *mes = NULL;
	size_t len = 0;
	size_t line;
	pid_t child_pid;
	int status, i = 0;
	char **argv;

	while(1)
	{
		write(1, "#cisfun$ ", 9);
		line = getline(&mes, &len, stdin);
		if (line == -1)
		{
			if(feof(stdin))
			{
				write(1, "\n", 1);
				break;
			}
			perror("./shell: ");
			return (-1);
		}
		else if (line == 1)
			continue;
		else
		{
			token = strtok(mes, "\t\n");
			argv = malloc(sizeof(char *) * 1024);
			i = 0;
			while(token != NULL)
			{
				argv[i] = token;
				token = strtok(NULL, "\t\n");
				i++;
			}
			argv[i] = NULL;
			child_pid = fork();
			if (child_pid == 0)
			{
				if(execve(argv[0], argv, environ) == -1)
					perror("./shell: ");
				exit(EXIT_FAILURE);
			}
			else if(child_pid > 0)
				wait(&status);
			else
				perror("./shell: ");
			free(argv);
		}

	}
	free(mes);
	return(0);
}
