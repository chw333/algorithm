#include <graphics.h>
#include <fstream.h>
#include <conio.h>
#include<math.h>

#define m 96

int n;

int Input( void )
{
/*	ifstream in("Input.txt");
	if(!in)
	{
		cout << "File not found!" << endl;
		return 1;
	}
	in >> n;
	in.close();
	*/ n =
	return 0;
}

void Initgraph( void )
{
	int gdriver = DETECT, gmode, errorcode;

	initgraph(&gdriver, &gmode, "c:\\tc30\\bgi");
}

void Process1( int x, int y, int depth, int size )
{
	int loop1, loop2;

	rectangle( x-size, y-size, x+size, y+size );
	if(depth!=n)
	{
		Process1( x-size, y-size, depth+1, size/2 );
		Process1( x+size, y-size, depth+1, size/2 );
		Process1( x-size, y+size, depth+1, size/2 );
		Process1( x+size, y+size, depth+1, size/2 );
		setfillstyle( SOLID_FILL, BLACK );
		bar3d( x-size, y-size, x+size, y+size, 0, 0 );
	}
}

void Process2( int x, int y, int depth, int size, int sw )
{
	int i, j, ss;

	if(sw!=1)
	{
		if(depth!=n)
		{
			line( x, y+size, x+size/2, y+size );
			line( x+size, y, x+size, y+size/2 );
		}
		else
		{
			line( x, y+size, x+size, y+size );
			line( x+size, y, x+size, y+size );
		}
	}
	if(sw!=2)
	{
		if(depth!=n)
		{
			line( x, y+size, x-size/2, y+size );
			line( x-size, y, x-size, y+size/2 );
		}
		else
		{
			line( x, y+size, x-size, y+size );
			line( x-size, y, x-size, y+size );
		}
	}
	if(sw!=3)
	{
		if(depth!=n)
		{
			line( x, y-size, x+size/2, y-size );
			line( x+size, y, x+size, y-size/2 );
		}
		else
		{
			line( x, y-size, x+size, y-size );
			line( x+size, y, x+size, y-size );
		}
	}
	if(sw!=4)
	{
		if(depth!=n)
		{
			line( x, y-size, x-size/2, y-size );
			line( x-size, y, x-size, y-size/2 );
		}
		else
		{
			line( x, y-size, x-size, y-size );
			line( x-size, y, x-size, y-size );
		}
	}
	if(depth!=n)
	{
		if(depth==n-1)
			ss=size;
		else
			ss=size/2;
		if(sw!=4)
			Process2( x-size, y-size, depth+1, size/2, 1 );
		if(sw!=3)
			Process2( x+size, y-size, depth+1, size/2, 2 );
		if(sw!=2)
			Process2( x-size, y+size, depth+1, size/2, 3 );
		if(sw!=1)
			Process2( x+size, y+size, depth+1, size/2, 4 );
	}
}

void main( void )
{
	if(Input()==1) return;
	Initgraph();
	cleardevice();
	Process1( 320, 240, 1, m );
	getch();
	cleardevice();
	Process2( 320, 240, 1, m, 0 );
	getch();
	closegraph();
}