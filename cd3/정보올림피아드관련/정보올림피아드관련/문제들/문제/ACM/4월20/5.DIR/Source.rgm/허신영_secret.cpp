#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>

int P, W;
int ipd[20000][3];
bool v[2000];
int min = 2000000000, min2 = 2000000000;

void Input()
{
	int i;
	int i_tmp1, i_tmp2, i_tmp3;

	ifstream in("secret.in");

	in >> W >> P;
	for( i = 0; i < P; i++ )
	{
		in >> i_tmp1 >> i_tmp2 >> i_tmp3;
		ipd[i][0] = i_tmp1 - 1;
		ipd[i][1] = i_tmp2 - 1;
		ipd[i][2] = i_tmp3;
	}

	in.close();
}

int sort_function( const void *a, const void *b )
{
	int *aa = (int *)a;
	int *bb = (int *)b;
	if( aa[2] > bb[2] ) return 1;
	else if( aa[2] < bb[2] ) return -1;
	else return 0;
}

int Data( int ii, int jj )
{
	int i;

	for( i = 0; i < P; i++ )
	{
		if( ( ipd[i][0] == ii && ipd[i][1] == jj ) || ( ipd[i][1] == ii && ipd[i][0] == jj ) )
			return ipd[i][2];
	}
	return 0;
}

void gg( int ie, int *a, int *b )
{
	int i;
	int i_tmp1 = -1, i_tmp2 = -1;

	for( i = 0; i < P; i++ )
	{
		if( ( ipd[i][0] == ie && v[ipd[i][1]] == false ) || ( ipd[i][1] == ie && v[ipd[i][0]] == false ) )
		{
			if( i_tmp1 == -1 )
				if( ipd[i][0] == ie ) i_tmp1 = ipd[i][1]; else i_tmp1 = ipd[i][0];
			else
			{
				if( ipd[i][0] == ie ) i_tmp2 = ipd[i][1]; else i_tmp2 = ipd[i][0];
				break;
			}
		}
	}
	*a = i_tmp1;
	*b = i_tmp2;
}

void BT( int idd, int sum )
{
	int i;
	int i_tmp1, i_tmp2;
	bool chk = false;

	v[idd] = true;
	for( i = 0; i < W; i++ )
	{
		if( v[i] == false ) continue;
		gg( i, &i_tmp1, &i_tmp2 );
		if( i_tmp1 != -1 ) { BT( i_tmp1, sum + Data( i, i_tmp1 ) ); chk = true; }
		if( i_tmp2 != -1 ) { BT( i_tmp2, sum + Data( i, i_tmp2 ) ); }
	}
	v[idd] = false;

	if( chk == false )
	{
		if( sum < min )
		{
			min2 = min;
			min = sum;
		}
		else if( sum > min && sum < min2 )
			min2 = sum;
	}
}

void Process()
{
	qsort( ipd, P, sizeof( ipd[0] ), sort_function );
	BT( 0, 0 );
}

void Output()
{
	ofstream out("secret.out");

	out << min2;

	out.close();
}

void main()
{
	Input();
	Process();
	Output();
}