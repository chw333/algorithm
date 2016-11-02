#include <fstream.h>

#define IF_NAME "palin.in"
#define OF_NAME "palin.out"
#define MAXN 5000
#define MAXINT 32767
#define min(a, b) ((a > b) ? b : a)

int n, sol;
char arr1[MAXN];

void input(void)
{
	ifstream in(IF_NAME);

	in >> n;
	for(int i = 0; i < n; i++)
		in >> arr1[i];

	in.close();
}

void dynamic(void)
{
	int table1[3][MAXN] = { 0 };

	for(int i = 1; i < n; i++)
	{
		for(int j = 0; j < n - i; j++)
		{
			int x = (arr1[j] == arr1[j + i]) ? table1[0][j + 1] : MAXINT;
			table1[2][j] = min(table1[1][j + 1] + 1, min(table1[1][j] + 1, x));
		}
		for(int j = 0; j < n - i + 1; j++)
		{
			table1[0][j] = table1[1][j];
			table1[1][j] = table1[2][j];
		}
	}
	sol = table1[2][0];
}

void output(void)
{
	ofstream out(OF_NAME);

	out << sol;

	out.close();
}

int main(void)
{
	input();
	dynamic();
	output();

	return 0;
}