#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
char udt[100],dt[100];
int buf[100][100];

void input()
{
	int k = 0,i,j;
	fp = fopen("input.txt","r");
		fgets(dt,100,fp);
		for(i=strlen(dt)-1;i>=0;i--)udt[k++] =  dt[i];
	fclose(fp);
}
void process()
{
	int i,j,k;
	for(i=0;i<=strlen(dt);i++)buf[0][i] = i;
	for(i=1;i<strlen(dt);i++){
		for(j=1;j<strlen(dt);j++){
			if(dt[i+1] != udt[j+1]){
				int min = 999,cur[3];
				cur[0] = buf[i-1][j];
				cur[1] = buf[i-1][j-1];
				cur[2] = buf[i][j-1];
					for(k=0;k<3;k++)if(min > cur[k])min = cur[k];
					buf[i][j] = min+1;
			}
			else
				buf[i][j] = buf[i-1][j-1];
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
