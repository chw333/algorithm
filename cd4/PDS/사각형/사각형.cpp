#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int buf[1000][1000];
int dt[100][2];
int max1,max2,n,sum;
void input()
{
	int i;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fscanf(fp,"%d %d\n",&dt[i][0],&dt[i][1]);
			if(dt[i][0] > dt[i][1]){
				int imsi;
				imsi = dt[i][0]; dt[i][0] = dt[i][1]; dt[i][1] = imsi;
			}
			if(dt[i][0] > max1) max1 = dt[i][0];
			if(dt[i][1] > max2) max2 = dt[i][1];
		}
	fclose(fp);
	printf("4");
}
void process()
{
	int i,j,k;
	for(i=0;i<n;i++){
		for(j=0;j<dt[i][0];j++){
			for(k=0;k<dt[i][1];k++){
				buf[j][k] = 1;
			}
		}
	}
	for(i=0;i<=max1;i++)
		for(j=0;j<=max2;j++)
			sum+=buf[i][j];
}
void output()
{
	printf("%d",sum);
}
void main(void)
{
	input();
	process();
	output();
}
