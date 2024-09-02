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
	char **argv = NULL, *mes = NULL;
	ssize_t line;
	size_t len = 0;

	(void)ac;
	while (1)
	{
		prompt();
		line = getline(&mes, &len, stdin);
		if (line == -1)
		{
			if (feof(stdin))
			{
				end_file(mes);
			} else
			{
				perror("getline");
				free(mes);
				exit(EXIT_FAILURE);
			} }
		if (line <= 1)
		{
			continue;
		} rem_newline(mes, line);
		argv = token_input(mes);
		if (argv == NULL || argv[0] == NULL)
		{
			if (argv != NULL)
				free(argv);
			continue;
		}
		if (strcmp(argv[0], "cd") == 0)
		{
			_cd(argv);
			free(argv);
			continue;
		}
		if (built_in(argv, mes))
		{
			free(argv);
			continue;
		} execute_command(argv, av);
		free(argv);
	} free(mes);
	return (0);
}
