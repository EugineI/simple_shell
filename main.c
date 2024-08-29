#include"shell.h"
/**
 * main - entry point
 * @ac: count
 * @av: vector
 * Return: 0
 */
int main(int ac, char **av)
{
	char **argv, *mes = NULL, *token;
	ssize_t line;
	int i, status;
	size_t len = 0;
	pid_t child_pid;

	(void)ac;
	while(1)
	{
		prompt();
		line = getline(&mes, &len, stdin);
		if (line == -1)
		{
			free(mes);
			end_file();
			break;
		}
		if (line <= 1)
			continue;
		else
		{
			argv = malloc(sizeof(char *) * 1024);
			if(argv == NULL)
			{
				print_error(av[0], argv[0]);
			}
			i = 0;
			token = strtok(mes, " \t\n");
			while (token != NULL)
			{
				argv[i] = token;
				token = strtok(NULL, " \t\n");
				i++;
			} argv[i] = NULL;
			child_pid = fork();
			if (child_pid == 0)
			{
				if (execve(argv[0], argv, (char *const *)environ) == -1)
					print_error(av[0], argv[0]);
				exit(EXIT_FAILURE);
			}
			else if (child_pid > 0)
				wait(&status);
			else
				print_error(av[0], argv[0]);
			free(argv);
		}
	} free(mes);
	return (0);
}
