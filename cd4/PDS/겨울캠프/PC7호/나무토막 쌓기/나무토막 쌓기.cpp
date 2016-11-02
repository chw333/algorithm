#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int wi[100],at[100];
int cur[200][4];
int dt[100][4];
int n;

void input()
{
	int i,j;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fscanf(fp,"%d %d %d %d",&dt[i][0],&dt[i][1],&dt[i][2],&dt[i][3]);
		}
	fclose(fp);
}
void process()
{
	int i,j,p[3],k,t = 0;
	int buf[100],m;
	for(i=0;i<n;i++){
		buf[0] = dt[i][0];
		buf[1] = dt[i][1];
		buf[2] = dt[i][2];
		buf[3] = dt[i][3];
		
		for(j=0;j<3;j++){
			int imsi;
			imsi = buf[1];
			buf[1] = buf[2];
			buf[2] = buf[3];
			buf[3] = imsi;
			cur[t][0] = dt[i][0];
			for(k=1;k<=3;k++)cur[t][k] = buf[k];
			t++;
		}
	}
	for(i=0;i<(3*n-1);i++){
		for(j=i+1;j<(3*n);j++){
			if(cur[i][1] * cur[i][2] < cur[j][1] * cur[j][2])
			{
				int imsi;
				imsi = cur[i][0]; cur[i][0] = cur[j][0]; cur[j][0] = imsi;
				imsi = cur[i][1]; cur[i][1] = cur[j][1]; cur[j][1] = imsi;
				imsi = cur[i][2]; cur[i][2] = cur[j][2]; cur[j][2] = imsi;
				imsi = cur[i][3]; cur[i][3] = cur[j][3]; cur[j][3] = imsi;
			}
		}
	}
	
	p[0] = cur[0][1];p[1] = cur[0][2];p[2] = cur[0][3];

	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			if((cur[j][1] < p[0] && cur[j][2] < p[1]) || (cur[j][1] < p[1] && cur[j][2] < p[0])){
				p[0] = cur[j][1];
				p[1] = cur[j][2];
				p[2] = cur[j][3];
				wi[i] = j;
				at[i]++;
			}
			if(k < at[i]){
				k = at[i];
				m = wi[i];
			}
		}
	}
/*	for(i=0;i<3*n;i++){
		for(j=0;j<4;j++)fprintf(fp,"%3d ",cur[i][j]);
		fprintf(fp,"%3d %3d %3d \n",(cur[i][1] * cur[i][2]), wi[i], at[i]);
	}
	fclose(fp);*/
}
void output()
{
	int i,k;
	for(i=n;i>=0;i--){
		printf("%d",wi[k]);
		k = wi[k];
	}
}
void main(void)
{
	input();
	process();
	output();
} 

