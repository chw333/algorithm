#include <fstream.h>

const char input_file_name[] = "land.inp";
const char output_file_name[] = "land.out";

ifstream fin;
ofstream fout;

int input( void );
void process( void );
void output( void );

long ta[ 100 ][ 100 ];
long max = -1;
int x1, y1, x2, y2;
int n, m;

int main( void )
{
	if( ! input() ) { cout << "!!!dnuof ton elif" << endl; return 1; }
	process();
	output();

	return 0;
}

int input( void )
{
	int l1, l2;

	fin.open( input_file_name );

	if( ! fin ) { fin.close(); return 0; }
	fin >> n >> m;
	for( l1 = 0; l1 < n; l1++ )
	{
		for( l2 = 0; l2 < m; l2++ )
		{
			fin >> ta[ l1 ][ l2 ];
		}
	}

	fin.close();

	return 1;
}

void process( void )
{
	int arr[ 100 ];
	int l1, l2, l3;
	int sum, st;

	for( l1 = 0; l1 < n; l1++ )
	{
		for( l2 = 0; l2 < m; l2++ ) arr[ l2 ] = 0;
		for( l2 = l1; l2 < n; l2++ )
		{
			sum = 0; st = 0;
			for( l3 = 0; l3 < m; l3++ )
			{
				arr[ l3 ] += ta[ l2 ][ l3 ];
				sum += arr[ l3 ];
				if( sum < 0 ) { sum = 0; st = l3 + 1; }
				if( max < sum )
				{
					x1 = l1; x2 = l2;
					y1 = st; y2 = l3;
					max = sum;
				}
			}
		}
	}
}

void output( void )
{
	fout.open( output_file_name );

	x1++; y1++; x2++; y2++;
	fout << '(' << x1 << ',' << y1 << ")-(" << x2 << ',' << y2 << ')' << endl;
	fout << max;

	fout.close();
}