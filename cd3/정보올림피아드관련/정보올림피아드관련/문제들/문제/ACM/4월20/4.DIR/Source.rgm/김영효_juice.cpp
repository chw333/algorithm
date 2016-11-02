#include "fstream.h"

int water;
int table[10001]={0,};
int n;
int data[500][2];

void input()
{
	int tmp;
	ifstream in("juice.in");
	in >> tmp;
	water = -tmp;
	in >> tmp;
	water += tmp;
	
	in >> n;
	int i;
	for( i=0; i<n; i++ )
		in >> data[i][0] >> data[i][1];
}

void sort()
{
	int i,j,tmp;

	for( i=0; i<n; i++ )
		for( j=0; j<n-i-1; j++ )
			if( ((float)data[j][1]/data[j][0]) < ((float)data[j+1][1]/data[j+1][0]) )
			{
				tmp = data[j][0];
				data[j][0] = data[j+1][0];
				data[j+1][0] = tmp;

				tmp = data[j][1];
				data[j][1] = data[j+1][1];
				data[j+1][1] = tmp;
			}
}

void set(int a)
{
	int i=0;
	while( 1 )
	{
		if( data[i][1] <= a && table[a-data[i][1]] != -1 )
		{
			table[a] = data[i][0]+table[a-data[i][1]];
			break;
		}

		i++;
		if( i >= n )
		{
			table[a] = -1;
			break;
		}
	}
}

void proc()
{
	int i;
	sort();

	for( i=1; i<=water; i++ )
		set(i);
}

void output()
{
	ofstream out("juice.out");
	
	if( table[water] == -1 )
		out << "impossible";
	else
		out << table[water];
}

void main()
{
	input();
	proc();
	output();
}