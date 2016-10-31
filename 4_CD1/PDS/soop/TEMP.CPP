#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int cmp(const void *a, const void *b)
{
	return( *((int *)a) - *((int *)b));
}

main()    {
	int i;
	int cnt;
	int dt[100][4];
	int map[100][100];
	int x[100],y[100];
	int nx = 0, ny = 0;
	int tmp = 0;
	FILE *fp;
	clrscr();
	fp = fopen("input.txt","r");
	fscanf(fp,"\n%d\n",&cnt);
	for(i=0;i<cnt;i++) {
		fscanf(fp,"%d %d %d %d\n",&dt[i][0],&dt[i][1],&dt[i][2],&dt[i][3]);
		x[nx++] = dt[i][0]; y[ny++] = dt[i][1];
		x[nx++] = dt[i][2]; y[ny++] = dt[i][3];
	}
	qsort(x, nx, sizeof(int), cmp);
	qsort(y, ny, sizeof(int), cmp);
	for (i=1, tmp=x[0];i<nx;i++)
		if (tmp == x[i]) x[i] = 2000;
					else tmp = x[i];
	for (i=1, tmp=y[0];i<ny;i++)
		if (tmp == y[i]) y[i] = 2000;
					else tmp = y[i];
	qsort(x, nx, sizeof(int), cmp);
	qsort(y, ny, sizeof(int), cmp);
	for (i=0, tmp=nx;i<tmp;i++)
		if (x[i] != 2000) nx = i+1;
	for (i=0, tmp=ny;i<tmp;i++)
		if (y[i] != 2000) ny = i+1;
	for (i=0;i<nx;i++)
		printf("%d ", x[i]);
	printf("\n");
	for (i=0;i<ny;i++)
		printf("%d ", y[i]);
	printf("\n");
	return 0;
}


