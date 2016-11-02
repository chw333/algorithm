#include <fstream.h>

int ta[ 5 ][ 5 ] = { { 100, 2, 2, 2, 2 },
		     { 100, 1, 3, 4, 3 },
		     { 100, 3, 1, 3, 4 },
		     { 100, 4, 3, 1, 3 },
		     { 100, 3, 4, 3, 1 } };

long arr[ 5 ], arr2[ 5 ];

int main( void )
{
	int prev, now, l1;
	long min;

	ifstream fin( "ddr.inp" ); ofstream fout( "ddr.out" );

	arr[ 0 ] = 0;
	arr[ 1 ] = -1;
	arr[ 2 ] = -1;
	arr[ 3 ] = -1;
	arr[ 4 ] = -1;
	prev = 0;
	while( 1 )
	{
		fin >> now;
		if( now == 0 ) break;
		arr2[ 0 ] = -1; arr2[ 1 ] = -1; arr2[ 2 ] = -1; arr2[ 3 ] = -1; arr2[ 4 ] = -1;
		for( l1 = 0; l1 < 5; l1++ )
		{
			if( arr[ l1 ] != -1 )
			{
				if( ( arr2[ l1 ] > arr[ l1 ] + ta[ prev ][ now ] && l1 != now ) || arr2[ l1 ] == -1 )
				{
					arr2[ l1 ] = arr[ l1 ] + ta[ prev ][ now ];
				}
				if( ( arr2[ prev ] > arr[ l1 ] + ta[ l1 ][ now ] && prev != now ) || arr2[ prev ] == -1 )
				{
					arr2[ prev ] = arr[ l1 ] + ta[ l1 ][ now ];
				}
			}
		}
		for( l1 = 0; l1 < 5; l1++ ) arr[ l1 ] = arr2[ l1 ];
		prev = now;
	}
	min = arr[ 0 ];
	for( l1 = 1; l1 < 5; l1++ )
	{
		if( min > arr[ l1 ] && arr[ l1 ] != -1 ) min = arr[ l1 ];
	}

	fout << min;

	fin.close(); fout.close();

	return 0;
}