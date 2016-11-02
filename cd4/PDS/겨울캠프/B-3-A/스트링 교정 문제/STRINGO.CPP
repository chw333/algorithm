#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

FILE *fp;

char buf[2][100];
int dt[100][100];
int ans = 9999;

void input()
{
	fp = fopen("stringo.inp","r");
		fgets(buf[0],100,fp);
		fscanf(fp,"\n");
		fgets(buf[1],100,fp);
	fclose(fp);
}
void process()
{
	int i,j,k;
	for(i=1;i<strlen(buf[1]);i++){
		dt[i][0] = i;
		for(j=1;j<strlen(buf[0]);j++){
			if(buf[0][i] == buf[1][j]){
				dt[i][j] = dt[i-1][j-1];
			}
			else
			{
				int che[3] = {0,0,0},min = 9999;
				che[0] = dt[i-1][j] + 1;
				che[1] = dt[i][j-1] + 1;
				che[2] = dt[i-1][j-1]+1;
				for(k=0;k<3;k++)if(che[k] < min)min = che[k];
				dt[i][j] = min;
			}
		}
	}
	int imsi;
	imsi = strlen(buf[1]);
	for(i=0;i<strlen(buf[0]);i++)if(dt[strlen(buf[1])-1][i] < ans)ans = dt[strlen(buf[1])-1][i];
}
void output()
{
	int i,j;
	fp = fopen("stringo.ans","w");
		fprintf(fp,"%d\n",ans);
	for(i=0;i<strlen(buf[0]);i++)fprintf(fp,"%c",buf[0][i]);
	for(i=0;i<strlen(buf[0]);i++){
		if(buf[0][i] == buf[1][i])fprintf(fp,"|");
		else fprintf(fp," ");
	}
	fprintf(fp,"\n");
	for(i=0;i<strlen(buf[1]);i++)fprintf(fp,"%c",buf[1][i]);

	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}
