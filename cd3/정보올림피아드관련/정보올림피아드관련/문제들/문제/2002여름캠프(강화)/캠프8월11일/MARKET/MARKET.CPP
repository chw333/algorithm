#include <fstream.h>

#define Max 500

int N;
int T[Max];
int SW[Max];
int POJANG[2][500000+1];
int Last;

ifstream in  ( "market.in" );
ofstream out ( "market.out" );

void input ()
{
	int i;
	in >> N;
	for ( i = 0; i < N; i ++ ) {
		in >> T[i];
	}
}

void process ( )
{
	int i, j;
	for ( i = 0; i < N; i ++ ) {
		POJANG[i%2][T[i]] ++;
		for ( j = 1; j <= 500000; j ++ ) {
			if ( POJANG[(i+1)%2][j] )  {
				POJANG[i%2][j] = POJANG[(i+1)%2][j];
				POJANG[i%2][j+T[i]] ++;
			}
		}
		Last = i%2;
	}
}

void output ()
{	
	int i, count = 0;
	for ( i = 1; i <= 500000; i ++ ) {
		count += POJANG[Last][i];
	}
	out << count;
}

void main()
{
	input();
	process();
	output();
}


