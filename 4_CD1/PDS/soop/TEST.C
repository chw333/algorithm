#include <stdio.h>

main()
{
	int a = 3;
	int *b;

	clrscr();

	*b = 4;

	printf("%ld \n", &a);
	printf("%d \n", a);
	printf("%ld \n", b);
	printf("%ld \n", &b);
	printf("%d  \n", *b);
}
