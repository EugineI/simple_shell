#include"shell.h"
/**
 * shell_env - checks environment
 * Return: nothing
 */
void shell_env(void)
{
	char **env = environ;

	while (*env)
	{
		write(1, *env, strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}
