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
	char **argv, *mes = NULL;
	ssize_t line;
	size_t len = 0;

	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			prompt();
		}
		line = getline(&mes, &len, stdin);
		if (line == -1)
		{
			if (errno == 0 || errno == EINVAL || errno == EBADF)
				end_file(mes);
			free(mes);
			exit(0);
		}
		else if (line <= 1)
			continue;
		rem_newline(mes, len);
		argv = token_input(mes);
		if (argv == NULL)
			continue;
		if (built_in(argv, mes))
		{
			free(argv);
			continue;
		}
		execute_command(argv, av);
		free(argv);
	} free(mes);
	return (0);
}
