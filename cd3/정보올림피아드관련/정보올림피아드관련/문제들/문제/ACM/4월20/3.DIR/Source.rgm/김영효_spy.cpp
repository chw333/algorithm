#include "fstream.h"

int n;
int count=0;

void inproc()
{
	int x,y,bx,by,i;

	ifstream in("spy.in");
	in >> n;
	
	for( i=0; i<n; i++ )
	{
		in >> x >> y >> bx >> by;

		if( bx < x && by < y )
			count++;
		else if( bx < y && by < x )
			count++;
	}
}

void output()
{
	ofstream out("spy.out");

	out << count;
}

void main()
{
	inproc();
	output();
}