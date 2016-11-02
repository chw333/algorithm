#include "fstream.h"
#include "stdlib.h"

int kr,kc,lr,lc;   // r : ±æÀÌ c : ³Ðºñ
char data[500][100];
int color[500][100];
int	sum=0;
int dep=-1;
int pass=0;
int maxr=0;
//ofstream out("tetris.out");

void input()
{
	int i,j;
	ifstream in("tetris.in");
	
	in >> kr >> kc;
	for( i=0; i<kr; i++ )
	{
		for( j=0; j<kc; j++ )
		{
			in >> data[i][j];
			color[i][j] = 1;
		}
	}
	
	in >> lr >> lc;
	for( i=kr; i<kr+lr; i++ )
	{
		for( j=0; j<lc; j++ )
		{
			in >> data[i][j];
			color[i][j] = 2;
		}
	}

	int maxl = 0;
	int ex=0;
	for( i=0; i<kc; i++ )
	{
		for( j=0; j<kr; j++ )
		{
			if( data[j][i] == '#' )
			{
				ex = 1;
				break;
			}
		}
		if( ex ) break;
		maxl++;
	}

	if( maxl )
	{
		for( i=0; i<kr; i++ )
		{
			for( j=maxl; j<kc; j++ )
			{
				data[i][j-maxl] = data[i][j];
				data[i][j] = '.';
			}
		}
	}

	ex=0;
	for( i=lc-1; i>=0; i-- )
	{
		for( j=0; j<kr; j++ )
		{
			if( data[j][i] == '#' )
			{
				ex = 1;
				break;
			}
		}
		if( ex ) break;
		maxr++;
	}
}	

void zzambbong()
{
	char upd[500][100];
	int upc[500][100];
	char tmp[500][100];
	int tmpcolor[500][100];
	int right=0, i, j;
	int up=0;

	while( 1 )
	{
		for( i=0; i<kr+lr; i++ )
			for( j=0; j<lc; j++ )
			{
				tmp[i][j] = data[i][j];
				tmpcolor[i][j] = color[i][j];
			}
		for( i=kr+lr; i<(kr*2)+lr; i++ )
			for( j=0; j<lc; j++ )
			{
				tmp[i][j] = '.';
				tmpcolor[i][j] = 0;
			}

		for( i=kr-1; i>=0; i-- )
			for( j=kc-1; j>=0; j-- )
			{
				tmp[i][j+right] = tmp[i][j];
				tmpcolor[i][j+right] = tmpcolor[i][j];
				if( right != 0 )
				{
					tmp[i][j] = '.';
					tmpcolor[i][j] = 0;
				}
			}

		int hole=kr-1;
		while( 1 )
		{
			int set=1;
			int flag=0;
			//for( i=hole-(kr-1); i<=hole; i++ )
			for( i=0; i<kr+lr; i++ )
			{
				for( j=0; j<lc; j++ )
				{
					if( tmpcolor[i][j] == 1 ) set=0;
					if( tmp[i][j] == '#' && tmpcolor[i][j] == 1 && tmp[i+1][j] == '#' && tmpcolor[i+1][j] == 2 )
					{
						flag=1;
						break;
					}
				}
			}
			if( flag )
				break;

			if( set )
			{
				pass=1;
				return;
			}

			for( i=hole; i>=hole-(kr-1); i-- )
				for( j=right+kc-1; j>=right; j-- )
				{
					if( tmpcolor[i][j] == 1 )
					{
						if( tmp[i][j] == '.' && tmp[i+1][j] == '#' && tmpcolor[i][j] == 1 && tmpcolor[i+1][j] == 2 )
						{
							tmpcolor[i+1][j] = 2;
							tmp[i+1][j] = '#';
						}
						else if( tmp[i][j] == '#' && tmp[i+1][j] == '.' && tmpcolor[i][j] == 1 && tmpcolor[i+1][j] == 2 )
						{
							tmpcolor[i+1][j] = 1;
							tmp[i+1][j] = '#';
						}
						else
						{
							tmpcolor[i+1][j] = tmpcolor[i][j];
							tmp[i+1][j] = tmp[i][j];
						}
						tmp[i][j] = '.';
						tmpcolor[i][j] = 0;
					}
				}
			hole++;
		}

		if( hole-1 > dep )
		{
			dep = hole-1;
			for( i=0; i<(kr*2)+lr; i++ )
				for( j=0; j<lc; j++ )
				{
					upd[i][j] = tmp[i][j];
					upc[i][j] = tmpcolor[i][j];
					up = 1;
				}
		}
/*
		for( i=0; i<(kr*2)+lr; i++ )
		{
			for( j=0; j<lc; j++ )
			{

				out << tmp[i][j] << " ";
			}
			out	<< endl;
		}
		out << endl;
*/

		right++;
		if( right > maxr )
			break;
	}


	if( up )
	{
		for( i=0; i<(kr*2)+lr; i++ )
			for( j=0; j<lc; j++ )
			{
				data[i][j] = upd[i][j];
				color[i][j] = upc[i][j];
			}
	}
}

void output()
{
	int low=-1,i,j;
	ofstream out("tetris.out");

	if( pass )
	{
		out << "pass" << endl;
		return;
	}
	for( i=((kr*2)+lr)-1; i>=0; i-- )
	{
		for( j=lc-1; j>=0; j-- )
		{
			if( data[i][j] == '#' && color[i][j] == 1 )
			{
				low = i;
				break;
			}
			if( low != -1 ) break;
		}
		if( low != -1 ) break;
	}
	
	int dap = kr-1-low;
	if( dap < 0 )
		dap *= -1;
	out << dap << endl;
}

void proc()
{
	zzambbong();
	if( pass ) return;
}

void main()
{
	input();
	proc();
	output();
}