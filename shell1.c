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
	pid_t child_pid;
	int status;
	char *com_path = NULL;

	if (strchr(argv[0], '/') == NULL)
	{
		com_path = command_path(argv[0]);
		if (com_path == NULL)
		{
			print_error(av[0], argv[0]);
			return;
		}
		argv[0] = com_path;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		if (com_path != NULL)
			free(com_path);
		return;
	}
	else if (child_pid == 0)
	{
		if (execve(argv[0], argv, (char *const *)environ) == -1)
		{
			print_error(av[0], argv[0]);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			last_status = WEXITSTATUS(status);
		}
	}
	if (com_path != NULL)
		free(com_path);
}
/**
 * command_path - name
 * @mes: command
 * Return: Null
 */
char *command_path(const char *mes)
{
	char *path_env, *path, *dir, *full;
	size_t len;
	struct stat st;

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path = strdup(path_env);
	if (path == NULL)
		return (NULL);
	dir = strtok(path, " :\t\n");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(mes) + 2;
		full = malloc(len);
		if (full == NULL)
		{
			free(path);
			return (NULL);
		}
		strcpy(full, dir);
		strcat(full, "/");
		strcat(full, mes);
		if (stat(full, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		{
			free(path);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
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
