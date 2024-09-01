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
	exit(2);
}
/**
 * end_file - name
 * @mes: mes
 * Return: nothing
 */
void end_file(char *mes)
{
	{
		free(mes);
		exit(0);
	}
}
/**
 * print_error - name
 * @pro_name: program name
 * @command: command
 * Return: Nothing
 */
void print_error(char *pro_name, char *command)
{
	char *message = ": 1: ";
	char *not_found = ": not found\n";

	write(2, pro_name, strlen(pro_name));
	write(2, message, strlen(message));
	write(2, command, strlen(command));
	write(2, not_found, strlen(not_found));
}
/**
 * token_input - tokenises input
 * @mes: argument
 * Return: argv
 */
char **token_input(char *mes)
{
	char **argv;
	char *token;
	int i = 0;

	argv = malloc(sizeof(char *) * 1024);
	if (argv == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	token = strtok(mes, " \t\n");
	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
