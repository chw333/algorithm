#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int cur[100][3];
int dt[100];
int k;

int index(int x)
{
	for(int i=1;i<=k;i++){
		if(dt[i] == x){
			return i;
		}
	}
	dt[k++] = 0;	
}
void input()
{
	FILE *fp;
		fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n1);
		for(i=0;i<n1;i++)fscanf(fp,"\n");
		fclose(fp);
		fscanf(fp,"%d\n",&n2);
		for(i=0;i<n2;i++){
			fscanf(fp,"%d %d %d\n",&cur[i][0],&cur[i][1],&cur[i][2]);
		}		
	index(
}
void main(void)
{
	input();
	process();
	output();
}