#include <fstream.h>
#include <windows.h>
#include <stdlib.h>

void bck_tr( int x );
void bfs1( int x );
void bfs2( int x );

int queue[ 120 ];
int degree1[ 120 ], degree2[ 120 ];
int ta1[ 110 ][ 110 ], ta2[ 110 ][ 110 ], ta3[ 110 ][ 110 ];
int fucking1[ 110 ][ 110 ], fucking2[ 110 ][ 110 ];
int arr[ 110 ], chk[ 110 ];
int n;
int sw;
DWORD tm = GetTickCount();

int main( void )
{
	int l1, l2, l3;

	ifstream fin( "graph.inp" );

	fin >> n;
	for( l1 = 0; l1 < n; l1++ )
	{
		degree1[ l1 ] = 0;
		for( l2 = 0; l2 < n; l2++ )
		{
			fin >> ta1[ l1 ][ l2 ];
			if( ta1[ l1 ][ l2 ] == 1 ) degree1[ l1 ]++;
		}
	}
	for( l1 = 0; l1 < n; l1++ )
	{
		degree2[ l1 ] = 0;
		for( l2 = 0; l2 < n; l2++ )
		{
			fin >> ta2[ l1 ][ l2 ];
			if( ta2[ l1 ][ l2 ] == 1 ) degree2[ l1 ]++;
		}
	}

	fin.close();

	for( l1 = 0; l1 < n; l1++ )
	{
		for( l2 = 0; l2 < n + 3; l2++ ) 
		{
			fucking1[ l1 ][ l2 ] = 0;
			fucking2[ l1 ][ l2 ] = 0;
		}
		for( l2 = 0; l2 < n; l2++ )
		{
			chk[ l2 ] = -1;
		}
		bfs1( l1 );
		for( l2 = 0; l2 < n; l2++ )
		{
			if( chk[ l2 ] != -1 ) fucking1[ l1 ][ chk[ l2 ] ]++;
		}
		for( l2 = 0; l2 < n; l2++ )
		{
			chk[ l2 ] = -1;
		}
		bfs2( l1 );
		for( l2 = 0; l2 < n; l2++ )
		{
			if( chk[ l2 ] != -1 ) fucking2[ l1 ][ chk[ l2 ] ]++;
		}
	}
	sw = 0;
	for( l1 = 0; l1 < n; l1++ )
	{
		for( l2 = 0; l2 < n; l2++ )
		{
			ta3[ l1 ][ l2 ] = 0;
			if( degree1[ l1 ] == degree2[ l2 ] )
			{
				for( l3 = 0; l3 < n + 3; l3++ )
				{
					if( fucking1[ l1 ][ l3 ] != fucking2[ l2 ][ l3 ] ) break;
				}
				if( l3 == n + 3 )
				{
					ta3[ l1 ][ l2 ] = 1;
					sw = 1;
				}
			}
		}
		if( sw == 0 ) break;
	}

	if( sw )
	{
		sw = 0;
		for( l1 = 0; l1 < n; l1++ )
		{
			chk[ l1 ] = 0;
		}
		bck_tr( 0 );
	}

	ofstream fout( "graph.out" );

	fout << sw << endl;
	if( sw )
	{
		for( l1 = 0; l1 < n; l1++ )
		{
			fout << arr[ l1 ] + 1 << ' ';
		}
	}

	fout.close();

	return 0;
}

void bfs1( int x )
{
	int front = 0, rear = 1;
	int l1, tmp1;
	
	queue[ 0 ] = x;
	chk[ x ] = 0;
	while( front < rear )
	{
		tmp1 = queue[ front++ ];
		for( l1 = 0; l1 < n; l1++ )
		{
			if( ta1[ tmp1 ][ l1 ] == 1 && chk[ l1 ] == -1 )
			{
				chk[ l1 ] = chk[ tmp1 ] + 1;
				queue[ rear++ ] = l1;
			}
		}
	}
}

void bfs2( int x )
{
	int front = 0, rear = 1;
	int l1, tmp1;
	
	queue[ 0 ] = x;
	chk[ x ] = 0;
	while( front < rear )
	{
		tmp1 = queue[ front++ ];
		for( l1 = 0; l1 < n; l1++ )
		{
			if( ta2[ tmp1 ][ l1 ] == 1 && chk[ l1 ] == -1 )
			{
				chk[ l1 ] = chk[ tmp1 ] + 1;
				queue[ rear++ ] = l1;
			}
		}
	}
}

void bck_tr( int x )
{
	int l1, l2;

	if( GetTickCount() - tm > 3000 ) { ofstream fout( "graph.out" ); fout << "Fucking case... KRWARWRWARWA"; fout.close(); exit( 0 ); }
	if( sw ) return;
	for( l1 = 0; l1 < x - 1; l1++ )
	{
		if( ta1[ l1 ][ x - 1 ] != ta2[ arr[ l1 ] ][ arr[ x - 1 ] ] ) return;
	}
	if( x < n )
	{
		for( l1 = 0; l1 < n; l1++ )
		{
			if( ta3[ x ][ l1 ] == 1 && chk[ l1 ] == 0 )
			{
				arr[ x ] = l1;
				chk[ l1 ] = 1;
				bck_tr( x + 1 );
				if( sw ) return;
				chk[ l1 ] = 0;
			}
		}
	}
	else sw = 1;
}