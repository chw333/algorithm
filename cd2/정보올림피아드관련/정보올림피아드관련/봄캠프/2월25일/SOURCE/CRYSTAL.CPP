#include <fstream.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>

#define MAX 102
#define PI 3.141592

void inputdata(void);
void initialize(void);
int cross(int, int, int, int, int, int, int, int);
int ccw(int, int, int, int, int, int);
int checkside(int, int);
int checkinside(int, int);

int n;
struct {
	int x,y;
} p[MAX];
struct {
	double a,b,c;
} l[MAX];
int minx=9999, miny=9999, maxx=-9999, maxy=-9999;
double full, bantm;

void inputdata(void)
{
	int q,w,e;

	ifstream in("crystal.inp");
	in>>n; bantm=n-2;
	for (q=1;q<=n;q++){
		in>>p[q].x>>p[q].y;
		if (minx>p[q].x) minx=p[q].x;
		if (miny>p[q].y) miny=p[q].y;
		if (maxx<p[q].x) maxx=p[q].x;
		if (maxy<p[q].y) maxy=p[q].y;
	}
	p[0].x=p[n].x; p[0].y=p[n].y;
}

void initialize(void)
{
	int q,w,e;
	int ax,ay,bx,by;
	for (q=1;q<=n;q++){
		ax=p[q-1].x; ay=p[q-1].y;
		bx=p[q].x; by=p[q].y;
		l[q].a=-1*(ay-by);
		l[q].b=(ax-bx);
		l[q].c=ay*bx-ax*by;
	}
}

void main(void)
{ 
	int q,w,e;
	int data;
	inputdata();
	initialize();

	for (q=miny;q<=maxy;q++){
		for (w=minx;w<=maxx;w++){
			data=checkside(w,q);
			bantm+=data;
			full+=checkinside(w,q);
//			if (checkinside(w,q)==1) {cout<<w<<","<<q<<endl; getch();}
		}
	}


//	cout<<checkinside(86,1)<<endl;
//	cout<<checkinside(87,1)<<endl;
//	cout<<checkinside(88,1)<<endl;
	FILE *stream;
	stream=fopen("crystal.out", "w+");
	fprintf(stream, "%.2lf", 	((bantm/2)+full) * (PI/4) );
//	cout<<(double) ((bantm/2)+full) * (PI/4) <<endl;

}

int checkinside(int x, int y)
{
	int q,w,e;
	int cc[2]; cc[0]=0; cc[1]=0;
	double ccwd[MAX];
	double tx=-87.7, ty=-99.7;
	int data;
	double length, min=9999.9;
	ccwd[0]=1;
	for(q=1;q<=n;q++){
		ccwd[q]=ccw(x,y,p[q-1].x,p[q-1].y, p[q].x, p[q].y);
//		cout<<ccwd[q]<<" ";
		if (ccwd[q]*ccwd[q-1]<0) return 0;
	}//cout<<endl;

//	if ((cc[0]+cc[1])%2==0) return 0;
	for (q=1;q<=n;q++){
		length=abs( (l[q].a*x+l[q].b*y+l[q].c) ) / (sqrt(l[q].a*l[q].a+l[q].b*l[q].b) );
		if (length<min) min=length;
	}
	if (min<0.5) return 0;
	return 1;
}


int checkside(int x, int y)
{
	int q,w,e;
	int ax,ay,bx,by;
	w=0;
	for (q=1;q<=n;q++){
		ax=p[q-1].x; ay=p[q-1].y;
		bx=p[q].x; by=p[q].y;

		if (ax>bx) {
			e=ax; ax=bx; bx=e;
			e=ay; ay=by; by=e;
		}

		if (ccw(x,y,ax,ay,bx,by)==0&&ax<=x&&x<=bx
			&&((ay<=y&&y<=by)||(by<=y&&y<=ay))
			) {
			w++;
			if (w>1) return 0;
		}
	}
	if (w==1) return 1; else return 0;
}


int cross(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int p4x, int p4y)
{
	int temp;
	if (p1x>p2x) {
		temp=p1x; p1x=p2x; p2x=temp;
		temp=p1y; p1y=p2y; p2y=temp;
	}		
	if (p3x>p4x) {
		temp=p3x; p3x=p4x; p4x=temp;
		temp=p3y; p3y=p4y; p4y=temp;
	}		

	int r123=ccw(p1x,p1y,p2x,p2y,p3x,p3y);
	int r124=ccw(p1x,p1y,p2x,p2y,p4x,p4y);
	int r341=ccw(p3x,p3y,p4x,p4y,p1x,p1y);
	int r342=ccw(p3x,p3y,p4x,p4y,p2x,p2y);

	if (r123*r124<0&&r341*r342<0) return 1;

//f (bb==3) {
//cout<<r123<<" "<<r124<<endl;
//cout<<r341<<" "<<r342<<endl;
//
	if (r123==0&&r124==0){
		if (!(p3x>p2x||p1x>p4x)) return 0;
		else return -1;
	}
	if (r123==0) {
		if (p1x<=p3x&&p3x<=p2x) return 0;
		else return -1;
	}
	if (r124==0) {
		if (p1x<=p4x&&p4x<=p2x) return 0;
		else return -1;
	}
	if (r341==0) {
		if (p3x<=p1x&&p1x<=p4x) return 0;
		else return -1;
	}
	if (r342==0) {
		if (p3x<=p2x&&p2x<=p4x) return 0;
		else return -1;
	}
	return -1;

}
int ccw(int aax, int aay, int abx, int aby , int acx, int acy)
{
	return ((aax*acy+abx*aay+acx*aby)-(aax*aby+abx*acy+acx*aay));
}