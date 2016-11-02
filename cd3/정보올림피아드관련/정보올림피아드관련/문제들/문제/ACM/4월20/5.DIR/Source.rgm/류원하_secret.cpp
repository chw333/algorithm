#include <fstream.h>
#include <stdlib.h>

long n,m;
long data[20000][3];
char used[20001];
long connected[2000];
long index[20000];
long calc;
long min = 65535;
long queue[500000];
long count;
long check[2000];

int sort_function(const void *a, const void *b)                                                                                                                                    // sinjae
{
	long *p = (long *)a, *q = (long *)b;
	if (data[*p][2] > data[*q][2]) return 1;
	if (data[*p][2] < data[*q][2]) return -1;
	return 0;
}

void i_stream()
{
	ifstream in ("secret.in");
	in >> n >> m;
	long i;
	for (i = 0;i < m;i++)
	{
		in >> data[i][0] >> data[i][1] >> data[i][2];
		data[i][0]--;
		data[i][1]--;
		index[i] = i;
	}
	for (i = 0;i < n;i++)
		connected[i] = i;
	qsort(index,m,sizeof(index[0]),sort_function);
}

void change(long a, long b)
{
	long i;
	for (i = 0;i < n;i++)
	{
		if (connected[i] == b)
			connected[i] = a;
	}
}

int cycle(long a, long b)
{
	count++;
	long h = -1, f = 1,k;
	char tused[20001];
	queue[f] = data[index[a]][1];
	tused[index[b]] = '1';
	for (;;)
	{
		h++;
		check[queue[h]] = count;
		if (h == n-1)
			break;
		if (h != 0 && queue[h] == data[index[a]][0] || h == f)
			return 0;
		for (k = 0;k < m;k++)
		{
			if (data[index[k]][0] == queue[h] && used[index[k]] == '1' && tused[index[k]] != '1')
			{
				if (check[data[index[k]][1]] == count)
					return 0;
				queue[f] = data[index[k]][1];
				f++;
				tused[index[k]] = '1';
			}
			if (data[index[k]][1] == queue[h] && used[index[k]] == '1' && tused[index[k]] != '1')
			{
				if (check[data[index[k]][0]] == count)
					return 0;
				queue[f] = data[index[k]][0];
				f++;
				tused[index[k]] = '1';
			}
		}
	}
	return 1;
}

void process()
{
	connected[data[index[0]][1]] = connected[data[index[0]][0]];
	calc += data[index[0]][2];
	used[index[0]] = '1';
	long i,j;
	for (i = 1;i < m;i++)
	{
		if (connected[data[index[i]][0]] != connected[data[index[i]][1]])
		{
			change(connected[data[index[i]][0]], connected[data[index[i]][1]]);
			calc += data[index[i]][2];
			used[index[i]] = '1';
		}
	}
	
	for (i = 0;i < m;i++)
	{
		if (used[index[i]] == '1')
		{
			for (j = 0;j < m;j++)
			{
				if (used[index[j]] != '1')
				{
					if (cycle(i,j) == 1)
					{
						if (min > data[index[j]][2] - data[index[i]][2])
							min = data[index[j]][2] - data[index[i]][2];
					}
				}
			}
		}
	}
}

void o_stream()
{
	ofstream out ("secret.out");
	out << calc + min;
}

void main()
{
	i_stream();
	process();
	o_stream();
}