// IOI2002 2002. 6 고등부 도미노(domino)

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

struct posi_list
{
	int y1, x1, y2, x2;
	posi_list* next;
};

int n;
int m[MAX_N][MAX_N+1];
int num[MAX_N+1][MAX_N+1];
bool visited[MAX_N+1][MAX_N+1];
posi_list* posi[MAX_N+1][MAX_N+1];
posi_list* header[MAX_N+1][MAX_N+1]; 
int dir[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int res[MAX_N][MAX_N+1];
int res_n;
bool found = false;

void Input_data()
{
	int i, j;
	FILE *inf;

	inf = fopen(INPUT_FILE, "r");

	fscanf(inf, "%d\n", &n);	

	for (i=0; i<n; i++)
		for (j=0; j<n+1; j++)
			fscanf(inf, "%d", &m[i][j]);

	fclose(inf);
}

void add(int p, int q, int y1, int x1, int y2, int x2)
{
	int temp;
	
	if (p>q) {
		temp = p;	p = q;		q = temp;
	}

	num[p][q]++;
	posi[p][q]->next = (posi_list*) malloc(sizeof(posi_list));
	posi[p][q] = posi[p][q]->next;
	posi[p][q]->y1 = y1;			posi[p][q]->x1 = x1;
	posi[p][q]->y2 = y2;			posi[p][q]->x2 = x2;
	posi[p][q]->next = NULL;
}

void preprocess()
{
	int i, j;
	int p, q;

	for (i=1; i<=n; i++)
		for (j=i; j<=n; j++)
		{
			posi[i][j] = (posi_list*) malloc(sizeof(posi_list));
			posi[i][j]->next = NULL;
			header[i][j] = posi[i][j];
		}

	for (i=0; i<n; i++)
	{
		p = m[i][0];

		for (j=1; j<n+1; j++)
		{
			q = m[i][j];
			add(p, q, i, j-1, i, j);
			p = q;
		}
	}

	for (i=0; i<n+1; i++)
	{
		p = m[0][i];

		for (j=1; j<n; j++)
		{
			q = m[j][i];
			add(p, q, j-1, i, j, i);
			p = q;
		}
	}
}
/*
int check()
{
}
*/
bool out(int y, int x)
{
	if ((y<0) || (x<0) || (y>=n) || (x>n)) return true;
	else return false;
}

void decrease(int n1, int n2)
{
	if (n1<n2) num[n1][n2]--;
	else num[n2][n1]--;
}

void increase(int n1, int n2)
{
	if (n1<n2) num[n1][n2]++;
	else num[n2][n1]++;
}

void Output_result()
{
	int i, j;
	FILE *ouf;

	ouf = fopen(OUTPUT_FILE, "w");

	if (!found) fprintf(ouf, "Impossible\n");
	else
	{
		for (i=0; i<n; i++)
		{
			for (j=0; j<n+1; j++)
				fprintf(ouf, "%d ", res[i][j]);
			fprintf(ouf, "\n");
		}
	}
}

void find_solution()
{
	int i, j;
	int p, q, min;
	posi_list* posi;
	int y1, x1, y2, x2;
	int yy, xx;

	printf("%d\n", res_n);

	if (res_n == MAX_N * (MAX_N+1) / 2)	
	{
		found = true;
		Output_result();
		exit(0);
	}

	min = MAX_N * MAX_N * 2 + 1;
	for (i=1; i<=n;	i++)
		for (j=i; j<=n; j++)
			if ((!visited[i][j]) && (num[i][j] < min))
			{
				min = num[i][j];	p = i;	q = j;
			}

	if (min == 0) return;

	posi = header[p][q];

	visited[p][q] = true;

	while(posi->next != NULL)
	{
		posi = posi->next;
		y1 = posi->y1;		x1 = posi->x1;
		y2 = posi->y2;		x2 = posi->x2;

		if (res[y1][x1] || res[y2][x2]) continue; 

		for (i=0; i<4; i++)
		{
			yy = y1 + dir[i][0];	xx = x1 + dir[i][1];
			if ((out(yy,xx)) || (yy == y2) && (xx == x2)) continue;

			if (!res[yy][xx]) decrease(m[y1][x1], m[yy][xx]);
		}

		for (i=0; i<4; i++)
		{
			yy = y2 + dir[i][0];	xx = x2 + dir[i][1];
			if ((out(yy,xx)) || (yy == y1) && (xx == x1)) continue;

			if (!res[yy][xx]) decrease(m[y2][x2], m[yy][xx]);
		}

		res_n++;
		res[y1][x1] = res_n;	res[y2][x2] = res_n;

		find_solution();

		res_n--;
		res[y1][x1] = 0;		res[y2][x2] = 0;

		for (i=0; i<4; i++)
		{
			yy = y1 + dir[i][0];	xx = x1 + dir[i][1];
			if ((out(yy,xx)) || (yy == y2) && (xx == x2)) continue;

			if (!res[yy][xx]) increase(m[y1][x1], m[yy][xx]);
		}

		for (i=0; i<4; i++)
		{
			yy = y2 + dir[i][0];	xx = x2 + dir[i][1];
			if ((out(yy,xx)) || (yy == y1) && (xx == x1)) continue;

			if (!res[yy][xx]) increase(m[y2][x2], m[yy][xx]);
		}
	}

	visited[p][q] = false;
}

void Solve()
{
	preprocess();
	find_solution();
	Output_result();
}

void main()
{
	Input_data();
	Solve();
}