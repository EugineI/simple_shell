#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	size_t n = 0;
	char *buf = NULL;

	printf("root@TheRipe$ ");
	getline(&buf, &n, stdin);
	printf("%s", buf);

	free(buf);
	
	return(0);

}
