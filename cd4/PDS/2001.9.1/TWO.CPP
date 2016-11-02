#include <fstream.h>

#define NONE   -2
#define UNDEFINED   -1

const char input_file_name[] = "input.txt";
const char output_file_name[] = "output.txt";

ifstream fin;
ofstream fout;

int input( void );
void process( void );
void output( void );
void bck_tr( int x, int y, int z );

int phone[ 4 ][ 3 ] = { { 1, 2, 3 },
						{ 4, 5, 6 },
						{ 7, 8, 9 },
						{ NONE, 0, NONE } };
int chk[ 4 ][ 3 ] = { 0 };
int arr[ 100 ];
int n = 0;
long cnt = 0;
int res[ 100 ];

int main( void )
{
	if( ! input() ) { cout << "!!!dnuof ton elif" << endl; return 1; }
	process();
	output();

	return 0;
}

int input( void )
{
	char tmp1;

	fin.open( input_file_name );

	if( ! fin ) { fin.close(); return 0; }

	while( 1 )
	{
		fin.get( tmp1 );
		if( tmp1 == '\n' || fin.eof() ) break;
		if( tmp1 == '?' )
		{
			arr[ n++ ] = UNDEFINED;
		}
		else if( '0' <= tmp1 && tmp1 <= '9' )
		{
			arr[ n++ ] = tmp1 - '0';
		}
	}

	fin.close();

	return 1;
}

void process( void )
{
	int l1, l2;

	for( l1 = 0; l1 < 4; l1++ )
	{
		for( l2 = 0; l2 < 3; l2++ )
		{
			if( phone[ l1 ][ l2 ] != NONE )
			{
				bck_tr( l1, l2, 0 );
			}
		}
	}
}

void output( void )
{
	fout.open( output_file_name );

	fout << cnt;

	fout.close();
}

void bck_tr( int x, int y, int z )
{
	if( x >= 4 || x < 0 || y >= 3 || y < 0 ) return;
	if( chk[ x ][ y ] == 1 ) return;
	if( phone[ x ][ y ] == NONE ) return;
	if( arr[ z ] != UNDEFINED && phone[ x ][ y ] != arr[ z ] ) return;
	chk[ x ][ y ] = 1;
	res[ z ] = phone[ x ][ y ];

	if( z < n - 1 )
	{
		bck_tr( x + 1, y, z + 1 );
		bck_tr( x - 1, y, z + 1 );
		bck_tr( x, y + 1, z + 1 );
		bck_tr( x, y - 1, z + 1 );
	}
	else
	{
		cnt++;
	}

	chk[ x ][ y ] = 0;
}