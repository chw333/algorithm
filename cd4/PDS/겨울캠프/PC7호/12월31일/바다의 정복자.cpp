#include<stdio.h>
#include<conio.h>
int cur;
int buf[100][2];

void input()
{
	FILE *fp;
	int cnt1,cnt2,i;
	fp = fopen("inpout.txt","r");
	fscanf(fp,"%d\n",&cur);
	fscanf(fp,"%d %d\n",&cnt1,&cnt2);
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

}		
void main(void)
{
	input();
	process();
}

