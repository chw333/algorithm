#include<conio.h>
#include<string.h>
#include<stdio.h>
main()
{
	char a[100];
	char c[10][100];
	char *b;
	int cnt = 0;
	gets(a);

/*
	"abc,def,ghi"

	b = strtok(a, ",")

		  |
	"abc\0def,ghi"
	 |
	 b

	"abc"

	b = strtok(NULL, ",")

			   |
	"abc\0def\0ghi"
		  |
		  b

	"def"

	b = strtok(NULL, ",")

				  |
	"abc\0def\0ghi"
			   |
			   b

	"ghi"

	b => NULL

	for end....

*/

	for(b = a; ((b = strtok(b, ",")) != NULL); b = NULL) {
//		printf("%s\n", b);
		strcpy(c[cnt], b);
		cnt++;
		for (int i=strlen(b)-1; i>=0; i--)
			printf("%c", b[i]);
		printf("\n");
	}

	for (int i=0; i<cnt; i++)
		printf("%s\n", c[i]);
}