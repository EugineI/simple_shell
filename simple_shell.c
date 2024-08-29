#include"shell.h"
/**
 * main - entry point
 * @ac: count
 * @av: vector
 * Description: simple shell, takes no arguments
 * Return: 0
 */
int main(int ac, char **av)
{
	char **argv, *token, *mes = NULL;
	size_t len = 0;
	ssize_t line;
	pid_t child_pid;
	int status, i;

	(void)ac;
	while (1)
	{
		write(1, "#cisfun$ ", 9);
		line = getline(&mes, &len, stdin);
		if (line == -1)
		{
			free(mes);
			end_file();
		}
		if (line <= 1)
			continue;
		argv = malloc(sizeof(char *) * 1024);
		if (argv == NULL)
		{
			perror("malloc");
			continue;
		}
		i = 0;
		token = strtok(mes, " \t\n");
		while (token != NULL)
		{
			if (strcmp(token, "exit") == 0)
				exit_shell(argv, mes);
			argv[i] = token;
			token = strtok(NULL, " \t\n");
			i++;
		} argv[i] = NULL;
		if (argv[0] != NULL && strcmp(argv[0], "env") == 0)
		{
			shell_env();
			free(argv);
			continue;
		} child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, (char *const *)environ) == -1)
			{
				print_error(av[0], argv[0]);
				exit(EXIT_FAILURE);
			}
		} else if (child_pid > 0)
			wait(&status);
		else
			print_error(av[0], argv[0]);
		free(argv);
	} free(mes);
	return (0);
}
