#include"shell.h"
/**
 * rem_newline - removes \n
 * @str: input
 * @len: iput length
 * Return: command with no \n
 */
char *rem_newline(char *str, ssize_t len)
{
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}
