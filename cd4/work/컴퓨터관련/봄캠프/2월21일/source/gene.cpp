#include <fstream.h>
#include <stdlib.h>

ifstream fin;
ofstream fout;

int K, N;
char C1[2002];
char C2[2002];
char C3[3002];

int min(int t1, int t2) { return t1 > t2 ? t2 : t1; }
int max(int t1, int t2) { return t1 > t2 ? t1 : t2; }

void impossible()
{
	fout.open("gene.out");
	fout << 0 << endl;
	fout.close();
	exit(0);
}

void input()
{
	int i;
	char c;

	fin.open("gene.inp");

	fin >> K; N = K << 1;

	fin >> C1 >> C2 >> C3;
	for (i = K; i >= 1; i--) C1[i] = C1[i-1];
	for (i = K; i >= 1; i--) C2[i] = C2[i-1];
	for (i = N; i >= 1; i--) C3[i] = C3[i-1];

	fin.close();
}

char table[2001][1001];

int answer[2001], nof_answer = 0;

void dynamic()
{
	int i, j, mi;

	table[0][0] = 1;
	for (i = 1; i <= N; i++)
	{
		if (K-N+i <= 0 && C3[i] == C2[i] && table[i-1][0]) table[i][0] = 1;
		mi = min(i, K);
		for (j = max(1, K-N+i); j <= mi; j++)
			if ( C3[i] == C1[j] && table[i-1][j-1] ||
				 C3[i] == C2[i-j] && table[i-1][j] )
				table[i][j] = 1;
	}

	i = N; j = K; if (!table[i][j]) impossible();

	while (i > 0)
	{
		if (C3[i] == C1[j] && table[i-1][j-1])
		{
			answer[nof_answer++] = i;
			j--;
		}
			
		i--;
	}
}

void output()
{
	int i;
	fout.open("gene.out");
	for (i = nof_answer-1; i >= 0; i--)
		fout << answer[i] << ' ';
	fout << endl;
}

void main()
{
	input();
	dynamic();
	output();
}
