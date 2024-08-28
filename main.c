#include"shell.h"
/**
 * main - entry point
 * Description: simple shell, takes no arguments
 * Return: 0
 */
int main(void)
{
	char **argv, *token, *mes = NULL;
	size_t len = 0;
	pid_t child_pid;
	int status, line, i = 0;

	while (1)
	{
		write(1, "($) ", 4);
		line = getline(&mes, &len, stdin);
		if (line == -1)
			end_file();
		else if (line == 1)
			continue;
		token = strtok(mes, " \t|\n");
		argv = malloc(sizeof(char *) * 1024);
		i = 0;
		while (token != NULL)
		{
			if (strcmp(token, "exit") == 0)
				exit_shell(argv, mes);
			argv[i] = token;
			token = strtok(NULL, "\t| \n");
			i++;
		}
		argv[i] = NULL;
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, (char *const *)environ) == -1)
				perror("./shell");
			exit(EXIT_FAILURE);
		} else if (child_pid > 0)
			wait(&status);
		else
			perror("./shell");
		free(argv);
	} free(mes);
	return (0);
}
