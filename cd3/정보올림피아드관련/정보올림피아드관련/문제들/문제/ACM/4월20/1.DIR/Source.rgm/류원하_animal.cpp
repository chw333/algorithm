#include <fstream.h>

long n,m;
char data[1000][1001];
long value[1000][1000];
long visit[1000][1000];
long maximum;
long cnt;

void i_stream()
{
	ifstream in ("animal.in");
	in >> m >> n;
	long i,j;
	for (i = 0;i < n;i++)
		in >> data[i];
	for (i = 0;i < n;i++)
		for (j = 0;j < m;j++)
			value[i][j] = -1;
}

void bfs_scan(long x, long y)
{
	long i,j,k;
	bool s;
	cnt++;
	/*if (value[x][y] != -1)
		return;*/
	value[x][y] = 0;
	visit[x][y] = cnt;
	for (k = 0;;k++)
	{
		s = false;
		for (i = 0;i < n;i++)
		{
			for (j = 0;j < m;j++)
			{
				if (value[i][j] == k && visit[i][j] == cnt)
				{
					s = true;
					if (i > 0 && data[i-1][j] != '#' && visit[i-1][j] != cnt)
					{
						value[i-1][j] = k+1;
						visit[i-1][j] = cnt;
					}
					if (j > 0 && data[i][j-1] != '#' && visit[i][j-1] != cnt)
					{
						value[i][j-1] = k+1;
						visit[i][j-1] = cnt;
					}
					if (i < n - 1 && data[i+1][j] != '#' && visit[i+1][j] != cnt)
					{
						value[i+1][j] = k+1;
						visit[i+1][j] = cnt;
					}
					if (j < m - 1 && data[i][j+1] != '#' && visit[i][j+1] != cnt)
					{
						value[i][j+1] = k+1;
						visit[i][j+1] = cnt;
					}
				}
			}
		}
		if (s == false)
			break;
		if (maximum < k)
			maximum = k;
	}
}

void process()
{
	long i,j,cnt;
	short int sw1, sw2;
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < m;j++)
		{
			if (data[i][j] != '#')
			{
				cnt = 0;
				sw1 = 0;
				sw2 = 0;
				if (i == 0 || data[i-1][j] == '#')
				{
					sw1++;
					cnt++;
				}
				if (j == 0 || data[i][j-1] == '#')
				{
					sw2++;
					cnt++;
				}
				if (i == n-1 || data[i+1][j] == '#')
				{
					sw1++;
					cnt++;
				}
				if (j == m-1 || data[i][j+1] == '#')
				{
					sw2++;
					cnt++;
				}
				if (cnt >= 3 || (cnt == 2 && sw1 == 1 && sw2 == 1))
						bfs_scan(i,j);
			}
		}
	}
}

void o_stream()
{
	ofstream out ("animal.out");
	out << maximum;
}

void main()
{
	i_stream();
	process();
	o_stream();
}