#include <iostream.h>
#include <fstream.h>
#include <time.h>

#define IF_NAME "walls.in"
#define OF_NAME "walls.out"
#define MAXM 200
#define MAXN 250
#define MAXL 30
#define MAXINT 32767

int m, n, l, sol1;
long sol2;
int arr1[MAXL], arr2[MAXM];
unsigned char arr3[MAXM][MAXN] = { 0 }, *map[MAXM] = { NULL };

void input(void)
{
	int temp;
	ifstream in(IF_NAME);

	in >> m;
	in >> n;
	in >> l;
	for(int i = 0; i < l; i++)
	{
		in >> arr1[i];
		arr1[i]--;
	}
	for(i = 0; i < m; i++)
	{
		in >> arr2[i];
		for(int j = 0; j < arr2[i]; j++)
		{
			in >> temp;
			arr3[i][j] = (unsigned char) (temp - 1);
		}
	}
	in.close();
}

int adj_area(int &n, int &m, unsigned char *arr1, unsigned char *arr2, char *arrt[])
{
	int flag = 0;
	for(int i = 0; i < n; i++)
	{
		arrt[*(arr1 + i)][*(arr1 + (i + 1) % n)] = 1;
		arrt[*(arr1 + (i + 1) % n)][*(arr1 + i)] = 1;
	}
	for(i = 0; i < m; i++)
		if(arrt[*(arr2 + i)][*(arr2 + (i + 1) % m)]) flag = 1;
	for(i = 0; i < n; i++)
	{
		arrt[*(arr1 + i)][*(arr1 + (i + 1) % n)] = 0;
		arrt[*(arr1 + (i + 1) % n)][*(arr1 + i)] = 0;
	}
	return flag;
}

void make_map(void)
{
	char *arrt[MAXN];
	ofstream out("temp.out");

	for(int i = 0; i < m; i++)
		map[i] = new unsigned char[m];
	for(i = 0; i < n; i++)
		arrt[i] = new char[n];
	for(i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
			*(arrt[i] + j) = 0;
	}
	for(i = 0; i < m; i++)
	{
		for(int j = i + 1; j < m; j++)
		{
			map[i][j] = map[j][i] = (char)adj_area(arr2[i], arr2[j], arr3[i], arr3[j], arrt);
			out << (char)('0' + map[i][j]) << " ";
		}
		out << endl;
	}
	for(i = 0; i < n; i++)
		delete arrt[i];
}

void delete_map(void)
{
	for(int i = 0; i < m; i++)
		delete map[i];
}

void bfs(int start, int *path1)
{
	const int qsize = MAXM * 2;
	int head = 0, tail = 0;
	int queue[qsize], path2[MAXM];

	for(int i = 0; i < m; i++)
		path2[i] = MAXINT;
	for(i = 0; i < m; i++)
		for(int j = 0; j < arr2[i]; j++)
			if(arr3[i][j] == start)
			{
				queue[head++] = i;
				path2[i] = 0;
				break;
			}
	while(head != tail)
	{
		if(tail == qsize) tail = 0;
		int t = queue[tail++];
		for(int i = 0; i < m; i++)
			if(map[t][i] && path2[i] > path2[t] + 1)
			{
				path2[i] = path2[t] + 1;
				if(head == qsize) head = 0;
				queue[head++] = i;
			}
	}
	for(i = 0; i < m; i++)
		path1[i] += path2[i];
}

void solve(void)
{
	int i;
	int path1[MAXM] = { 0 };

	for(i = 0; i < l; i++)
		bfs(arr1[i], path1);
	sol1 = 0;
	for(i = 1; i < m; i++)
		if(path1[sol1] > path1[i]) sol1 = i;
	sol2 = path1[sol1];
}

void process(void)
{
	make_map();
	solve();
	delete_map();
}

void output(void)
{
	ofstream out(OF_NAME);

	out << sol2 << endl;
	out << sol1 + 1;

	out.close();
}

int main(void)
{
	input();
	process();
	output();

	return 0;
}