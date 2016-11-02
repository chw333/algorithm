#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int dt[100][3];
void back(
void main(void)
{
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		fscanf(fp,"%d\n",&p);
		for(i=0;i<p;i++){
			fscanf(fp,"%d %d %d\n",&dt[i][0],&k,&dt[i][2]);
			if(k == 'H')dt[i][1] = 1;
			if(k == 'V')dt[i][1] = 2;
		}
	fclose(fp);
	for(i=0;i<p;i++){
		for(j=i+1;j<p;j++){
			if(dt[i][1] > dt[i][2]){
				int imsi;
				imsi = 
			
}