#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100
ofstream out("round5.in");

void main()
{
	int i,j;
    srand((unsigned)time(NULL));
	out << MAX << endl;
	for(i=0;i<MAX;i++) {
			out << rand()%100+1 << " ";
			out << rand()%100+1 << endl;
	}
}
