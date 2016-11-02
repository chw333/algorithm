#include <fstream.h>
#include <stdlib.h>

ifstream fin;
ofstream fout;

int N, M, Q;

int data[100][12];
int nofc[100];

int answer_found = 0;
int answer[12];

void impossible()
{
	fout.open("lock1.out");
	fout << -1 << endl;
	fout.close();
	exit(0);
}

void input()
{
	char temp[12];

	int i, j;
	fin.open("lock1.inp");
	fin >> N >> M >> Q;
	for (i = 0; i < Q; i++)
	{
		fin >> temp >> nofc[i];
		for (j = 0; j < N; j++)
			data[i][j] = temp[j] - '0';
	}
	fin.close();
}

int his[12];
int depth;
int flag, tsum;

void backtrack(int x)
{
	int i;

	flag = tsum = 0;
	for (i = 0; i < Q; i++)
	{
		if (x == data[i][depth])
		{
			--nofc[i];
			if (nofc[i] == -1) flag = 1;
		}
		
		if (nofc[i] - (N-depth-1) > 0) flag = 1;
		tsum += nofc[i];
	}

	if (flag == 0)
	{
		his[depth++] = x;
		
		if (depth == N)
		{
			if (tsum == 0)
			{
				if (answer_found) impossible();
				answer_found = 1;
				for (i = 0; i < N; i++)
					answer[i] = his[i];
			}
		}
		else
		{
			for (i = 0; i < M; i++)
				backtrack(i);
		}
		
		his[--depth] = 0;
	}

	for (i = 0; i < Q; i++)
		if (x == data[i][depth])
			++nofc[i];
}

void process()
{
	int i;
	for (i = 0; i < M; i++)
		backtrack(i);
}

void output()
{
	int i;
	
	if (!answer_found) impossible();

	fout.open("lock1.out");
	for (i = 0; i < N; i++)
		fout << answer[i];
	fout << endl;
	fout.close();
}

void main()
{
	input();
	process();
	output();
}
