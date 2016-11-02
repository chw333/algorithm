#include <fstream.h>
#include <stdlib.h>
#include <string.h>

int n, m, q, tsw, suc, cnt, inpn[101];
int cnt1[10], cnt2[10], chk1[101][10], chk2[101][10];
char inpstr[101][11], outstr[11], outstr2[11];
double p[10][10];
long far *time1 = (long far *)0x0040006c;
long time2;

void input()
{
	int l1, l2, l3, tmp2;
	char tmp[11];

	ifstream fin("lock1.inp");
	fin >> n >> m >> q;
	for (l1 = 0; l1 < n; l1++)
		for (l2 = 0; l2 < m; l2++)
			p[l1][l2] = 1;
	for (l1 = 1; l1 <= q; l1++)
	{
		for (l2 = 0; l2 < n; l2++)
		{
			fin >> tmp;
			fin >> tmp2;
			if (tmp2 == n) { strcpy(outstr, tmp); suc = 1; return; }
			if (tmp2 == 0) {
				for (l2 = 0; l2 < n; l2++)
					for (l3 = 0; l3 < m; l3++)
					{
						if (l3 == tmp[l2] - '0')
						{
							p[l2][l3] = 0;
							break;
						}
					}
			}
			else
			{
				strcpy(inpstr[cnt], tmp);
				inpn[cnt] = tmp2;
				cnt++;
				for (l2 = 0; l2 < n; l2++)
				{
					for (l3 = 0; l3 < m; l3++)
						if (l3 == tmp[l2] - '0')
						{
							p[l2][l3] *= (double)tmp2 / n;
						}
						else
						{
							p[l2][l3] *= (1 - (double)tmp2 / n) / (n - 1);
						}
				}
			}
		}
	}
}

void output(int sw)
{
	ofstream fout("lock1.out");
	if (sw == 0) fout << -1;
	else
		fout << outstr2;
	fout.close();
}

void backtracking(int i)
{
	int l1, l2, tmp, sw, order[10];

	if (*time1 - time2 > 52)
	{
		if (tsw == 1)
			output(1);
		else
			output(0);
		exit(0);
	}
	if (i == n)
	{
		for (l1 = 0; l1 < cnt; l1++)
		{
			if (cnt1[l1] != inpn[l1]) break;
		}
		if (l1 >= cnt)
		{
			if (tsw == 1) { output(0); exit(0); }
			tsw = 1;
			strcpy(outstr2, outstr);
		}
	}
	else
	{
		for (l1 = 0; l1 < m; l1++) order[l1] = l1;
		for (l1 = 0; l1 < m; l1++)
			for (l2 = l1 + 1; l2 < m; l2++)
				if (p[i][order[l1]] < p[i][order[l2]])
				{
					tmp = order[l1]; order[l1] = order[l2]; order[l2] = tmp;
				}
		for (l1 = 0; l1 < m; l1++)
		{
			for (l2 = 0; l2 < cnt; l2++)
			{
				sw = 0;
				if (inpstr[l2][i] == order[l1] + 48)
				{
					if (cnt1[l2] == inpn[l2]) sw = 1;
					cnt1[l2]++;
				}
				if (inpstr[l2][i] != order[l1] + 48)
				{
					if (cnt2[l2] == n - inpn[l2]) sw = 1;
					cnt2[l2]++;
				}
			}
			if (sw == 0)
			{
				outstr[i] = order[l1] + 48;
				backtracking(i + 1);
			}
			for (l2 = 0; l2 < cnt; l2++)
			{
				if (inpstr[l2][i] == order[l1] + 48)
					cnt1[l2]--;
				if (inpstr[l2][i] != order[l1] + 48)
					cnt2[l2]--;
			}
aa :
		}
	}
}

void process()
{
	backtracking(0);
}

void output()
{
	ofstream fout("lock1.out");
	fout << outstr;
}

int main()
{
	time2 = *time1;
	input();
	process();
	if (suc == 1)
		output();
	return 0;
}