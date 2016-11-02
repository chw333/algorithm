#include <fstream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <conio.h>

int n, map[130][130];

int Input( void )
{
/*	ifstream in("Input.txt");
	if(!in)
	{
		cout << "File not Found!!";
		return 1;
	}
	in >> n;*/

	n = 2
	return 0;
}

void Output( void )
{
	int loop1, loop2;

	ofstream out("Output.txt");
	for(loop1=1; loop1<=n; loop1++)
	{
		for(loop2=2; loop2<=n; loop2++)
			out << setw(4) << map[loop1][loop2];
		out << endl;
	}
	out.close();
	exit(1);
}

void Divide_and_conquer( int x )
{
	int loop1, loop2, sw;

	if(x==n)
		Output();
	sw=-1;
	for(loop1=1; loop1<=n; loop1++)
	{
		if(loop1%x==1 || x==1)
			sw*=-1;
		for(loop2=1; loop2<=x; loop2++)
			map[x+loop2][loop1+(sw*x)]=map[loop2][loop1];
	}
	Divide_and_conquer( x*2 );
}

void Process( void )
{
	int loop1, loop2;

	for(loop1=1; loop1<=n; loop1++)
		map[1][loop1]=loop1;
	Divide_and_conquer( 1 );
}

void main( void )
{
	if(Input()==1) return;
	Process();
}