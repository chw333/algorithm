#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define Max 10001
#define area(ax,ay,bx,by,cx,cy) ax*by-bx*ay+bx*cy-cx*by+cx*ay-ax*cy
int count[Max];
int x1[Max];
int y1[Max];
int x2[Max];
int y2[Max];
int minx[Max];
int miny[Max];
int maxx[Max];
int maxy[Max];
int solution;
int sp;
int n;
int sx1,sx2,sy1,sy2;
clock_t st;

void read_dat()
{
	FILE *in=fopen("meteor.inp","r");
	int i; 
	int temp;
	fscanf(in,"%d",&n);
	for(i=1;i<=n;i++)
	{
		fscanf(in,"%d %d %d %d",&x1[i],&y1[i],&x2[i],&y2[i]);
		if(x1[i]>x2[i])
		{
			temp=x1[i];x1[i]=x2[i];x2[i]=temp;
			temp=y1[i];y1[i]=y2[i];y2[i]=temp;
		}
	}
	fclose(in);
}

void q_sort(int l,int r)
{
	int i,j;
	int temp;
	if(l>=r) return;
	i=l-1;
	j=r-1;
	while(i<j)
	{
		do
			i++;
		while(x1[i]<x1[r]);
		while(x1[j]>x1[r]) j--;
		if(i<j)
		{
			temp=x1[i];x1[i]=x1[j];x1[j]=temp;
			temp=y1[i];y1[i]=y1[j];y1[j]=temp;
			temp=x2[i];x2[i]=x2[j];x2[j]=temp;
			temp=y2[i];y2[i]=y2[j];y2[j]=temp;
			
		}
	}
	temp=x1[i];x1[i]=x1[r];x1[r]=temp;
	temp=y1[i];y1[i]=y1[r];y1[r]=temp;
	temp=x2[i];x2[i]=x2[r];x2[r]=temp;
	temp=y2[i];y2[i]=y2[r];y2[r]=temp;
	
	q_sort(l,i-1);
	q_sort(i+1,r);
}
		

void output_dat()
{
	FILE *out=fopen("meteor.out","w");
	fprintf(out,"%d\n",solution);
	fprintf(out,"%d %d %d %d\n",sx1,sy1,sx2,sy2);
	fclose(out);
}


void process()
{
	int i,j;
	
	int ccw1,ccw2,ccw3,ccw4;
	

	solution=1;
	sp=1;
	for(i=1;i<n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			if(x2[i]<x1[j]) break;

			ccw1=area(x1[i],y1[i],x2[i],y2[i],x1[j],y1[j]);
			ccw2=area(x1[i],y1[i],x2[i],y2[i],x2[j],y2[j]);
			if((ccw1>=0&&ccw2<=0)||(ccw1<=0&&ccw2>=0))
			{
				ccw3=area(x1[j],y1[j],x2[j],y2[j],x1[i],y1[i]);
				
				ccw4=area(x1[j],y1[j],x2[j],y2[j],x2[i],y2[i]);
				if((ccw3>=0&&ccw4<=0)||(ccw3<=0&&ccw4>=0))
				{
					count[i]++;
					count[j]++;
				}
			}
		}
		if(solution<count[i])
		{
			solution=count[i];
			sx1=x1[i];sx2=x2[i];
			sy1=y1[i];sy2=y2[i];
		}
	}
}

void main()
{
	st=clock();
	read_dat();
	q_sort(1,n);
	process();
	output_dat();
//	printf("%dms\n",clock()-st);
}