#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char *str = malloc(sizeof(char) * 15);
	str = "hi";
	printf("hello, world %s\n", str);
	return 0;
}
