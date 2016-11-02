#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define N 15

FILE *fp;
int n[2];
int dt[100][100];
int fun[100][100];

void back(int x,int y)
{
	int i;
	if(dt[x][y] == 1)return;
	if(fun[x][y] == 1)return;

		fun[x-1][y] = 1;
		back(x-1,y);
		fun[x-1][y] = 0;

		fun[x+1][y] = 1;
		back(x+1,y);
		fun[x+1][y] = 0;

		fun[x][y-1] = 1;
		back(x,y-1);
		fun[x][y-1] = 0;

		fun[x][y+1] = 1;
		back(x,y+1);
		fun[x][y+1] = 0;
	if(x == N && y == N)return;
}

void main(void)
{
	int i,j;
	fp = fopen("mazefind.inp","r");
		fscanf(fp,"%d %d\n",&n[0],&n[1]);

		for(i=0;i<n[0];i++){
			for(j=0;j<n[1];j++){
				fscanf(fp,"%d,",&dt[i][j]);
			}
			fscanf(fp,"\n");
		}
	fclose(fp);
	back(1,1);

}

