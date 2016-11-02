#include<stdio.h>
#include<conio.h>
int cur;
int buf[100][2];

void input()
{
	FILE *fp;
	int cnt1,cnt2,i;
	fp = fopen("무게중심.txt","r");
	fscanf(fp,"%d %d %d\n",&cnt1,&cnt2,&cur);
	for(i=0;i<cur;i++){
			fscanf(fp,"%d %d\n",&buf[i][0],&buf[i][1]);
	}
}
void process()
{
	
	int minx,miny;
	int i;
	for(i=0;i<cur;i++)
	{
		minx += buf[i][0];
		miny += buf[i][1];
	}
	minx = minx/cur;
	miny = miny/cur;
	printf("%d %d",minx,miny);
	minx = int(minx+0.5);
	miny = int(miny+0.5);
}		
void main(void)
{
	input();
	process();
}

