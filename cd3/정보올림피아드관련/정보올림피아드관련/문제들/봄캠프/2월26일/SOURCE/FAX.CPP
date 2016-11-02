#include <fstream.h>

int abs( int x );

int fucker[ 4 ] = { 1, 86, 172, 256 };
int arr[ 100 ];
int sucker[ 100 ][ 4 ], backer[ 100 ][ 4 ];
char str[ 10000 ];
int n, m, tmp1, tmp2, min;

int main( void )
{
	int l1, l2, l3;
	int z;

	ifstream fin( "fax.inp" );

	fin >> n >> m;
	for( l1 = 0; l1 < n; l1++ )
	{
		fin >> arr[ l1 ];
	}

	fin.close();

	for( l1 = 0; l1 < 4; l1++ )
	{
		sucker[ 0 ][ l1 ] = 2 * m + abs( fucker[ l1 ] - arr[ 0 ] );
	}
	for( l1 = 1; l1 < n; l1++ )
	{
		for( l2 = 0; l2 < 4; l2++ )
		{
			tmp2 = abs( fucker[ l2 ] - arr[ l1 ] );
			if( l2 == 0 )
			{
				sucker[ l1 ][ 0 ] = sucker[ l1 - 1 ][ 0 ] + m + tmp2;
			}
			else
			{
				sucker[ l1 ][ l2 ] = sucker[ l1 - 1 ][ 0 ] + 3 * m + tmp2;
			}
			backer[ l1 ][ l2 ] = 0;
			for( l3 = 1; l3 < 4; l3++ )
			{
				if( l2 == l3 )
				{
					tmp1 = sucker[ l1 - 1 ][ l3 ] + m + tmp2;
				}
				else
				{
					tmp1 = sucker[ l1 - 1 ][ l3 ] + 3 * m + tmp2;
				}
				if( sucker[ l1 ][ l2 ] > tmp1 )
				{
					sucker[ l1 ][ l2 ] = tmp1;
					backer[ l1 ][ l2 ] = l3;
				}
			}
		}
	}

	ofstream fout( "fax.out" );

	min = sucker[ n - 1 ][ 0 ]; tmp1 = 0;
	for( l1 = 1; l1 < 4; l1++ )
	{
		if( min > sucker[ n - 1 ][ l1 ] )
		{
			min = sucker[ n - 1 ][ l1 ];
			tmp1 = l1;
		}
	}

	fout << min << endl;

	for( l1 = n - 1, z = 0; l1 > 0; l1-- )
	{
		if( backer[ l1 ][ tmp1 ] == tmp1 )
		{
			str[ z++ ] = '0';
		}
		else
		{
			switch( backer[ l1 ][ tmp1 ] )
			{
				case 0:
					str[ z++ ] = '0';
					str[ z++ ] = '0';
					str[ z++ ] = '1';
					break;
				case 1:
					str[ z++ ] = '1';
					str[ z++ ] = '0';
					str[ z++ ] = '1';
					break;
				case 2:
					str[ z++ ] = '0';
					str[ z++ ] = '1';
					str[ z++ ] = '1';
					break;
				case 3:
					str[ z++ ] = '1';
					str[ z++ ] = '1';
					str[ z++ ] = '1';
					break;
			}
		}
		tmp1 = backer[ l1 ][ tmp1 ];
	}
	switch( backer[ l1 ][ tmp1 ] )
	{
		case 0:
			str[ z++ ] = '0';
			str[ z++ ] = '0';
			break;
		case 1:
			str[ z++ ] = '1';
			str[ z++ ] = '0';
			break;
		case 2:
			str[ z++ ] = '0';
			str[ z++ ] = '1';
			break;
		case 3:
			str[ z++ ] = '1';
			str[ z++ ] = '1';
			break;
	}
	for( z--; z >= 0; z-- )
	{
		fout << str[ z ];
	}

	fout.close();

	return 0;
}

int abs( int x )
{
	if( x < 0 ) return -x;
	return x;
}