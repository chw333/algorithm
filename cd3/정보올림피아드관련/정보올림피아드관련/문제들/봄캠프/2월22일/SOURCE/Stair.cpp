#include <stdio.h>
#include <stdlib.h>
#define Max 101

int table[Max];
int n,k;
void read_dat()
{
	FILE *in=fopen("stair.inp","r");
	fscanf(in,"%d %d",&n,&k);
	fclose(in);
}

void process()
{
	int i,j;
	table[0]=1;
	for(i=1;i<=n;i++)
	{
		for(j=i-1;j>=i-k;j--)
		{
			if(j<0) break;
			table[i]+=table[j];
		}
	}
}

void output_dat()
{
	FILE *out=fopen("stair.out","w");
	fprintf(out,"%d\n",table[n]);
	fclose(out);
}

void main()
{
	read_dat();
	process();
	output_dat();
}
