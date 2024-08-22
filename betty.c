#include<stdio.h>
/**
 * main - entry point to the program
 * Return: 0
 */
int main(void)
{
	char *name = "Eugine";
	int a = 10;
	int b = 5;

	if (a > b)
	{
		printf("%d\n", a);
		printf("A wins.\n");
	}
	else
	{
		printf("B wins");
	}
	printf("My name is %s and I love pleasing betty.\n", name);
	return (0);
}
