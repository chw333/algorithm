#include<fstream.h>
#include<stdlib.h>
#include<time.h>
ifstream in("spy.in");
ofstream out("spy.out");

void main()
{
	
	static int a,b;
	time_t t;
	srand((unsigned) time(&t));
	in >> b;
	
	out << rand() % (b+1);;
}