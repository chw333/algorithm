#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Max 401
#define Max_value 100000000

int solution;
int list[Max];
int sort[Max];
int n;
void read_dat()
{
	FILE *in=fopen("cowsort.inp","r");
	int i;
	fscanf(in,"%d",&n);
	for(i=1;i<=n;i++)
	{
		fscanf(in,"%d",&list[i]);
		sort[i]=list[i];
	}
	fclose(in);
	solution=Max_value;
}

void q_sort(int l,int r)
{
	int i,j;
	int temp;
	if(l>=r) return;
	i=l-1;
	j=r-1;
	while(i<j)
	{
		do
			i++;
		while(sort[i]<sort[r]);
		while(sort[j]>sort[r]) j--;
		if(i<j)
		{
			temp=sort[i];sort[i]=sort[j];sort[j]=temp;
		}
	}
	temp=sort[i];sort[i]=sort[r];sort[r]=temp;
	q_sort(l,i-1);
	q_sort(i+1,r);
}

void process()
{
	int i,j,k;
	int temp;
	int value;
	int flag[Max];

	for(i=1;i<=n;i++)
	{
		temp=sort[1];
		for(j=1;j<n;j++)
		{
			sort[j]=sort[j+1];
		}
		sort[n]=temp;
		value=0;
		for(j=1;j<=n;j++)
		{
			flag[j]=0; 
		}
		for(j=1;j<=n;j++)
		{
			if(list[j]==sort[j])
			{
				flag[j]=1;
			}
		}

		for(j=1;j<=n;j++)
		{ 
			if(list[j]==sort[j]) continue;
			for(k=1;k<=n;k++)
			{
			 	if(flag[k]==0&&list[j]==sort[k])
				{
					
					if(j!=k)
					{
							value+=(20+abs(j-k));
					}
					
					flag[k]=j;
					break;
				}
			}
		}
		
		if(value<solution)
		{
			solution=value;
		}
	}
}

void output_dat()
{
	FILE *out=fopen("cowsort.out","w");
	fprintf(out,"%d\n",solution);
	fclose(out);
}

void main()
{
	read_dat();
	q_sort(1,n);
	process();
	output_dat();
}



				






		


