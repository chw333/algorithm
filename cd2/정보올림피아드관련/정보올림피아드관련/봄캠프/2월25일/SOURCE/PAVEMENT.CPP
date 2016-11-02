#include <fstream.h>

const char infile[20] = "pavement.inp";
const char outfile[20] = "pavement.out";

int pavement[101][16384], check[3][7], n, m;
int w[15] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
int road[100][7], g;
int tile[9][3][3] = {{{1, 0, 0}, {1, 1, 0}, {1, 0, 0}}, {{0, 1, 0}, {1, 1, 0}, {0, 1, 0}}, {{0, 1, 0}, {1, 1, 0}, {1, 0, 0}}, {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}},  {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}, {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}}, {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}, {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}, {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
int tilex[9] = {3, 3, 3, 3, 2, 2, 2, 2, 3};
int tiley[9] = {2, 2, 2, 2, 3, 3, 3, 3, 3};
int tt[9] = {1, 2, 1, 2, 3, 2, 2, 3, 2};
void checking(int depth, int cost, int x);
void input();
void process();
void output();

main()
{
	input();
	process();
	output();
}

void input()
{
	int i, j;
	ifstream in(infile);
	in >> n >> m;
	for (i = 1; i <= n; i++)
		for (j = 0; j < m; j++)
			in >> road[i][j];
	return;
}

void process()
{
	int i, j, k, l, temp, pp;
	pavement[0][w[2 * m] - 1] = 1;
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < w[2 * m]; j++)
		{
			if (pavement[i - 1][j] != 0)
			{
  				if (i == n)
				{
					 temp = 0;
				}
				temp = j; pp = 2 * m - 1;
				for (k = 0; k < 2; k++)
					for (l = 0; l < m; l++)
					{
						if (temp >= w[pp])
						{ 
							check[k][l] = 3;
							temp -= w[pp];
						}
						else
							check[k][l] = 0;
						pp--;
					}
				temp = 0;
				for (k = 0; k < 2; k++)
					for (l = 0; l < m; l++)
						if (road[i - 2 + k][l] == 1 && check[k][l] == 0) check[k][l] = 1;
				for (k = 0; k < m; k++)
					check[2][k] = road[i][k], temp += (1 - road[i][k]);
				checking(0, pavement[i - 1][j] + temp, i);
			}
		}
	}
}

void output()
{
	int i, min = -1;
	ofstream out(outfile);
	for (i = 0; i < w[2 * m]; i ++)
	{
		if (pavement[n][i] != 0)
			if (pavement[n][i] < min || min == -1) min = pavement[n][i];
	}
	out << min - 1 << endl;
	out.close();
}

void checking(int depth, int cost, int x)
{
	int i, j, pp, temp, k;
	pp = 2 * m - 1;temp = 0;
	for (i = 1; i < 3; i++)
		for (j = 0; j < m; j++)
		{
			if (check[i][j] > 1) temp += w[pp--]; else pp--;
		}
	if (pavement[x][temp] == 0 || pavement[x][temp] > cost) pavement[x][temp] = cost;
	if (depth >= m - 1) return;  	
	for (i = 0; i < 9; i++)
	{
		temp = 0;
		if (tiley[i] + depth <= m)
		{
			for (j = 0; j < tilex[i]; j++)
				for (k = 0; k < tiley[i]; k++)
				{
					if (tile[i][j][k] == 1)
					{
						if (check[3 - tilex[i] + j][depth + k] > 1) goto a;					
					    if (check[3 - tilex[i] + j][depth + k] == 0) temp ++;
						if (check[3 - tilex[i] + j][depth + k] == 1) temp --;
					}
				}
			if (temp > 0)
			{
	 			for (j = 0; j < tilex[i]; j++)
					for (k = 0; k < tiley[i]; k++)
					{
						check[3 - tilex[i] + j][depth + k] += tile[i][j][k] * 2;
					}
				checking(depth + tt[i], cost - temp, x);
				for (j = 0; j < tilex[i]; j++)
					for (k = 0; k < tiley[i]; k++)
					{
						check[3 - tilex[i] + j][depth + k] -= tile[i][j][k] * 2;
					}
			}
		}
		else
		{
			break;
		}
a:;
	}
	checking(depth + 1, cost, x);
}
