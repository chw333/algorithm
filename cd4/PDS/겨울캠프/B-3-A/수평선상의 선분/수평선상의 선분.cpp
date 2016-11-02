#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;

void input()
{
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d %d\n",&dt[i][0],&dt[i][1]);
	fclose(fp);
}
void process()
{
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(dt[i][1] < dt[j][1]){
				int imsi;
				imsi = dt[i][0];dt[i][0] = dt[j][0];dt[j][0] = imsi;
				imsi = dt[i][1];dt[i][1] = dt[j][1];dt[j][1] = imsi;
					}
		}
	}
		
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