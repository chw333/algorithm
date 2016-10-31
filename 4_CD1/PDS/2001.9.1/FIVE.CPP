#include <fstream.h>

const char input_file_name[] = "triangle.inp";
const char output_file_name[] = "triangle.out";

ifstream fin;
ofstream fout;

int input_and_process( double & answer );
void output( double res );

int main( void )
{
	double answer;

	if( ! input_and_process( answer ) ) { cout << "!!!dnuof ton elif" << endl; return 1; }
	output( answer );

	return 0;
}

int input_and_process( double & answer )
{
	double arr[ 1000 ] = { 0 };
	double tmp1;
	int l1, l2;
	int n;

	fin.open( input_file_name );

	if( ! fin ) { fin.close(); return 0; }
	fin >> n;
	for( l1 = 0; l1 < n; l1++ )
	{
		if( l1 > 0 ) arr[ l1 ] = arr[ l1 - 1 ];
		for( l2 = l1 - 2; l2 >= 0; l2-- )
		{
			if( arr[ l2 + 1 ] < arr[ l2 ] )
			{
				arr[ l2 + 1 ] = arr[ l2 ];
			}
		}
		for( l2 = 0; l2 <= l1; l2++ )
		{
			fin >> tmp1;
			arr[ l2 ] += tmp1;
		}
	}

	fin.close();

	answer = arr[ 0 ];
	for( l1 = 1; l1 < n; l1++ )
	{
		if( answer < arr[ l1 ] ) answer = arr[ l1 ];
	}

	return 1;
}

void output( double res )
{
	fout.open( output_file_name );

	fout << res;

	fout.close();
}