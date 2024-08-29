#include"shell.h"
/**
 * prompt - name
 * Return: nothing
 */
void prompt()
{
	char prompt[] = "#cisfun ";
	write(1, prompt, strlen(prompt));
}
