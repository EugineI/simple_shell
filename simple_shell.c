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
	int interactive = isatty(STDIN_FILENO);

	(void)ac;
	while (1)
	{
		if (interactive)
		{
			prompt();
		}
		line = getline(&mes, &len, stdin);
		if (line == -1)
		{
			if (errno == 0 || errno == EINVAL || errno == EBADF)
				end_file(mes);
			free(mes);
			exit(EXIT_FAILURE);
		}
		if (line <= 1)
			continue;
		argv = malloc(sizeof(char *) * 1024);
		if (argv == NULL)
		{
			perror("malloc");
			free(mes);
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
		if (child_pid == -1)
		{
			perror("fork");
			free(argv);
			continue;
		}
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, (char *const *)environ) == -1)
			{
				print_error(av[0], argv[0]);
				exit(EXIT_FAILURE);
			}
		} else
			wait(&status);
		free(argv);
	}
	free(mes);
	return (0);
}
