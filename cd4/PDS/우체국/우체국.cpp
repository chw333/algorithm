#include <fstream.h>
#include <values.h>

#define IF_NAME "post.in"
#define OF_NAME "post.out"
#define MAXV 300
#define MAXP 30
#define min(a, b) (a > b) ? b : a

int v, p;
int arr1[MAXV], path1[MAXV];
long sol = MAXLONG;

void input(void)
{
	ifstream in(IF_NAME);

	in >> v >> p;
	for(int i = 0; i < v; i++)
		in >> arr1[i];

	in.close();
}

void dynamic(void)
{
	long table1[MAXV][MAXP];
	int table2[MAXV][MAXP];

	for(int i = 0; i < v; i++)
	{
		long total = 0;
		for(int j = 0; j < i; j++)
			total += (arr1[i] - arr1[j]);
		table1[i][0] = total;
	}
	if(p > 1)
		for(int i = 0; i < v; i++)
		{
			for(int j = 1; j < p; j++)
				table1[i][j] = MAXLONG;
			for(int j = 0; j < i; j++)
			{
				long total = 0;
				for(int k = j + 1; k < i; k++)
					total += min(arr1[i] - arr1[k], arr1[k] - arr1[j]);
				for(int k = 1; k < (min(p, j + 2)); k++)
				{
					if(table1[i][k] > table1[j][k - 1] + total)
					{
						table1[i][k] = table1[j][k - 1] + total;
						table2[i][k] = j;
					}
				}
			}
		}
	for(int i = p - 1; i < v; i++)
	{
		long total = 0;
		for(int j = i + 1; j < v; j++)
			total += (arr1[j] - arr1[i]);
		if(sol > table1[i][p - 1] + total)
		{
			sol = table1[i][p - 1] + total;
			for(int j = p - 1, k = i; j >= 0; j--)
			{
				path1[j] = arr1[k];
				k = table2[k][j];
			}
		}
	}
}

void output(void)
{
	ofstream out(OF_NAME);

	out << sol << endl;
	for(int i = 0; i < p; i++)
	{
		out << path1[i];
		if(i + 1 != p) out << " ";
	}

	out.close();
}

int main(void)
{
	input();
	dynamic();
	output();
	return 0;
}