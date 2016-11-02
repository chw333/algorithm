#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int n;
int dt[100][3];
int save[100][100];
int check[100];

void input()
{
	int i,j;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d %d %d\n",&dt[i][0],&dt[i][1],&dt[i][2]);
	fclose(fp);
}

void process()
{
	int i,j,car[2];
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(dt[i][2] > dt[j][2]){
				int imsi;
				imsi = dt[i][0];dt[i][0] = dt[j][0];dt[j][0] = imsi
				imsi = dt[i][1];dt[i][1] = dt[j][1];dt[j][1] = imsi;
				imsi = dt[i][2];dt[i][2] = dt[j][2];dt[j][2] = imsi;
			}
		}
	}
	save[0][0] = dt[0][0];
	car[0] = dt[0][1];
	car[1] =
		dt[0][2];
	for(j=0;;j++){
		for(i=0;i<n;i++){
			if(car[0] <= dt[i][1] && dt[i][1] <= car[1]){
				car[0] = dt[i][1];
				car[1] = dt[i][2];
				dt[i][0] = save[f++][k];
				check[i] = 1;
			}
			for(j=0;j<n;j++){
				if(dt[j] != 1)goto end;
			}
		output();
end:
		}
	}
}
void output()
{
	int i;
	for(i=0;i<
}
void main(void)
{
	input();
	process();
	output();
} 