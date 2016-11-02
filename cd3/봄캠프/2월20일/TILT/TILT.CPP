#include<stdio.h>
#include<stdlib.h>

#define FILEIN "TILT.INP"
#define FILEOUT "TILT.OUT"

struct Point {short x,y;};

const short MAXN=30000;

short N;
Point n[MAXN];

int input()
{
	FILE *fp=fopen(FILEIN,"r");
	if(fp==NULL)
		return 1;
	fscanf(fp,"%hi",&N);
	for(short i=0;i<N;i++)
		fscanf(fp,"%hi %hi",&n[i].x,&n[i].y);
	fclose(fp);
	return 0;
}

void sort()
{
	short h,hx,i,j;
	Point temp;
	for(h=1;h<N;h=h*3+1);
	for(h/=3;h>0;h/=3)
		for(hx=0;hx<h;hx++)
			for(i=hx+h;i<N;i+=h)
				for(j=i;j>=h;j-=h)
					if(n[j-h].x>n[j].x)
					{
						temp=n[j-h];
						n[j-h]=n[j];
						n[j]=temp;
					}
					else
						break;
}

short sp=-1;

void core()
{
	unsigned long sdx=1,sdy=0;
	register unsigned long dx,dy;
	for(short i=0;i<N-1;i++)
	{
		dx=(long)n[i+1].x-n[i].x;
		dy=labs((long)n[i+1].y-n[i].y);
		if(dy*sdx>sdy*dx)
		{
			sdy=dy;
			sdx=dx;
			sp=i;
		}
	}
}

void output()
{
	FILE *fp=fopen(FILEOUT,"w");
	fprintf(fp,"%hi %hi %hi %hi\n",n[sp].x,n[sp].y,n[sp+1].x,n[sp+1].y);
	fclose(fp);
}

main()
{
	if(input())
		return 1;
	sort();
	core();
	output();
	return 0;
}
