#include<stdio.h>
#include<conio.h>

FILE *fp;
int n;
int buf[100],cur[100][2];
void input()
{
	fp = fopen("diameter","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fscanf(fp,"%d %d %d\n",&cur[i][0],&cur[i][1],&buf[i]);
			cur[i][0]-='A';
			cur[i][1]-='A';
		}			
}
void process()
{
}

void output()
{
}

void main(void)
{
	input();
	process();
	output();
}
