#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#define MAX 1000
ofstream out("hendel5.in");

void main()
{
	int i,j;
    srand((unsigned)time(NULL));
	out << MAX << endl;
	for(i=0;i<MAX;i++) {
		for(j=0;j<MAX;j++)
			out << rand()%2 << " ";
		out << endl;
	}

}
