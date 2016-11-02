#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
FILE *fp;
int cur[100][2];
int n,d;
int buf[100],k[100];

void input()
{
	int i,j,k,dt;
	fp = fopen("diameter.in","r");
		fscanf(fp,"%d\n",&n);
		for( i = 0 ; i < n ; i++)
		{

			char im1,im2;
			fscanf(fp,"%c %c %d",&im1,&im2,&k[i]);
			cur[i][0] = int(im1 - 'A'+1);
			cur[i][1] = int(im2 - 'A'+1);
		}
		buf[0] = cur[0][1];
		for(i=0;i<n;i++){	
 			if(dt == cur[i][1]){buf[cur[i][1]*2+2] = cur[i][0];dt = 0;}
			
			else {buf[cur[i][1]*2+1] = cur[i][0]; dt = cur[i][1];}
		}
	fclose(fp);
}
/*
void process()
{
	int i,j;
	
}
void output()
{


}*/
void main(void)
{
	input();
//	process();
//	output();


}