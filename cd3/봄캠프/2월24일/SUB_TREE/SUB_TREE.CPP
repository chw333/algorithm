#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int tree[100];
int tree1[100];
int buf[100];
int visit[100];
void input()
{
	fp = fopen("subtree.inp","r");
	fscanf(fp,"%d %d\n",&n,&k);
	for(i=1;i<=n;i++)fscanf(fp,"%d\n",&dt[i]);
	for(i=1;i<n;i++){
		int x,y;
		fscanf(fp,"%d %d\n",&x,&y);
		tree[y] = x;tree1[x] = 1;
	}
	fclose(fp);
}
void process()
{
	int i,j;
	for(i=1;i<=n;i++){
		if(tree1[i] == 0){
			buf[tree[i]] = buf[i][op 
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
