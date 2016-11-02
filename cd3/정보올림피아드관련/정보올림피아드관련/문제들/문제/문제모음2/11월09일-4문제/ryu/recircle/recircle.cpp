#include <fstream.h>

ifstream in ("recircle.in");
ofstream out("recircle.out");

struct RECT {
	int l, r, u, d;
} Rect={-500,500,500,-500};

struct CIRC {
	int x, y, r;
} Circ;

void input()
{
	int r;
	in>>Circ.x>>Circ.y>>Circ.r;
}

void process()
{
	double d1, d2, d3, d4;
	d1=sqrt(pow(Rect.l-Circ.x,2)+pow(Rect.u-Circ.y,2));
	d2=sqrt(pow(Rect.l-Circ.x,2)+pow(Rect.d-Circ.y,2));
	d3=sqrt(pow(Rect.r-Circ.x,2)+pow(Rect.u-Circ.y,2));
	d4=sqrt(pow(Rect.r-Circ.x,2)+pow(Rect.d-Circ.y,2));	
	if(Rect.u<Circ.y+Circ.r){
		if(d1<Circ.r){

		} else if(d2<Circ.r){
		} else {
		}
	}
	if(Rect.d>Circ.y-Circ.r){
	}
	if(Rect.l>Circ.x-Circ.r){
	}
	if(Rect.r<Circ.x+Circ.r){
	}
}

void output()
{
	out<<
}

void main()
{
	input();
	process();
	output();
}