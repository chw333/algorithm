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
int ccw( Point p1, Point p2, Point p3 );
int is_cross( Point p1, Point p2, Point p3, Point p4 );
double get_area( int * chk );

Point p[ 1000 ];
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
	int chk[ 1000 ] = { 0 };
	int l1, l2, l3;
	Point tmp_p;
	double max = get_area( chk ), tmp1, tmp2;

	tmp2 = max;
	for( l1 = 0; l1 < n; l1++ )
	{
		tmp_p = p[ 0 ]; chk[ 0 ] = 0;
		for( l2 = 1; l2 < n; l2++ )
		{
			p[ l2 - 1 ] = p[ l2 ];
			chk[ l2 ] = 0;
		}
		p[ n - 1 ] = tmp_p;
		for( l2 = 2; l2 < n - 1; l2++ )
		{
			chk[ l2 - 1 ] = 1;
			for( l3 = 2; l3 < n; l3++ )
			{
				if( l2 != l3 && l2 != l3 - 1 )
				{
					if( is_cross( p[ l3 - 1 ], p[ l3 ], p[ 0 ], p[ l2 ] ) ) break;
				}
			}
			if( l3 == n )
			{
				tmp1 = get_area( chk );
				if( max < tmp1 ) max = tmp1;
			}
		}
	}

	return max - tmp2;
}

void output( double res )
{
	fout.open( output_file_name );

	fout << res;

	fout.close();
}

int ccw( Point p1, Point p2, Point p3 )
{
	double tmp1;

	tmp1 = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.x * p3.y - p2.x * p1.y - p3.x * p2.y;
	if( tmp1 < 0 ) return -1;
	else if( tmp1 > 0 ) return 1;

	return 0;
}

int is_cross( Point p1, Point p2, Point p3, Point p4 )
{
	int ccw123, ccw124, ccw341, ccw342;
	Point pp1 = p1, pp2 = p2, pp3 = p3, pp4 = p4;
	double tmp1;

	ccw123 = ccw( p1, p2, p3 );
	ccw124 = ccw( p1, p2, p4 );
	ccw341 = ccw( p3, p4, p1 );
	ccw342 = ccw( p3, p4, p2 );
	if( ccw123 * ccw124 == -1 && ccw341 * ccw342 == -1 ) return 1;

	if( pp1.x > pp2.x ) { tmp1 = pp1.x; pp1.x = pp2.x; pp2.x = tmp1; }
	if( pp1.y > pp2.y ) { tmp1 = pp1.y; pp1.y = pp2.y; pp2.y = tmp1; }
	if( pp3.x > pp4.x ) { tmp1 = pp3.x; pp3.x = pp4.x; pp4.x = tmp1; }
	if( pp3.y > pp4.y ) { tmp1 = pp3.y; pp3.y = pp4.y; pp4.y = tmp1; }
	if( ccw123 == 0 )
	{
		if( pp1.x <= p3.x && p3.x <= pp2.x && pp1.y <= p3.y && p3.y <= pp2.y ) return 1;
	}
	if( ccw124 == 0 )
	{
		if( pp1.x <= p4.x && p4.x <= pp2.x && pp1.y <= p4.y && p4.y <= pp2.y ) return 1;
	}
	if( ccw341 == 0 )
	{
		if( pp3.x <= p1.x && p1.x <= pp4.x && pp3.y <= p1.y && p1.y <= pp4.y ) return 1;
	}
	if( ccw342 == 0 )
	{
		if( pp3.x <= p2.x && p2.x <= pp4.x && pp3.y <= p2.y && p2.y <= pp4.y ) return 1;
	}

	return 0;
}

double get_area( int * chk )
{
	double res = ( p[ n - 1 ].x - p[ 0 ].x ) * ( p[ n - 1 ].y + p[ 0 ].y ) / 2;
	int l1, prev;

	prev = 0;
	for( l1 = 1; chk[ l1 ]; l1++ );
	for( ; l1 < n; )
	{
		res += ( p[ prev ].x - p[ l1 ].x ) * ( p[ prev ].y + p[ l1 ].y ) / 2;
		prev = l1;
		for( l1++; chk[ l1 ] && l1 < n; l1++ );
	}

	if( res < 0 ) res = -res;

	return res;
}