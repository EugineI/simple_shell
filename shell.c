#include"shell.h"
/**
 * exit_shell - name
 * @argv: argument vector
 * @mes: line message
 * Return: nothing
 */
void exit_shell(char **argv, char *mes)
{
	free(argv);
	free(mes);
	exit(0);
}
/**
 * end_file - name
 * Return: nothing
 */
void end_file(void)
{
	if (feof(stdin))
	{
		write(1, "\n", 1);
		exit(0);
	}
	perror("./shell");
}
