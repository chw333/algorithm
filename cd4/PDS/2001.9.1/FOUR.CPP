#include <fstream.h>

const char input_file_name[] = "input.txt";
const char output_file_name[] = "output.txt";

ifstream fin;
ofstream fout;

struct Point
{
	double x, y;
};

int input( void );
double process( void );
void output( double res );

Point p[ 1000 ];
double div_x[ 1000 ];
double div_y[ 1000 ];
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
	for( l1 = 0; l1 < n; l1++ )
	{
		fin >> p[ l1 ].x >> p[ l1 ].y;
	}

	fin.close();

	return 1;
}

double process( void )
{
	int line[ 1000 ][ 3 ];
	int chk1[ 1000 ] = { 0 }, chk2[ 1000 ];
	int arr[ 1000 ] = { 0 };
	int m;
	int tmp1, xn = 0, yn = 0;
	int l1, l2, l3, l4;
	double sum, max = -1;

	for( l1 = 0; l1 < n; l1++ )
	{
		for( l2 = 0; l2 < xn; l2++ )
		{
			if( div_x[ l2 ] == p[ l1 ].x ) break;
		}
		if( l2 == xn )
		{
			div_x[ xn++ ] = p[ l1 ].x;
		}
		for( l2 = 0; l2 < yn; l2++ )
		{
			if( div_y[ l2 ] == p[ l1 ].y ) break;
		}
		if( l2 == yn )
		{
			div_y[ yn++ ] = p[ l1 ].y;
		}
	}
	for( l1 = 1; l1 < xn; l1++ )
	{
		for( l2 = l1; l2 > 0; l2-- )
		{
			if( div_x[ l2 ] < div_x[ l2 - 1 ] )
			{
				tmp1 = div_x[ l2 ]; div_x[ l2 ] = div_x[ l2 - 1 ]; div_x[ l2 - 1 ] = tmp1;
			}
			else break;
		}
	}
	for( l1 = 1; l1 < yn; l1++ )
	{
		for( l2 = l1; l2 > 0; l2-- )
		{
			if( div_y[ l2 ] < div_y[ l2 - 1 ] )
			{
				tmp1 = div_y[ l2 ]; div_y[ l2 ] = div_y[ l2 - 1 ]; div_y[ l2 - 1 ] = tmp1;
			}
			else break;
		}
	}
	for( l1 = 0; l1 < n; l1++ )
	{
		for( l2 = 0; l2 < xn; l2++ )
		{
			if( p[ l1 ].x == div_x[ l2 ] ) break;
		}
		p[ l1 ].x = l2;
		for( l2 = 0; l2 < yn; l2++ )
		{
			if( p[ l1 ].y == div_y[ l2 ] ) break;
		}
		p[ l1 ].y = l2;
	}

	m = 0;
	for( l1 = 0; l1 < n; l1++ )
	{
		if( p[ l1 ].x == p[ ( l1 + 1 ) % n ].x )
		{
			line[ m ][ 0 ] = p[ l1 ].x;
			line[ m ][ 1 ] = p[ l1 ].y;
			line[ m ][ 2 ] = p[ ( l1 + 1 ) % n ].y;
			if( line[ m ][ 1 ] > line[ m ][ 2 ] )
			{
				tmp1 = line[ m ][ 1 ]; line[ m ][ 1 ] = line[ m ][ 2 ]; line[ m ][ 2 ] = tmp1;
			}
			m++;
		}
	}

	for( l1 = 1; l1 < m; l1++ )
	{
		for( l2 = l1; l2 > 0; l2-- )
		{
			if( line[ l2 ][ 0 ] < line[ l2 - 1 ][ 0 ] )
			{
				tmp1 = line[ l2 ][ 0 ]; line[ l2 ][ 0 ] = line[ l2 - 1 ][ 0 ]; line[ l2 - 1 ][ 0 ] = tmp1;
				tmp1 = line[ l2 ][ 1 ]; line[ l2 ][ 1 ] = line[ l2 - 1 ][ 1 ]; line[ l2 - 1 ][ 1 ] = tmp1;
				tmp1 = line[ l2 ][ 2 ]; line[ l2 ][ 2 ] = line[ l2 - 1 ][ 2 ]; line[ l2 - 1 ][ 2 ] = tmp1;
			}
		}
	}

	for( l1 = 0; l1 < xn - 1; l1++ ) chk1[ l1 ] = arr[ l1 ] = 0;
	for( l1 = 0, l2 = 0; l1 < xn - 1; l1++ )
	{
		for( l3 = 1; l3 <= xn; l3++ ) chk2[ l3 ] = 0;
		for( ; line[ l2 ][ 0 ] == l1; l2++ )
		{
			for( l3 = line[ l2 ][ 1 ]; l3 < line[ l2 ][ 2 ]; l3++ )
			{
				chk1[ l3 ] = 1 - chk1[ l3 ];
			}
			for( l3 = 0; l3 < yn - 1; l3++ )
			{
				if( chk1[ l3 ] == 0 ) arr[ l3 ] = 0;
				else
				{
					arr[ l3 ]++;
					chk2[ arr[ l3 ] ] = 1;
				}
			}
			for( l3 = 1; l3 <= xn; l3++ )
			{
				if( chk2[ l3 ] == 1 )
				{
					sum = 0;
					for( l4 = 0; l4 < yn - 1; l4++ )
					{
						if( arr[ l4 ] < l3 ) sum = 0;
						else sum += ( div_x[ l1 + 1 ] - div_x[ l1 + 1 - l3 ] ) * ( div_y[ l4 + 1 ] - div_y[ l4 ] );
						if( max < sum ) max = sum;
					}
				}
			}
		}
	}

	m = 0;
	for( l1 = 0; l1 < n; l1++ )
	{
		if( p[ l1 ].y == p[ ( l1 + 1 ) % n ].y )
		{
			line[ m ][ 0 ] = p[ l1 ].y;
			line[ m ][ 1 ] = p[ l1 ].x;
			line[ m ][ 2 ] = p[ ( l1 + 1 ) % n ].x;
			if( line[ m ][ 1 ] > line[ m ][ 2 ] )
			{
				tmp1 = line[ m ][ 1 ]; line[ m ][ 1 ] = line[ m ][ 2 ]; line[ m ][ 2 ] = tmp1;
			}
			m++;
		}
	}

	for( l1 = 1; l1 < m; l1++ )
	{
		for( l2 = l1; l2 > 0; l2-- )
		{
			if( line[ l2 ][ 0 ] < line[ l2 - 1 ][ 0 ] )
			{
				tmp1 = line[ l2 ][ 0 ]; line[ l2 ][ 0 ] = line[ l2 - 1 ][ 0 ]; line[ l2 - 1 ][ 0 ] = tmp1;
				tmp1 = line[ l2 ][ 1 ]; line[ l2 ][ 1 ] = line[ l2 - 1 ][ 1 ]; line[ l2 - 1 ][ 1 ] = tmp1;
				tmp1 = line[ l2 ][ 2 ]; line[ l2 ][ 2 ] = line[ l2 - 1 ][ 2 ]; line[ l2 - 1 ][ 2 ] = tmp1;
			}
		}
	}

	for( l1 = 0; l1 < xn - 1; l1++ ) chk1[ l1 ] = arr[ l1 ] = 0;
	for( l1 = 0, l2 = 0; l1 < yn - 1; l1++ )
	{
		for( l3 = 1; l3 <= yn; l3++ ) chk2[ l3 ] = 0;
		for( ; line[ l2 ][ 0 ] == l1; l2++ )
		{
			for( l3 = line[ l2 ][ 1 ]; l3 < line[ l2 ][ 2 ]; l3++ )
			{
				chk1[ l3 ] = 1 - chk1[ l3 ];
			}
			for( l3 = 0; l3 < xn - 1; l3++ )
			{
				if( chk1[ l3 ] == 0 ) arr[ l3 ] = 0;
				else
				{
					arr[ l3 ]++;
					chk2[ arr[ l3 ] ] = 1;
				}
			}
			for( l3 = 1; l3 <= yn; l3++ )
			{
				if( chk2[ l3 ] == 1 )
				{
					sum = 0;
					for( l4 = 0; l4 < xn - 1; l4++ )
					{
						if( arr[ l4 ] < l3 ) sum = 0;
						else sum += ( div_y[ l1 + 1 ] - div_y[ l1 + 1 - l3 ] ) * ( div_x[ l4 + 1 ] - div_x[ l4 ] );
						if( max < sum ) max = sum;
					}
				}
			}
		}
	}

	return max;
}

void output( double res )
{
	fout.open( output_file_name );

	fout << res;

	fout.close();
}