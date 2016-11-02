#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>

int a[100][100],ar[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int list[100][2],top,n,dt[100][100],max,k[100][2],p;

void indt()
{
	int i,j;
	top = 0;
	for(i=0;i<100;i++)
		for(j=0;j<2;j++)
			list[i][j] = 0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			a[i][j] = dt[i][j];
}
void output(void)
{
	int i;
	if(max < p){
		max = p;
		for(i=0;i<100;i++)k[i][0] = k[i][1] = 0;
		for(i=0;i<=top;i++){k[i][0] = list[i][0];k[i][1] = list[i][1];}
	}
}

void visit(int x, int y)
{
	int i;
	a[y][x]=0;
	list[++top][0]=x;
	list[top][1]=y;

	if(top == 7) output();
	else
		for(i=0; i<=3; i++){
		   if(a[y+ar[i][1]][x+ar[i][0]] == 1)
				visit(x+ar[i][0],y+ar[i][1]);
		}

	--top;
	a[y][x]=1;
}

void main(void)
{
	int i,j;
	FILE *fp;
	fp = fopen("back.inp","r");
		fscanf(fp,"%d\n",&n);
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++){
			fscanf(fp,"%d ",&a[i][j]);
			dt[i][j] = a[i][j];
		}
		fscanf(fp,"\n");
		for(i=0;i<n;i++){
						   visit(i,0);indt();
						   visit(0,i);indt();
						   visit(i,n-1);indt();
						   visit(n-1,i);indt();
		}
	fclose(fp);
	visit(1,1);
	printf("%d",max);
}