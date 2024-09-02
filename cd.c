#include"shell.h"
/**
 * _cd - handles cd
 * args: argument
 * Return: 0 and 1
 */
int _cd(char **args)
{
	char *dir, cwd[1024];
	char *prev_dir = getenv("OLDPWD");

	if (args[1] == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			return (1);
		}
	}
	else if (strcmp(args[1], "_") == 0)
	{
		if (prev_dir == NULL)
		{
			return (1);
		}
		dir = prev_dir;
		printf("%s\n", dir);
	} else
	{
		dir = args[1];
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(dir) != 0)
	{
		return(1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
	{
		return (1);
	}
	return 0;
}
