#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define Max 101
#define Max_value 2000000
#define Max_Time 104800
#define K 1
#define Add_fever 0.77
#define Loop 800


int n;
int dat[Max][Max];
int save[Max];
int solution;
int ch[4][2]={{0,0},{2,3},{1,3},{1,2}};
clock_t st;


void read_dat()
{
	FILE *in=fopen("chem.inp","r");
	int i,j;
	fscanf(in,"%d",&n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			fscanf(in,"%d",&dat[i][j]);
		}
	}
	fclose(in);
}

void output_dat()
{
	FILE *out=fopen("chem.out","w");
	int i,j;
	fprintf(out,"%d\n",solution);
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(save[j]==i)
			{
				fprintf(out,"%d ",j);
			}
		}
		fprintf(out,"\n");
	}
	fclose(out);
}


void proc1()
{
	int i,j,k;
	int g[Max][Max];
	int g_flag[Max];
	int group[Max];
	int min,mx,my;
	int num[Max];
	int np;
	for(i=1;i<=n;i++)
	{
		g_flag[i]=0;
		group[i]=i;
		for(j=1;j<=n;j++)
		{
			g[i][j]=dat[i][j];
		}
	}
	for(i=1;i<=(n-3);i++)
	{
		min=Max_value;
		for(j=1;j<n;j++)
		{
			if(g_flag[j]) continue;
			for(k=j+1;k<=n;k++)
			{
				if(g_flag[k]) continue;
				if(g[j][k]<min)
				{
					min=g[j][k];
					mx=j;
					my=k;
				}
			}
		}
		for(j=1;j<=n;j++)
		{
			if(group[j]==my)
				group[j]=mx;
		}
		for(j=1;j<=n;j++)
		{
			g[mx][j]+=g[my][j];
			g[j][mx]=g[mx][j];
		}
		g_flag[my]=1;
	}
	solution=0;
	for(i=1;i<n;i++)
	{
		if(g_flag[i]) continue;
		for(j=i+1;j<=n;j++)
		{
			if(g_flag[j]) continue;
			solution+=g[i][j];
		}
	}

	np=0;
	for(i=1;i<=n;i++)
	{
		if(g_flag[i]) continue;
		num[++np]=i;
	}
	for(i=1;i<=np;i++)
	{
		if(num[i]==group[i])
		{
			group[i]=i;
		}
	}

	for(i=1;i<=n;i++)
	{
		save[i]=group[i];
	}
}

void proc2()
{
	int i,j;
	double fever;
	int value,new_value,old_value;
	int list[Max];
	int old_list[Max];
	int r1,r2;
	int count[4];
	double temp;
	
//	while(clock()-st<Max_Time)
	while(1)
	{
		count[1]=count[2]=count[3]=0;
		for(i=1;i<=n;i++)
		{
			list[i]=rand()%3+1;
			count[list[i]]++;
		}
		value=0;
		while(1)
		{
			if(count[1]==0)
			{
				r1=rand()%n+1;
				count[list[r1]]--;
				count[1]++;
				list[r1]=1;
			}
			else if(count[2]==0)
			{
				r1=rand()%n+1;
				count[list[r1]]--;
				count[2]++;
				list[r1]=2;
			}
			else if(count[3]==0)
			{
				r1=rand()%n+1;
				count[list[r1]]--;
				count[3]++;
				list[r1]=3;
			}
			else
			{
				break;
			}
		}

			
		for(i=1;i<n;i++)
		{
			for(j=i+1;j<=n;j++)
			{
				if(list[i]!=list[j])
					value+=dat[i][j];
			}
		}
		old_value=value;
		

		while(1)
		{
			fever=1;
			for(i=1;i<=Loop;i++)
			{
				do
				{
					r1=rand()%n+1;
				} while(count[list[r1]]==1);
				r2=ch[list[r1]][rand()%2];
				new_value=value;
				for(j=1;j<=n;j++)
				{
					if(list[j]==r2)
					{
						new_value-=dat[r1][j];
					}
					else if(list[j]==list[r1])
					{
						new_value+=dat[r1][j];
					}
				}
				if(new_value>value)
				{
					count[list[r1]]--;
					count[r2]++;
					list[r1]=r2;
					value=new_value;
				}
				else if(exp(new_value-value)/(K*fever)>(rand()%100000001)/100000000.)
				{
					count[list[r1]]--;
					count[r2]++;
					list[r1]=r2;
					value=new_value;
				}
				else
				{
					for(j=1;j<=n;j++)
					{
						if(list[j]==r2)
						{
							new_value+=dat[r1][j];
						}
						else if(list[j]==list[r1])
						{
							new_value-=dat[r1][j];
						}
					}
				}
				fever*=Add_fever;
			}
			if(value>old_value)
			{
				old_value=value;
				for(i=1;i<=n;i++)
					old_list[i]=list[i];
			}
			else
			{
				break;
			}
		}
		if(old_value>solution)
		{
			solution=old_value;
			printf("%d\n",solution);
			for(i=1;i<=n;i++)
			{
				save[i]=old_list[i];
			}
		}
	}
}


		
		

void main()
{
	
	st=clock();
	srand((unsigned int)time(NULL));
	read_dat();
//	proc1();
	proc2();
	output_dat();
} 
	