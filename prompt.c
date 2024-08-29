#include"shell.h"
/**
 * prompt - name
 * Return: nothing
 */
void prompt()
{
	char *prompt;

	if (isatty(0))
	{
		prompt = "#cisfun ";
		write(1, prompt, strlen(prompt));
	}
}
