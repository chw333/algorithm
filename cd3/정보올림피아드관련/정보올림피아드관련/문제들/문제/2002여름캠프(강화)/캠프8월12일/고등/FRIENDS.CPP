// IOI2002 2002. 7 模备客 利(friends)

#include <stdio.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_N 30000
#define MAX_M 100000

int N, M;
int party[MAX_N+1], enemy[MAX_N+1];
int party_n[MAX_N+1];
int dat[MAX_M][2];
int res_n;
int res[MAX_M][2];
int party_num;

void Input_data()
{
	FILE *inf;
	int i;

	inf = fopen(INPUT_FILE, "r");

	fscanf(inf, "%d %d\n", &N, &M);	

	for (i=0; i<M; i++)
		fscanf(inf, "%d %d\n", &dat[i][0], &dat[i][1]);	

	fclose(inf);
}

void union_find(int x, int y)
{
	int xx, yy;

	xx = x;		yy = y;

	while (party[x] > 0)	x = party[x];
	while (party[y] > 0)	y = party[y];

	if (party[x] != party[y])
	{
		party[y] = x;
		party_n[x] += party_n[y];
	}
}

void Solve()
{
	int i;
	int x, y;

	for (i=1; i<=N; i++)
	{
		party[i] = -i;
		party_n[i] = 1;
	}
	
	for (i=0; i<M; i++)
	{
		x = dat[i][0];	y = dat[i][1];

		if (x == 0) // type 1
		{
			x = y;	y = enemy[y];

			while (party[x] > 0)	x = party[x];
			while (party[y] > 0)	y = party[y];

			res[res_n][0] = party_n[x] - 1;
			res[res_n][1] = party_n[y];
			res_n++;
			continue;
		}

		// type 2

		while (party[x] > 0)	x = party[x];
		while (party[y] > 0)	y = party[y];

		if (party[x] != party[y])
		{
			x = dat[i][0];	y = dat[i][1];
			if (enemy[y] == 0) enemy[y] = x;
			else union_find(x, enemy[y]);
			if (enemy[x] == 0) enemy[x] = y;
			else union_find(y, enemy[x]);
		}
	}
}

void Output_result()
{
	int i;
	FILE *ouf;

	ouf = fopen(OUTPUT_FILE, "w");

	fprintf(ouf, "%d\n", res_n);	

	for (i=0; i<res_n; i++)
		fprintf(ouf, "%d %d\n", res[i][0], res[i][1]);

	fclose(ouf);
}

void main()
{
	Input_data();
	Solve();
	Output_result();
}