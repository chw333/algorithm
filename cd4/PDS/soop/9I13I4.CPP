#include<stdio.h>
#include<conio.h>
int i,j,buf[6][6][2],cnt;
char input,ipt;
int c[6];

void dfs(int x)
{
	int i,j;
	/*
	for (i = 0; i < 6; i++)
	{
		printf("%d ", c[i]);
	}
	printf("\n");
	*/

	for(i=0;i<6;i++)
	if(buf[x][i][0] != 0 && c[i] == 0)
	{
		c[i] = c[x] * buf[x][i][1] / buf[x][i][0];
		dfs(i);
	}
}

void main()
{

	FILE *fp;
	clrscr();
	fp = fopen("input.in","r");
		for(i=0;i<5;i++){
			int d1,d2;
			char k1,k2;
			fscanf(fp,"%d %c %d %c\n",&d1,&k1,&d2,&k2);
			buf[k1-'A'][k2-'A'][0] = d1;
			buf[k1-'A'][k2-'A'][1] = d2;
			buf[k2-'A'][k1-'A'][0] = d2;
			buf[k2-'A'][k1-'A'][1] = d1;
		}
		fscanf(fp,"%d %c",&cnt,&ipt);
		c[ipt-'A'] = cnt;
	fclose(fp);
	dfs(0);
	for(i=0;i<6;i++){
		printf("%d ",c[i]);
	}

}


