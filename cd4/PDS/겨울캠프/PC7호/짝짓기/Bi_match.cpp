#include <conio.h>
#include <stdio.h>

FILE *in = fopen("input.txt", "r");

#define s	0
#define t	(n+m+1)

int n, m;
int G[100][100];
int visit[100], from[100];

void DFS(int node)
{
	for (int i = 1; i <= t; i++)
		if (visit[i] == -1 && G[node][i] == 1)
		{
			visit[i] = 1;
			from[i] = node;
			DFS(i);
		}
}
void flow(void)
{
	int i, matched = 0, match[100] = {0, };

	while (1)
	{
		for (i = s; i <= t; i++)
			visit[i] = -1, from[i] = s;

		DFS(0);
		if (visit[t] == -1) break;
		matched++;

		for (i = t; i != s; i = from[i])
		{
//			printf("(%d, %d) ", i, from[i]);
			if (from[i] <= n && i >= n) match[from[i]] = i;
			G[from[i]][i] = 0, G[i][from[i]] = 1;
		}
//		printf("\n");
	}

	printf("%d\n", matched);
	for (i = 1; i <= n; i++)
		if (match[i]) printf("%d %d\n", i, match[i]-n);

}

int main(void)
{
	int i, j, k;

	fscanf(in, "%d %d", &n, &m);
	for (i = 1; i <= n; i++) {
		G[s][i] = 1;
		fscanf(in, "%d", &j);
		while (j--)
		{
			fscanf(in, "%d", &k);
			G[i][n+k] = 1;
		}
	}
	for (i = n+1; i <= n+m; i++)
		G[i][t] = 1;
	fclose(in);

	flow();

	return 0;
}