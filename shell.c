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
