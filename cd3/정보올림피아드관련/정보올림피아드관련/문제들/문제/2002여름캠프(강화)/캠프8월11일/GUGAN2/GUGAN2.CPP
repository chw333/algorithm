#include <fstream.h>
#include <stdlib.h>

#define INFILE  "gugan2.in"
#define OUTFILE "gugan2.out"

#define Max 10000

int N;
int G[Max*2];
int /*huge*/ D[Max*2];
int /*huge*/ S[Max*2];
int Sindex;
int Maxc, Maxs, Maxe;

void input()
{
	int i;
	ifstream in ( INFILE );
	in >> N;
	for ( i = 0; i < N*2; i ++ ) {
		in >> G[i];
		D[i] = i;
	}
}

void output()
{
	ofstream out ( OUTFILE );
	out << Maxc + 1 << endl;
	out << Maxs << " " << Maxe;
}

int sort_function( const void *a, const void *b)
{
	int ret;
	int aa = G[*(int*)a];
	int bb = G[*(int*)b];
	if ( aa > bb ) ret = 1;
	else if ( aa == bb ) ret = 0;
	else ret = -1;
	return ret;
}

void push ( int s )
{
	S[Sindex ++] = s;
}

int pop ( )
{
	return ( S[--Sindex] );
}

void process()
{
	int i, s, e, maxd;
	Maxc = -1;
	qsort((void *)D, N*2, sizeof(D[0]), sort_function);
	for ( i = 0; i < N * 2; i ++ ) {
		e = D[i];
		if ( e % 2 == 0 ) push( G[e] );
		else {
			e = G[e];
			s = pop();
			if ( Maxc < Sindex ) {
				Maxc = Sindex;
				maxd = e - s;
				Maxs = s; Maxe = e;
			}
			if ( Maxc == Sindex && maxd < e - s ) {
				maxd = e - s;
				Maxs = s; Maxe = e;
			}
		}
	}
}

void main()
{
	input();
	process();
	output();
}
