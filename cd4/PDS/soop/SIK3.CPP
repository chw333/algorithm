#include <fstream.h>
#include <string.h>

const char input_file_name[] = "repe.inp";
const char output_file_name[] = "repe.out";

ifstream fin;
ofstream fout;

void string_coding( char * str );

int main( void )
{
	char str[ 1000 ];

	fin.open( input_file_name );
	if( ! fin ) { cout << "!!!dnuof ton elif" << endl; return 1; }

	fout.open( output_file_name );

	while( 1 )
	{
		fin.getline( str, 1000, '\n' );
		if( str[ 0 ] == 0 ) break;
		string_coding( str );
		fout << str << endl;
	}

	fin.close();
	fout.close();

	return 0;
}

void string_coding( char * str )
{
	int dyn_arr[ 1000 ] = { 0 }, back[ 1000 ][ 2 ];
	int l;
	char * tmp_str;
	int l1, l2, l3, l4, tmp1;

	back[ 0 ][ 0 ] = -9999;

	l = strlen( str );
	for( l1 = 1; l1 <= l; l1++ )
	{
		dyn_arr[ l1 ] = dyn_arr[ l1 - 1 ] + 1;
		back[ l1 ][ 0 ] = -1;
		for( l2 = 0; l2 < l1; l2++ )
		{
			for( l3 = l1 - 1; l2 + ( l1 - l3 ) <= l3; l3-- )
			{
				for( l4 = l3; l4 < l1; l4++ )
				{
					if( str[ l2 + l4 - l3 ] != str[ l4 ] ) break;
				}
				if( l4 == l1 )
				{
					tmp1 = 3 - l2 + l3;
					if( l2 + l1 - l3 == l3 ) tmp1--;
					if( dyn_arr[ l1 ] > dyn_arr[ l2 ] + tmp1 )
					{
						dyn_arr[ l1 ] = dyn_arr[ l2 ] + tmp1;
						back[ l1 ][ 0 ] = l2;
						back[ l1 ][ 1 ] = l3;
					}
				}
			}
		}
	}
	if( l != dyn_arr[ l ] )
	{
		tmp_str = new char [ dyn_arr[ l ] + 1 ];
		l1 = l; l2 = dyn_arr[ l ];
		tmp_str[ l2 ] = 0;
		while( back[ l1 ][ 0 ] != -9999 )
		{
			if( back[ l1 ][ 0 ] == -1 )
			{
				tmp_str[ --l2 ] = str[ --l1 ];
			}
			else
			{
				tmp1 = 3 - back[ l1 ][ 0 ] + back[ l1 ][ 1 ];
				if( back[ l1 ][ 0 ] + l1 - back[ l1 ][ 1 ] == back[ l1 ][ 1 ] )
				{
					tmp1--;
					tmp_str[ l2 - tmp1 ] = '(';
					for( l3 = back[ l1 ][ 1 ]; l3 < l1; l3++ )
					{
						tmp_str[ l2 - tmp1 + 1 + l3 - back[ l1 ][ 1 ] ] = str[ l3 ];
					}
					tmp_str[ l2 - 1 ] = ')';
					l2 -= tmp1;
				}
				else
				{
					tmp_str[ l2 - tmp1 ] = '(';
					for( l3 = back[ l1 ][ 1 ]; l3 < l1; l3++ )
					{
						tmp_str[ l2 - tmp1 + 1 + l3 - back[ l1 ][ 1 ] ] = str[ l3 ];
					}
					tmp_str[ l2 - tmp1 + 1 + l3 - back[ l1 ][ 1 ] ] = '|';
					l3 = l2 - tmp1 + 2 + l3 - back[ l1 ][ 1 ];
					for( l4 = back[ l1 ][ 0 ] + l1 - back[ l1 ][ 1 ]; l4 < back[ l1 ][ 1 ]; l4++ )
					{
						tmp_str[ l3 + l4 - back[ l1 ][ 0 ] - l1 + back[ l1 ][ 1 ] ] = str[ l4 ];
					}
					tmp_str[ l2 - 1 ] = ')';
					l2 -= tmp1;
				}
				l1 = back[ l1 ][ 0 ];
			}
		}
		strcpy( str, tmp_str );
		delete [] tmp_str;
	}
}