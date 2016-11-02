#include <stdio.h>
#include <string.h>

#define MAX 100

void main()
{
	char *op = "-+*/";
	char *input = "((1+34)*3)";
	char *b;
	int oper[MAX], t_op = 0;
	int result[MAX][2], t_res = 0;

	int trick = 0;
	int i, j, c;
	printf("\n");
	for (i = 0; i < strlen(input); i++)
	{
		if ('0'<=input[i] && input[i]<='9')
		{
			if (trick == 0)
			{
				trick = 1;
				result[t_res][0] = 0;
				result[t_res][1] = (int) input[i] - '0';
				t_res++;
			}
			else
			{
				result[t_res - 1][1] *= 10;
				result[t_res - 1][1] += ((int) input[i] - '0');
			}
		}
		else if (strchr(op, input[i]) != NULL)
		{
			b = strchr(op, input[i]);
			c = (int)(b - op);
			if ((oper[t_op - 1] / 2) <= (c/2))
			{
				oper[t_op] = c;
				t_op++;
			}
			else
			{
				result[t_res][0] = 1;
				result[t_res][1] = oper[t_op - 1];
				t_res++;
				oper[t_op - 1] = c;
			}
			trick = 0;
		}
		else if (input[i] == '(')
		{
			oper[t_op] = -1;
			t_op++;
			trick = 0;
		}
		else if (input[i] == ')')
		{
			while ((oper[t_op - 1] != -1) && (t_op > 0))
			{
				t_op--;
				result[t_res][0] = 1;
				result[t_res][1] = oper[t_op];
				t_res++;
			}
			if (t_op == 0)
			{
				printf("GUUUUEAK!!\n");
				exit(0);
			}
			t_op--;
			trick = 0;
		}
		else
		{
			printf("ERROR!!!!\n");
			exit(0);
		}
		printf("%c %d %d \n", input[i], t_res, t_op);
	}
	if (t_op != 0)
	{
		printf("UUUUUUUUUUUUUUAKKK!\n");
		exit(0);
	}
	for (i = 0; i < t_res; i++)
	{
		if (result[i][0] == 0)
			printf("%d ", result[i][1]);
		else
			printf("%c ", op[result[i][1]]);
	}
	printf("\n");
}
