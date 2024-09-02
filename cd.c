#include"shell.h"
/**
 * _cd - handles cd
 * args: argument
 * Return: 0 and 1
 */
int _cd(char **args)
{
	char *dir, cwd[1024];
	static char prev_dir[1024] = "";

	if (args[1] == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			fprintf(stderr, "cd: No home directory\n");
			return (1);
		}
	}
	else if (strcmp(args[1], "_") == 0)
	{
		if (strlen(prev_dir) == 0)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (1);
		}
		dir = prev_dir;
		printf("%s\n", dir);
	} else
	{
		dir = args[1];
	}
	if (getcwd(prev_dir, sizeof(prev_dir)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(dir) != 0)
	{
		perror("cd");
		return(1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
	{
		perror("getcwd");
		return (1);
	}
	return 0;
}
