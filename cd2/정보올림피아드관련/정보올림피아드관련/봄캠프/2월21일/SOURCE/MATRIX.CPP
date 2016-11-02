// DJGPP
#include <fstream.h>
#include <bios.h>
#include <stdlib.h>
#include <string.h>

#define Timelimit 30

long timer_start;

ifstream fin;
ofstream fout;

int row, col;
int hor, ver;
int matrix[60][60];

int horsum[60][60][60];
int versum[60][60][60];

int dyn[60][60];
int tra[60][60];

int horcut[60];
int vercut[60];

int maxsum[60][60];

int best_answer = 2147483647;
int best_horcut[60];
int best_vercut[60];
int best_each[60][60];

int each[60][60];

int maxF(int t1, int t2)
{
	return t1 > t2 ? t1 : t2;
}

int minF(int t1, int t2)
{
	return t1 > t2 ? t2 : t1;
}

void input()
{
	int i, j;
	fin.open("matrix.inp");
	fin >> row >> col;
	fin >> hor >> ver; hor++; ver++;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			fin >> matrix[i][j];
	fin.close();
}

void output()
{
	int i, j, i2, j2, sum;
	
	fout.open("matrix.out");
	fout << best_answer << endl;

	for (i = 1; i <= hor; i++)
		for (j = 1; j <= ver; j++)
			fout << best_horcut[i] << ' ' << best_vercut[j] << ' '
			     << best_horcut[i+1]-1 << ' ' << best_vercut[j+1]-1 << ' '
				 << best_each[i][j] << endl;
	fout.close();
}

void init()
{
	int i, j, k;

	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
		{
			horsum[i][j][j] = matrix[i][j];
			for (k = j+1; k <= col; k++)
				horsum[i][j][k] = horsum[i][j][k-1] + matrix[i][k];
		}

	for (i = 1; i <= col; i++)
		for (j = 1; j <= row; j++)
		{
			versum[i][j][j] = matrix[j][i];
			for (k = j+1; k <= row; k++)
				versum[i][j][k] = versum[i][j][k-1] + matrix[k][i];
		}
}

void dynamic()
{
	int i, j, k, p;
	int i2, j2;
	int tsum;

	for (i = 1; i <= row; i++)
	{
		dyn[1][i] = dyn[1][i-1] + horsum[i][1][col];
		tra[1][i] = 0;
	}
	for (i = 2; i <= hor; i++)
		for (j = i; j <= row; j++)
		{
			tsum = 0; dyn[i][j] = 2147483647;
			for (k = j; k >= i; k--)
			{
				tsum += horsum[k][1][col];
				if (maxF(tsum, dyn[i-1][k-1]) < dyn[i][j])
				{
					dyn[i][j] = maxF(tsum, dyn[i-1][k-1]);
					tra[i][j] = k-1;
				}
			}
		}

	j = row; horcut[hor+1] = j+1;
	for (i = hor; i >= 1; i--)
	{
		j = tra[i][j];
		horcut[i] = j+1;
	}

	int temparr[60];
	int tmax;

	for (i = 1; i <= col; i++)
	{
		for (j = 1; j <= row; j++) temparr[j] = 0;
		for (j = i; j <= col; j++)
		{
			p = 0;
			for (k = 1; k <= row; k++)
			{
				if (horcut[p+1] == k) p++;
				temparr[p] += matrix[k][j];
			}

			tmax = 0;
			for (k = 1; k <= hor; k++)
				if (temparr[k] > tmax)
					tmax = temparr[k];

			maxsum[i][j] = tmax;
		}
	}

	for (i = 1; i <= col; i++)
		dyn[1][i] = maxsum[1][i];
	for (i = 2; i <= ver; i++)
		for (j = i; j <= col; j++)
		{
			dyn[i][j] = 2147483647;
			for (k = i; k <= j; k++)
				if (maxF(dyn[i-1][k-1], maxsum[k][j]) < dyn[i][j])
				{
					dyn[i][j] = maxF(dyn[i-1][k-1], maxsum[k][j]);
					tra[i][j] = k-1;
				}
		}

	j = col; vercut[ver+1] = j+1;
	for (i = ver; i >= 1; i--)
	{
		j = tra[i][j];
		vercut[i] = j+1;
	}

	for (i = 1; i <= hor; i++)
		for (j = 1; j <= ver; j++)
		{
			each[i][j] = 0;
			for (i2 = horcut[i]; i2 < horcut[i+1]; i2++)
				for (j2 = vercut[j]; j2 < vercut[j+1]; j2++)
					each[i][j] += matrix[i2][j2];
		}

	best_answer = dyn[ver][col];
	for (i = 1; i <= hor+1; i++) best_horcut[i] = horcut[i];
	for (i = 1; i <= ver+1; i++) best_vercut[i] = vercut[i];
	for (i = 1; i <= hor; i++)
		for (j = 1; j <= ver; j++)
			best_each[i][j] = each[i][j];
}

int sel_table[4], nof_sel;
int selection;

int show;

void improve_solution()
{
	int i, j, secty, sectx, max;
	int flag;

	srand(biostime(0, 0));
	while (biostime(0, 0) - timer_start < Timelimit)
	{
		max = 0;
		for (i = 1; i <= hor; i++)
		{
			for (j = 1; j <= ver; j++)
				if (each[i][j] > max)
				{
					max = each[i][j];
					secty = i;
					sectx = j;
				}
		}

		if (max < best_answer)
		{
			best_answer = max;
			for (i = 1; i <= hor; i++) best_horcut[i] = horcut[i];
			for (i = 1; i <= ver; i++) best_vercut[i] = vercut[i];
			for (i = 1; i <= hor; i++)
				for (j = 1; j <= ver; j++)
					best_each[i][j] = each[i][j];
		}

		nof_sel = 0;
		if (horcut[secty+1] - horcut[secty] != 1)
		{
			if (sectx < ver) sel_table[nof_sel++] = 1;
			if (sectx > 1  ) sel_table[nof_sel++] = 3;
		}
		if (vercut[sectx+1] - vercut[sectx] != 1)
		{
			if (secty > 1  ) sel_table[nof_sel++] = 0;
			if (secty < hor) sel_table[nof_sel++] = 2;
		}

		if (nof_sel == 0) output();

		selection = sel_table[rand() % nof_sel];

		if (selection == 0)
		{
			for (i = 1; i <= ver; i++)
			{
				each[secty][i]   -= horsum[horcut[secty]][vercut[i]][vercut[i+1]-1];
				each[secty-1][i] += horsum[horcut[secty]][vercut[i]][vercut[i+1]-1];
			}
			horcut[secty]++;
		}
		else if (selection == 1)
		{
			for (i = 1; i <= hor; i++)
			{
				each[i][sectx]   -= versum[vercut[sectx+1]-1][horcut[i]][horcut[i+1]-1];
				each[i][sectx+1] += versum[vercut[sectx+1]-1][horcut[i]][horcut[i+1]-1];
			}
			vercut[sectx+1]--;
		}
		else if (selection == 2)
		{
			for (i = 1; i <= ver; i++)
			{
				each[secty][i]   -= horsum[horcut[secty+1]-1][vercut[i]][vercut[i+1]-1];
				each[secty+1][i] += horsum[horcut[secty+1]-1][vercut[i]][vercut[i+1]-1];
			}
			horcut[secty+1]--;
		}
		else if (selection == 3)
		{
			for (i = 1; i <= hor; i++)
			{
				each[i][sectx]   -= versum[vercut[sectx]][horcut[i]][horcut[i+1]-1];
				each[i][sectx-1] += versum[vercut[sectx]][horcut[i]][horcut[i+1]-1];
			}
			vercut[sectx]++;
		}
	}
}

void main()
{
	timer_start = biostime(0, 0);
	input();
	init();
	dynamic();
	if (minF(hor, ver) >= 2) improve_solution();
	output();
}
