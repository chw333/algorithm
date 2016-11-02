#include <stdio.h>
#include <fstream.h>

int E, F, N;
int P[500], W[500], K;
int D[10001], R[10001];

void Input()
{
	int i;

	ifstream in("juice.in");

	in >> E >> F;
	N = F - E;
	in >> K;
	for( i = 0; i < K; i++ )
		in >> P[i] >> W[i];

	in.close();
}

void Process()
{
	int i, j;

	for( i = 0; i < K; i++ )
	{
		for( j = W[i]; j <= N; j++ )
		{
			if( D[j] == 0 || D[j - W[i]] + P[i] < D[j] )
			{
				D[j] = D[j - W[i]] + P[i];
				R[j] = W[i];
			}
		}
	}
}

void Output()
{
	int i;

	ofstream out("juice.out");

	i = N;
	while( !( i == 0 || ( i > 0 && R[i] == 0 ) ) ) i = i - R[i];
	if( i > 0 ) out << "impossible";
	else out << D[N];

	out.close();
}

void main()
{
	Input();
	Process();
	Output();
}