#include <fstream.h>
#include <stdlib.h>

long n;
long m;
long data[500][2];
long index[500];
long calc[10000];

int sort_function(const void *a, const void *b)
{
	long *p = (long *)a, *q = (long *)b;
	if (data[*p][1] > data[*q][1]) return 1;
	if (data[*p][1] < data[*q][1]) return -1;
	return 0;
}

void i_stream()
{
	ifstream in ("juice.in");
	long t1, t2;
	in >> t1 >> t2;
	n = t2 - t1;
	in >> m;
	long i;
	for (i = 0;i < m;i++)
	{
		index[i] = i;
		in >> data[i][0] >> data[i][1];
	}
	qsort(index,m,sizeof(index[0]),sort_function);
}

void process()
{
	long now,min;
	long i;
	for (now = 1;now <= n;now++)
	{
		min = 420000000;
		for (i = 0;i < m;i++)
		{
			if (data[index[i]][1] <= now)
			{
				if (calc[now - data[index[i]][1]] + data[index[i]][0] < min)
					min = calc[now - data[index[i]][1]] + data[index[i]][0];
			}
			else
				break;
		}
		calc[now] = min;
	}
}

void o_stream()
{
	ofstream out ("juice.out");
	if (calc[n] == 420000000)
		out << "impossible";
	else
		out << calc[n];
}

void main()
{
	i_stream();
	process();
	o_stream();
}