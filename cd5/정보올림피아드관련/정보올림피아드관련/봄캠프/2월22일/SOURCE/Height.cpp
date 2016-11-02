#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Max	200
#define Max_point 3000
typedef struct queue { int p1;int p2;struct queue *link;}Queue;
Queue *head,*tail;

int ins_x[Max],ins_y[Max];
int x[Max_point],y[Max_point];
int dist[Max_point];
int pp;
int n;
int all_y[Max];
int ap;
int table[Max_point][Max_point];
int flag[Max_point][Max_point];
int solution;
void read_dat()
{
	FILE *in=fopen("height.inp","r");
	int i;
	fscanf(in,"%d",&n);
	for(i=1;i<=n+1;i++)
	{
		fscanf(in,"%d %d",&ins_x[i],&ins_y[i]);
	}
	fclose(in);
}

void output_dat()
{
	FILE *out=fopen("height.out","w");
	fprintf(out,"%d\n",solution);
	fclose(out);
}

void make_y()
{
	int i;
	int flag[300];
	for(i=0;i<300;i++)
		flag[i]=0;
	for(i=1;i<=n+1;i++)
	{
		flag[ins_y[i]+100]=1;
	}
	for(i=0;i<=200;i++)
	{
		if(flag[i])
		{
			all_y[++ap]=i-100;
		}
	}
}

void make_point()
{
	int i,j;
	int deltax,deltay;
	for(i=2;i<=n+1;i++)
	{
		deltax=ins_x[i]-ins_x[i-1];
		deltay=ins_y[i]-ins_y[i-1];
		if(deltax==0)
		{
			if(deltay>0)
			{
				for(j=1;j<=ap;j++)
				{
					if(all_y[j]<ins_y[i-1]) continue;
					if(all_y[j]>ins_y[i]) break;
					pp++;
					x[pp]=ins_x[i];
					y[pp]=all_y[j];
				}
			}
			else
			{
				for(j=ap;j>0;j--)
				{
					if(all_y[j]>ins_y[i-1]) continue;
					if(all_y[j]<ins_y[i]) break;
					pp++;
					x[pp]=ins_x[i];
					y[pp]=all_y[j];
				}
			}
		}
	}
	for(i=2;i<=pp;i++)
	{
		dist[i]=abs(x[i]-x[i-1])+abs(y[i]-y[i-1]);
	}
}

void process()
{
	int a,b;
	Queue *t;
	tail=new Queue;
	tail->link=NULL;
	head=new Queue;
	head->link=tail;
	head->p1=1;
	head->p2=pp;
	while(head!=tail)
	{
		// p1--    p2
		if(head->p1>1)
		{
			a=head->p1-1;
			b=head->p2;
			if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a+1][b]+dist[a+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a+1][b]+dist[a+1])
				{
					table[a][b]=table[a+1][b]+dist[a+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		// p1     p2--
		if(head->p2>1)
		{
			a=head->p1;
			b=head->p2-1;
	 		if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a][b+1]+dist[b+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a][b+1]+dist[b+1])
				{
					table[a][b]=table[a][b+1]+dist[b+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		// p1++    p2
		if(head->p1<pp)
		{
			a=head->p1+1;
			b=head->p2;
			if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a-1][b]+dist[a];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a-1][b]+dist[a])
				{
					table[a][b]=table[a-1][b]+dist[a];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		//p1 p2++
		if(head->p2<pp)
		{
			a=head->p1;
			b=head->p2+1;
			if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a][b-1]+dist[b];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a][b-1]+dist[b])
				{
					table[a][b]=table[a][b-1]+dist[b];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		//p1-- p2--
		if(head->p1>1&&head->p2>1)
		{
			a=head->p1-1;
			b=head->p2-1;
			if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a+1][b+1]+dist[a+1]+dist[b+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a+1][b+1]+dist[a+1]+dist[b+1])
				{
					table[a][b]=table[a+1][b+1]+dist[a+1]+dist[b+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		// p1++ p2++
		if(head->p1<pp&&head->p2<pp)
		{
			a=head->p1+1;
			b=head->p2+1;
			if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a-1][b-1]+dist[a]+dist[b];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a-1][b-1]+dist[a]+dist[b])
				{
					table[a][b]=table[a-1][b-1]+dist[a]+dist[b];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		//p1-- p2++
		if(head->p1>1&&head->p2<pp)
		{
			a=head->p1-1;
			b=head->p2+1;
			if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a+1][b-1]+dist[a+1]+dist[b];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a+1][b-1]+dist[a+1]+dist[b])
				{
					table[a][b]=table[a+1][b-1]+dist[a+1]+dist[b];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		//p1++ p2--
		if(head->p1<pp&&head->p2>1)
		{
			a=head->p1+1;
			b=head->p2-1;
			if(y[a]==y[b])
			{
				if(flag[a][b]==0)
				{
					flag[a][b]=1;
					table[a][b]=table[a-1][b+1]+dist[a]+dist[b+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
				else if(table[a][b]>table[a-1][b+1]+dist[a]+dist[b+1])
				{
					table[a][b]=table[a-1][b+1]+dist[a]+dist[b+1];
					tail->p1=a;
					tail->p2=b;
					tail->link=new Queue;
					tail=tail->link;
				}
			}
		}
		t=head;
		head=head->link;
		delete t;
	}
}

void get_solution()
{
	int i;
	solution=-1;
	for(i=1;i<=pp;i++)
	{
		if(flag[i][i]) 
		{
			solution=table[i][i];
			break;
		}
	}
	for(;i<=pp;i++)
	{
		if(flag[i][i]&&table[i][i]<solution)
		{
			solution=table[i][i];
		}
	}
	if(solution>0)
		solution*=2;
}

void main()
{
	read_dat();
	make_y();
	make_point();
	process();
	get_solution();
	output_dat();
}


	


					
					
					

			

	
		
	


	