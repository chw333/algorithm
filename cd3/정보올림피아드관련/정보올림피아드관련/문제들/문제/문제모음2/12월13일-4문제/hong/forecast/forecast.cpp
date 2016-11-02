#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100000

ifstream in("forecast10.in");
ofstream out("forecast10.out");

int m, n;
double percent, volume, depth;

struct _c {
	int height;
	int flow;
} city[MAX];

int sortf(void const *p, void const *q)
{
	struct _c *a=(struct _c *)p;
	struct _c *b=(struct _c *)q;
	return (a->height-b->height);
}

void inp()
{
	int i,j;
	in >> m >> n;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			in >> city[i*n+j].height;
	city[n*m].height=999999;
	in >> volume;
	volume=volume/100;
	qsort(city,n*m,sizeof(struct _c),sortf);
}
void oup()
{
	char s1[255];
	sprintf(s1,"%.2lf %.2lf",depth,percent);
	out << s1;
}

void proc()
{
	int deepcity, i;

	for(i=0;i<=m*n;i++) {
		if(i!=0) city[i].flow=i*(city[i].height-city[i-1].height); else city[i].flow=0;
		volume-=city[i].flow;
		if(volume==0) { 
			deepcity=i-1;
			percent=(double)(deepcity+1)/(m*n)*100;
			depth=city[i].height;
			break; 
		} else if(volume<0) { 
			deepcity=i-1; 
			volume+=city[i].flow;
			percent=(double)(deepcity+1)/(m*n)*100;
			depth=city[deepcity].height+volume/(deepcity+1);
			break; 
		}
	}
}

void main()
{
	inp();
	proc();
	oup();
}

/*
#include <time.h>


ofstream out("forecast10.in");

int m=100,n=100;

void main()
{
	srand((unsigned)time(NULL));
	out << m << " " << n << endl;
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			if(j!=0) out << " ";
			out << (rand()%200)-100;
		}
		out << endl;
	}
	out << rand()%9900+100;
}
*/