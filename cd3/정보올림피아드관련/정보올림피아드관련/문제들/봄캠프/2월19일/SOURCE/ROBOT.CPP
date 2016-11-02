#include<stdio.h>
#define infile "robot.inp"
#define outfile "robot.out"
#define N 101
#define K 251
char m[N][N],check[N][N];
long min[N][N];
int a,b,path[K][2],np=0;
int qu[K][2],from[K];
int front,rear;
void input(void)
{
	FILE *fp=fopen(infile,"r");
	fscanf(fp,"%d\n",&a);
	int i,j;
	char k;
	for(i=0;i<a;i++)
	{
		for(j=0;j<a;j++)
		{
			fscanf(fp,"%c",&k);
			k-=48;
			m[i][j]=k;
			min[i][j]=2147483647;
		}
		fscanf(fp,"\n");
	}
	min[0][0]=0;
	fclose(fp);
}
void process(void)
{
	int i,j;
	int mx,my;
	long gi;
	rear=1; front=0;
	qu[0][0]=qu[0][1]=0;
	from[0]=-1;
	while(1)
	{
		if(front>=rear) break;
		mx=qu[front][0]; my=qu[front][1];
		gi=min[mx][my]; check[mx][my]=0;
		for(i=mx-1;i>=0;i--)
		{
			if(m[i][my]==0) break;
			if(min[i][my]>gi+1)
			{
				min[i][my]=gi+1;
				if(check[i][my]==0)
				{
					check[i][my]=1;
					qu[rear][0]=i;
					qu[rear][1]=my;
					from[rear]=front;
					rear++;
				}
				else
				{
					for(j=front+1;j<rear;j++)
						if(qu[j][0]==i && qu[j][1]==my)
						{
							from[j]=front;
							break;
						}
				}
			}
		}
		for(i=my-1;i>=0;i--)
		{
			if(m[mx][i]==0) break;
			if(min[mx][i]>gi+1)
			{
				min[mx][i]=gi+1;
				if(check[mx][i]==0)
				{
					check[mx][i]=1;
					qu[rear][0]=mx;
					qu[rear][1]=i;
					from[rear]=front;
					rear++;
				}
				else
				{
					for(j=front+1;j<rear;j++)
						if(qu[j][0]==mx && qu[j][1]==i)
						{
							from[j]=front;
							break;
						}
				}
			}
		}
		for(i=mx+1;i<a;i++)
		{
			if(m[i][my]==0) break;
			if(min[i][my]>gi+1)
			{
				min[i][my]=gi+1;
				if(check[i][my]==0)
				{
					check[i][my]=1;
					qu[rear][0]=i;
					qu[rear][1]=my;
					from[rear]=front;
					rear++;
				}
				else
				{
					for(j=front+1;j<rear;j++)
						if(qu[j][0]==i && qu[j][1]==my)
						{
							from[j]=front;
							break;
						}
				}
			}
		}
		for(i=my+1;i<a;i++)
		{
			if(m[mx][i]==0) break;
			if(min[mx][i]>gi+1)
			{
				min[mx][i]=gi+1;
				if(check[mx][i]==0)
				{
					check[mx][i]=1;
					qu[rear][0]=mx;
					qu[rear][1]=i;
					from[rear]=front;
					rear++;
				}
				else
				{
					for(j=front+1;j<rear;j++)
						if(qu[j][0]==mx && qu[j][1]==i)
						{
							from[j]=front;
							break;
						}
				}
			}
		}
		front++;
	}
}
void output(void)
{
	FILE *fp=fopen(outfile,"w");
	if(min[a-1][a-1]==2147483647)
		fprintf(fp,"impossible\n");
	else
	{
		fprintf(fp,"%ld\n",min[a-1][a-1]-1);
		int i,j;
		for(i=rear-1;i>0;i--)
			if(qu[i][0]==a-1 && qu[i][1]==a-1)
				break;
		j=i;
		while(1)
		{
			path[np][0]=qu[j][0];
			path[np++][1]=qu[j][1];
			j=from[j];
			if(j==-1) break;
		}
		for(i=np-2;i>0;i--)
		{
			fprintf(fp,"%d %d\n",path[i][0]+1,path[i][1]+1);
		}
	}
	fclose(fp);
}
int main(void)
{
	input();
	process();
	output();
	return 0;
}