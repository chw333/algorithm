#include<stdio.h>
#include<stdlib.h>
#include<math.h>

FILE *fp;
int dt[30000][2];
int n;

void input()
{
	int i;
	fp = fopen("stroll.in","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fscanf(fp,"%d\n",&dt[i][1]);
			dt[i][0] = i;
			if(dt[i][0] > dt[i][1]){
				int imsi;
				imsi = dt[i][0];dt[i][0] = dt[i][1];dt[i][1] = imsi;
			}
		}
	fclose(fp);
}
void process()
{
	int i,j;
	for(i=0;i<n;i++){
		
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
