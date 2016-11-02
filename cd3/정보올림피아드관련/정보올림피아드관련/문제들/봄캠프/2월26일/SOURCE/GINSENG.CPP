#include <fstream.h>

int madfucker[ 30 ];
int crazyfucker[ 30 ];
int superfucker[ 500 ];

int main( void )
{
	int n, m;
	int crazyfuckers, madfuckers = 0, superfuckers;
	int max, sum;
	int l1, l2, l3;
	int tmp1, res = 0;

	ifstream fin( "ginseng.inp" );

	fin >> n; 
	max = 0; sum = 0; madfucker[ 0 ] = 0; madfuckers = 1;
	fin >> m;
	for( l2 = 0; l2 < m; l2++ )
	{
		fin >> tmp1; tmp1 = 100 - tmp1;
		sum += tmp1;
		if( sum > max )
		{
			max = sum;
			madfuckers = 0;
		}
		if( sum == max )
		{
			if( madfuckers < 10 )
			{
				madfucker[ madfuckers++ ] = l2 + 1;
			}
		}
	}
	res += max;
	for( l1 = 1; l1 < n; l1++ )
	{
		fin >> m;
		max = 0; sum = 0; crazyfucker[ 0 ] = 0; crazyfuckers = 1;
		for( l2 = 0; l2 < m; l2++ )
		{
			fin >> tmp1; tmp1 = 100 - tmp1;
			sum += tmp1;
			if( sum > max )
			{
				max = sum;
				crazyfuckers = 0;
			}
			if( sum == max )
			{
				if( crazyfuckers < 10 )
				{
					crazyfucker[ crazyfuckers++ ] = l2 + 1;
				}
			}
		}
		superfuckers = 0;
		for( l2 = 0; l2 < madfuckers; l2++ )
		{
			for( l3 = 0; l3 < crazyfuckers; l3++ )
			{
				superfucker[ superfuckers++ ] = madfucker[ l2 ] + crazyfucker[ l3 ];
			}
		}
		for( l2 = 1; l2 < superfuckers; l2++ )
		{
			for( l3 = l2; l3 > 0; l3-- )
			{
				if( superfucker[ l3 ] < superfucker[ l3 - 1 ] )
				{
					tmp1 = superfucker[ l3 ]; superfucker[ l3 ] = superfucker[ l3 - 1 ]; superfucker[ l3 - 1 ] = tmp1;
				}
				else break;
			}
		}
		madfucker[ 0 ] = superfucker[ 0 ];
		madfuckers = 1;
		for( l2 = 1; l2 < superfuckers && madfuckers < 10; l2++ )
		{
			if( superfucker[ l2 ] != superfucker[ l2 - 1 ] )
			{
				madfucker[ madfuckers++ ] = superfucker[ l2 ];
			}
		}
		res += max;
	}

	fin.close();

	ofstream fout( "ginseng.out" );

	fout << res << endl;
	for( l1 = 0; l1 < madfuckers; l1++ )
	{
		fout << madfucker[ l1 ] << ' ';
	}

	fout.close();

	return 0;
}