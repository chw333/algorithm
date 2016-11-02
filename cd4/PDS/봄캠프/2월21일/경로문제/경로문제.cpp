#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define N 5
#define MAX 100

int a[N+1][N+1];
int v[N+1];
int queue[MAX];
int count[MAX][MAX];
int head,tail;
int pri[MAX][MAX];
void main(void)
{
	int i,j,p,n;
	FILE *fp;
	fp = fopen("path1.inp","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;;i++){
			int x,y;
			if(x == -1 && y == -1)break;
			fscanf(fp,"%d %d\n",&x,&y);
			a[x+1][y+1] = 1;
		}
	for(p=1;p<=N;p++){
		for(i=1;i<=N;i++)
			v[i] = 0;
		head=tail=0;
		queue[tail++]=p;v[p]=1;
		do{
			i=queue[head++];
			for(j=1;j<=N;j++){
				if(a[i][j]==1 && v[j] == 0){
					//count[p][tail]=count[p][head-1]+1;
					//printf("%d->%d ",i,j);
					pri[i][j]++;			
					queue[tail++]=j;
					v[j] = 1;
				}
			}
		}
		while(head!=tail);
		//printf("\n");
	}
	fp = fopen("path1.out","w");
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fprintf(fp,"%d ",pri[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}
