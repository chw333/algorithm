#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int N;
char filename[80] = "centural00.in";

void outfile ()
{
	int i;
	ofstream out ( filename );
	out << N;
	srand ( (unsigned) time (NULL) );
	for ( i = 0; i < N; i ++ ) {
		out << endl << rand()%5000 + 1 << " " << rand()%5000 + 1;
	}
}

void main ()
{
	int i;
	for ( i = 0; i < 10; i ++ ) {
		sprintf ( &filename[8], "%02d", i + 1 );
		filename[10] = '.';
		N = 50 * ( i + 1 );
		outfile();
	}
}