#include <stdio.h>
int dynamic[50][200];

void main()
{
	FILE *fp;
	int i, j, k, m, s, c, stall[200];

	fp = fopen("barn1.in", "r");
	fscanf(fp, "%d %d %d", &m, &s, &c);
	for (i = 0; i < c; i++)
		fscanf(fp, "%d", &stall[i]);
	fclose(fp);

	for (i = 0; i < c; i++)
		for (j = 0; j < c; j++)
			if (stall[i] < stall[j])
			{
				int buff = stall[i];
				stall[i] = stall[j];
				stall[j] = buff;
			}

	// the best dynamic--------------------------------------
	for (i = 0; i < c; i++)
		dynamic[0][i] = stall[i] - stall[0] + 1;

	for (i = 1; i < m; i++)
		for (j = i; j < c; j++)
		{
			int min = 10000;
			for (k = i - 1; k < j; k++)
			{
				int buf = dynamic[i - 1][k] + stall[j] - stall[k + 1] + 1;
				if (min > buf) min = buf;
			}
			dynamic[i][j] = min;
		}
	printf("\n");
   for (i = 0; i < m; i++)
   {
	for (j = 0 ; j < c; j++)
		printf("%3d ", dynamic[i][j]);
	printf("\n");
   }
}