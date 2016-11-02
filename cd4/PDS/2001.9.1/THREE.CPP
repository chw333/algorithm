#include <fstream.h>

#define NONE   -1

const char input_file_name[] = "input.txt";
const char output_file_name[] = "output.txt";

ifstream fin;
ofstream fout;

int input( void );
int process( void );
void output( int res );

int how_many[ 100 ][ 51 ], how_many_n[ 100 ];
double limit[ 100 ];
double w[ 2 ];
int n;

int main( void )
{
	if( ! input() ) { cout << "!!!dnuof ton elif" << endl; return 1; }
	output( process() );

	return 0;
}

int input( void )
{
	int l1;

	fin.open( input_file_name );

	if( ! fin ) { fin.close(); return 0; }
	fin >> n;
	for( l1 = 0; l1 < n; l1++ ) fin >> limit[ l1 ];
	fin >> w[ 0 ] >> w[ 1 ];

	fin.close();

	return 1;
}

int process( void )
{
	int arr1[ 5001 ], arr2[ 5001 ];
	int l1, l2, l3, l4;
	double tmp1 = 0;
	int max;

	for( l1 = 0; l1 < n; l1++ )
	{
		how_many_n[ l1 ] = limit[ l1 ] / w[ 0 ];
		tmp1 += limit[ l1 ];
		for( l2 = 0; l2 <= how_many_n[ l1 ]; l2++ )
		{
			how_many[ l1 ][ l2 ] = ( limit[ l1 ] - w[ 0 ] * l2 ) / w[ 1 ];
		}
	}
	max = tmp1 / ( w[ 0 ] + w[ 1 ] * 2 );
	for( l2 = 0; l2 <= l1; l2++ )
	{
		arr1[ l2 ] = arr2[ l2 ] = NONE;
	}
	arr1[ 0 ] = 0;
	for( l2 = 0; l2 < n; l2++ )
	{
		for( l3 = 0; l3 <= l1; l3++ )
		{
			if( arr1[ l3 ] != NONE )
			{
				for( l4 = 0; l4 <= how_many_n[ l2 ]; l4++ )
				{
					if( l3 + l4 <= l1 )
					{
						if( arr2[ l3 + l4 ] < arr1[ l3 ] + how_many[ l2 ][ l4 ] || arr2[ l3 + l4 ] == NONE )
						{
							arr2[ l3 + l4 ] = arr1[ l3 ] + how_many[ l2 ][ l4 ];
						}
					}
				}
			}
		}
		for( l3 = 0; l3 <= l1; l3++ )
		{
			arr1[ l3 ] = arr2[ l3 ];
			arr2[ l3 ] = NONE;
		}
	}
	for( l1 = max; l1 >= 0; l1-- )
	{
		if( arr1[ l1 ] >= l1 * 2 ) break;
	}

	return l1;
}

void output( int res )
{
	fout.open( output_file_name );

	fout << res;

	fout.close();
}