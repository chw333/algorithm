#include <fstream.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

ifstream in("boxsum.in");
ofstream out("boxsum.out");

struct p {
	double x, y1, y2;
	int op;
};



struct p ln[10000+1];
double yl[10000+1];
int yb[10000+1];
int yn, n;
double area;

void inserty(double y)
{
	int fn, i;
	fn=0;
	for(i=1;i<=yn;i++) {
		if(yl[i]<=y) fn=i;
	}
	if(yl[fn]<y){
		for(i=yn;i>=fn+1;i--) yl[i+1]=yl[i];
		yn++; yl[fn+1]=y;
	}
}
void input()
{
	int cnt, i;
	double x1, y1, x2, y2;

	n=0;
    yl[0]=-100000;
	in >> cnt;

	for(i=1;i<=cnt;i++) {
		in >> x1 >> y1 >> x2 >> y2;
		x2=x2+x1;
		y2=y2+y1;
		inserty(y1);
		inserty(y2);
		n++;
		ln[n].x=x1; ln[n].y1=y1; ln[n].y2=y2; ln[n].op=1;
		n++;
		ln[n].x=x2; ln[n].y1=y1; ln[n].y2=y2; ln[n].op=-1;
	}
	yn--;
	for(i=1;i<=yn;i++) yb[i]=0;
}
void output()
{
	char rett[100];

	sprintf(rett,"%.2lf",area);
	out << rett;
}
int findy(double y)
{
	int i,fy;
	for(i=1;i<=yn+1;i++){
		if(yl[i]==y) fy=i;
	}
	return fy;
}

void sort_x()
{

	int i,j;
	struct p tp;
	ln[0].x=0;
	for(i=1;i<=n;i++) {
		for(j=i+1;j<=n;j++) {
			if(ln[i].x>ln[j].x) {
				tp=ln[i]; ln[i]=ln[j]; ln[j]=tp;
			}
		}
	}
}
void proc()
{
	int i,j;
	int s,e;


	sort_x();
	area=0;
	for(i=1;i<=n;i++){
		for(j=1;j<=yn;j++) {
			if(yb[j]>0) {
				area=area+(ln[i].x-ln[i-1].x)*(yl[j+1]-yl[j]);
			}
		}
		s=findy(ln[i].y1);
		e=findy(ln[i].y2);
		for(j=s;j<=e-1;j++)
			yb[j]=yb[j]+ln[i].op;
	}
}
void main()
{
	input();
	proc();
	output();
}

/*
void main()
{
	double x1, y1, x2, y2;
	int n=30, i;
	char ret[100];

	out << n << endl;
	srand( (unsigned)time( NULL ) );

	for(i=0;i<n;i++ ) {
		x1=(double)(rand()%1000)/2;
		y1=(double)(rand()%1000)/2;
		x2=(double)(rand()%100)/3;
		y2=(double)(rand()%100)/3;
	    sprintf(ret,"%.2lf %.2lf %.2lf %.2lf", x1,y1,x2,y2);
	    out << ret << endl;
	}
}
*/