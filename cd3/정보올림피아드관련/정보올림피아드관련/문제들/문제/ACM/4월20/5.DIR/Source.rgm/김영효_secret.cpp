#include "fstream.h"

int w, p;
int table[2000][2000];
int distance[2000];
int found[2000];

void input()
{
	ifstream in("secret.in");
	in >> w >> p;
	
	int i,j,tmp1,tmp2,tmp3;
	for( i=0; i<w; i++ )
		for( j=0; j<w; j++ )
			table[i][j] = 32000;

	for( i=0; i<p; i++ )
	{
		in >> tmp1 >> tmp2 >> tmp3;
		table[tmp1-1][tmp2-1] = tmp3;
		table[tmp2-1][tmp1-1] = tmp3;
	}
	for( i=0; i<w; i++ )
	{
		distance[i] = table[0][i];
		found[i] = 0;
	}
}

int minium(int a)
{
	int i,j;
	int minium=32000;
	int idx;
	for( i=0; i<w; i++ )
		if( !found[i] && minium > distance[i] )
		{
			minium = distance[i];
			idx = i;
		}
	if( a == 0 )
		return idx;


	for( i=0; i<w; i++ )
	{
		int rank=1;
		for( j=0; j<w; j++ )
			if( !found[j] && i != j && distance[i] > distance[j] ) rank++;

		if( rank == 2 ) return i;
	}

	return -32000;
}

void proc()
{
	int i,j,loc;

	found[0] = 1;

	for( i=1; i<w; i++ )
	{
		if( i == w-2 )
			loc = minium(1);
		else
			loc = minium(0);

		found[loc] = 1;

		for( j=0; j<w; j++ )
			if( !found[j] )
				if( table[loc][j] < distance[j] )
					distance[j] = table[loc][j];

	}
}

void output()
{
	ofstream out("secret.out");

	int i,sum=0;

	for( i=1; i<w; i++ )
		sum+=distance[i];
	out << sum << endl;
}

void main()
{
	input();
	proc();
	output();
}