#include <fstream.h>
#include <stdlib.h>

int n, start, arr[101][101], arr2[101][101], chk[101];
long far *time1 = (long far *)0x0040006c;
long time2;

void input()
{
	int a, b;

	ifstream fin("path1.inp");
	fin >> n;
	while (1)
	{
		fin >> a >> b;
		if (a == -1 && b == -1) break;
		arr[a][b] = 1;
	}
	time2 = *time1;
}

void output()
{
	int l1, l2;

	ofstream fout("path1.out");
	for (l1 = 0; l1 < n; l1++)
	{
		for (l2 = 0; l2 < n; l2++)
			fout << arr2[l1][l2] << ' ';
		fout << endl;
	}
}

void dfs(int i)
{
	int l1;

//	if (*time1 - time2 > 17) { output(); exit(0); }
	chk[i] = 1;
	for (l1 = 0; l1 < n; l1++)
		if (arr[i][l1] == 1 && chk[l1] == 0)
		{
			arr2[start][l1]++;
			dfs(l1);
		}
	chk[i] = 0;
}

void process()
{
	int l1, l2;

	for (l1 = 0; l1 < n; l1++)
	{
		start = l1;
		dfs(l1);
	}
}

int main()
{
	input();
	process();
	output();
	return 0;
}