#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int mr[100][100];


void input()
{
	fp = fopen("fire.inp","r");
	fscanf(fp,"%d %d\n",&n,&k);
	for(i=0;i<n;i++){
		fscanf(fp,"%d %d\n",&hs[i][0],&hs[i][1]);
		mr[hs[i][0]][hs[i][1]] = 1;
	}
	for(i=0;i<k;i++){
		fscanf(fp,"%d %d %d %d\n",&tm[i][0],&tm[i][1],&tm[i][2],&tm[i][3]);
		for(j=tm[i][0] + 1;j< tm[i][1];j++){
			for(k=tm[i][2] +1;k< tm[i][3];k++){
				mr[j][k] = 2;
			}
		}
	}
	fclose(fp);
}
void process()
{
	int i,j;
		
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
