#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int sum;
int m;
int dt[100][2];
void input()
{
	int i,n;
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
			sum += dt[i][1];
		}
	fclose(fp);
}
void process()
{
	int i,j,set = 1;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(dt[i][1] > dt[j][1]){
				int imsi;
				imsi = dt[i][0];dt[i][0] = dt[j][0];dt[j][0] = imsi;
				imsi = dt[i][1];dt[i][1] = dt[j][1];dt[j][1] = imsi;
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
	
}
void output()
{
	int i,j;
	printf("%d",m);
}
void main(void)
{
	input();
	process();
	output();
}
