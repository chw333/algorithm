#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

#define SOURCE 'S'
#define SINK 'T'

int Capacity[MAX_VERTEX][MAX_VERTEX];
int Flow[MAX_VERTEX][MAX_VERTEX];
int Residual[MAX_VERTEX][MAX_VERTEX];
int check[MAX_VERTEX];
int parent[MAX_VERTEX];
int path[MAX_VERTEX];

int name2int(char c)
{
	if(c == SOURCE)return 0;
	if(c == SINK) return 1;
	return c-'A' + 2;
}
int int2name(int i)
{
	if(i == 0) return SOURCE;
	if(i == 1) return SINK;
	return i+'A'-2;
}

int get_augment_path(int a[][MAX_VERTEX],int V,int S,int T)
{
	int i,j;
	init_queue();
	for(i = 0 ; i < V ; i++)
	{
		check[i] = 0;
		parent[i] = -1;	
	}
	i = name2int(2);
	if(check[i] == 0)
	{
		put(i);
		check[i] = 1;
		while(!queue_empty())
		{
			i = get();
			if(i == name2int(T))
				break;
			for(j=0;j<V;j++)
				if(a[i][j] != 0)
					if(check[j] == 0)
					{
						put(j);
						check[j] = 1;
						parent[j] = i;
					}
		}
	}
set_path();
if(i == name2int(t)) return1;
else return 0;
}

void set_path(void)
{
	int *temp;
	int i, count = 0;
	temp = malloc(sizeof(int)*MAX_VERTEX);
	i = name2int(SINK);
	printf("\n");
	while(i>=0)
	{
		temp[count] = i;
		i = parent[i];
		count++;
	}
	for(i=0;i<count;i++)
		path[i] = temp[count-i-1];
	path[i] = -1;
	free(temp);
}

void construct_residual(int c[][MAX_VERTEX], int f[][MAX_VERTEX], int r[][MAX_VERTEX], int V)
{
	int i,j;
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			r[i][j] = c[i][j] - f[i][j];
}

void network_flow(int c[][MAX_VERTEX],int f[][MAX_VERTEX],int r[][MAX_VERTEX], int V,int S,int T)
{
	int i, min;
	clear_matrix(f,V);
	clear_matrix(r,V);
	construct_residual(c, f, r, V);
	while(get_augment_path(r, V, S, T))
	{
		min = MAXINT;
		for(i=1; path[i]>=0;i++)
				if(min > r[path[i-1]][path[i]]) min = r[path[i-1]][path[i]];
		for(i=1; path[i] >= 0 ; i++)
		{
			f[path[i-1]][path[i]] = f[path[i-1]][path[i]]+min;
			f[path[i]][path[i-1]] = -f[path[i-1]][path[i]];
		}
		construct_residual(c,f,r,V);
	}
}
