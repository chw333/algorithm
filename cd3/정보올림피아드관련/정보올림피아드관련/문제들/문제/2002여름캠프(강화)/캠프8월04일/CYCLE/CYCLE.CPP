#include <stdio.h>
#define INFILE "cycle05.in"
#define OUTFILE "cycle05.out"

int a[20][20],n;
int b[20][20];
int fol[20][20],pus[20],ciclu[400];

void citire(void)
{
	FILE *f;
	int i,j;
	f=fopen(INFILE,"rt");
	fscanf(f,"%d",&n);
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			fscanf(f,"%d",&a[i][j]);
	fclose(f);
}
void adauga(int pas)
{
	for (int i=0;i<pas;i++)
	{
		b[ciclu[i]][ciclu[i+1]]++;
		b[ciclu[i+1]][ciclu[i]]++;
	}
}
void determina(int nr, int pas)
{
	ciclu[pas]=nr;
	if (nr==ciclu[0] && pas)
	{
		adauga(pas);
		return;
	}
	for (int i=ciclu[0];i<n;i++)
	   if (!pus[i])
		if (a[nr][i] && !fol[nr][i])
		{
			fol[nr][i]=fol[i][nr]=1;
			pus[i]=1;
			determina(i,pas+1);
			fol[nr][i]=fol[i][nr]=0;
			pus[i]=0;
		}
}
void cautare(int nr)
{
	ciclu[0]=nr;
	determina(nr,0);
}
void scriere(void)
{
	long cicluri[400];
	int nrc=0;
	int i,j;
	for (i=0;i<n-1;i++)
		for (j=i+1;j<n;j++)
			if (b[i][j])
			{
				cicluri[nrc]=(b[i][j]/2);
				nrc++;
			}
	int aux, sch;
	do
	{
		sch=0;
		for (i=0;i<nrc-1;i++)
			if (cicluri[i]>cicluri[i+1])
			{
				aux=cicluri[i];cicluri[i]=cicluri[i+1];cicluri[i+1]=aux;
				sch=1;
			}
	}while (sch);
	FILE *g;
	g=fopen(OUTFILE,"wt");
	if (nrc) fprintf(g,"%d\n",nrc);
	else fprintf(g,"NO CYCLE\n");
	for (i=0;i<nrc;i++)
		fprintf(g,"%d ",cicluri[i]);
	fclose(g);
}
void main(void)
{
	citire();
	for (int i=0;i<n;i++)
		cautare(i);
	scriere();
}