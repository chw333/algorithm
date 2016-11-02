#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int n;
int dt[100][2];

void input()
{
	int i;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d %d\n",&dt[i][0],&dt[i][1]);
	fclose(fp);
}
void process()
{
	int i,j,open1,open2,check[100];

	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(dt[i][0] > dt[j][0]){
				int imsi;
				imsi = dt[i][0]; dt[i][0] = dt[j][0]; dt[j][0] = imsi;
				imsi = dt[i][1]; dt[i][1] = dt[j][1]; dt[j][1] = imsi;
			}
		}
	}
	open1 = 0;
	open2 = 0;
	for(i=0;;i++){
			int cnt = 0;
			for(j=0;j<n;j++){
				if(open1< dt[j][0] && open2<dt[j][1] && check[j] != 1)
				{
					check[j] = 1;
					open1 = dt[j][0];open2 = dt[j][1];
					printf("%d ",j+1);
				}
			}
			for(j=0;j<n;j++){
				if(check[j] == 1)cnt++;
				open1 = open2 = 0;
			}
			printf("\n");
			if(cnt == n)break;	
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

