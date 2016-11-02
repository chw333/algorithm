#include <fstream.h>
#include <stdlib.h>
#include <time.h>

#define N   20
#define OUTFILE "contra214.in"

int Group[N];
int D[N][3];

int sort_function ( const void *a, const void *b )
{
	int *A = (int *) a;
	int *B = (int *) b;
	if ( A[0] > B[0] ) return 1;
	else if ( A[0] == B[0] ) {
		if ( A[1] > B[1] ) return 1;
		else if ( A[1] == B[1] ) return 0;
		return -1;
	}
	return -1;
}

void main()
{
	int c;
	int i, g, a, b, count = 0;
	ofstream out ( OUTFILE );
	srand ( (unsigned int) time ( NULL ) );
	out << N << endl;
	for ( i = 1; i <= N; i ++ ) {
		g = rand () % 100 + 1;
		out << i << " " << g << endl;
	}
	Group[0] = 1;
	do { 
		do {
			a = rand() % N; 
		} while ( !Group[a] );
		do {
			b = rand() % N;
		} while ( Group[b] );
		Group[b] = 1;
		c = (rand()%49)+2;
		D[count][0] = a + 1;
		D[count][1] = b + 1;
		D[count++][2] = c;
	} while ( count < N - 1 );
	qsort ( D, N-1, sizeof ( D[0] ), sort_function );
	for ( i = 0; i < N - 1; i ++ ) {
		if ( i != 0 ) out << endl;
		out << D[i][0] << " " << D[i][1] << " " << D[i][2];
	}	
}
