#include <stdio.h>

FILE *in = fopen("door.in", "r");

int m, A[10];
int min = 1000;

void recur(int n, int l, int r, int move)
{
	if (n == m)
	{
		if (min > move)
			min = move;
	}
	else
	{
		if (A[n] <= l)
			recur(n+1, A[n], r, move+l-A[n]);
		else if (A[n] >= r)
			recur(n+1, l, A[n], move+A[n]-r);
		else
		{

			recur(n+1, A[n], r, move+A[n]-l);
			recur(n+1, l, A[n], move+r-A[n]);
		}
	}
}

int main(void)
{
	int a, b, i;

	fscanf(in, "%d", &m);
	for (i = 0; i < m; i++)
		fscanf(in, "%d", &A[i]);

	recur(0, 2, 5, 0);
	printf("%d\n", min);
	return 0;
}