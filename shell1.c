#include"shell.h"
/**
 * prompt - name
 * Return: nothing
 */
void prompt(void)
{
	char *prompt;

	if (isatty(0))
	{
		prompt = "($) ";
		write(1, prompt, strlen(prompt));
	}
}
/**
 * execute_command - execve function
 * @argv: command
 * @av: for error handling
 * Return: nothing
 */
void execute_command(char **argv, char **av)
{
	pid_t child_pid = fork();
	int status;

	if (child_pid == -1)
	{
		perror("fork");
		free(argv);
		return;
	}
	else if (child_pid == 0)
	{
		if (execve(argv[0], argv, (char *const *)environ) == -1)
		{
			print_error(av[0], argv[0]);
			_exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
}
/**
 * built_in - handles built ins
 * @argv: vector
 * @mes: message
 * Return: 0 or 1
 */
int built_in(char **argv, char *mes)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		exit_shell(argv, mes);
		return (1);
	}
	if (argv[0] != NULL && strcmp(argv[0], "env") == 0)
	{
		shell_env();
		return (1);
	}
	return (0);
}
