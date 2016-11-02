#include <fstream.h>
#include <math.h>

const int Maxn = 100;
const char Infilename[30] = "treasure.inp";
const char Outfilename[30] = "treasure.out";

int n, m;
int data[Maxn];
int back[Maxn + 1][Maxn + 1];
long table[Maxn + 1][Maxn + 1];
long min[Maxn + 1][Maxn + 1];
long max[Maxn + 1][Maxn + 1];

int input();
int treasure();
long ma(long, long);
long mi(long, long);
int output();

int main()
{
	input();
	treasure();
	output();
	return 0;
}

int input()
{
	ifstream fin(Infilename);
	fin >> n >> m;
	for(int i = 0; i < n; i++)
		fin >> data[i];
	fin.close();
	return 0;
}

int output()
{
	ofstream fout(Outfilename);
	fout << table[m][n];
	fout.close();
	return 0;
}

int treasure()
{
	int i, j;
	for(i = 0; i <= n; i++)
		for(j = 0; j <= n; j++)
			table[i][j] = 100000000;
	table[0][0] = 0;
	int k;
	int sum = 0;
	for(i = 1; i <= n; i++)
	{
		sum += data[i - 1];
		min[1][i] = max[1][i] = sum;
		table[1][i] = 0;
	}
	for(i = 2; i <= m; i++)
	{
		for(j = i; j <= n; j++)
		{
			sum = 0;
			for(k = j; k >= i; k--)
			{
				sum += data[k - 1];
				if (ma(ma(abs(sum - max[i - 1][k - 1]), abs(sum - min[i - 1][k - 1])), max[i - 1][k - 1] - min[i - 1][k - 1]) < table[i][j])
				{
					table[i][j] = ma(ma(abs(sum - max[i - 1][k - 1]), abs(sum - min[i - 1][k - 1])), max[i - 1][k - 1] - min[i - 1][k - 1]);
					min[i][j] = mi(min[i - 1][k - 1], sum);
					max[i][j] = ma(max[i - 1][k - 1], sum);
					back[i][j] = k;
				}
			}
		}
	}
	return 0;
}

long ma(long a, long b)
{
	if (a > b) return a;
	else return b;
}

long mi(long a, long b)
{
	if (a < b) return a;
	else return b;
}