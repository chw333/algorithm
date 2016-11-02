#include<fstream.h>
#include<memory.h>

#define i_fnm "tree.inp"
#define o_fnm "tree.out"
#define MAXN 102
#define INF  10000

int a[MAXN][MAXN],b[MAXN],c[MAXN][MAXN],d[MAXN],e[MAXN][MAXN],n,Sol,Opt;

void In(void)
{
	int l1,l2;

	ifstream fin(i_fnm);
	fin >> n;
	for(l1=0;l1<n;l1++)
	{
		for(l2=0;l2<n;l2++)
		{
			fin >> a[l1][l2];
			c[l1][l2]=INF;
			b[l1]+=a[l1][l2];
		}
		a[l1][l2]=0;
	}
	fin.close();
}

void MakeGraph(void)
{
	int l1,l2;

	for(l1=1;l1<n;l1++)
	{
		for(l2=0;l2<n;l2++)
		{
			if(a[l1][l2])
			{
				c[l1][l2]=b[l2];
			}
		}
	}
}

void Prim(void)
{
	int Min,Min2,Temp1,Temp2;
	int l1,l2,l3;

	d[0]=-1;
	for(l1=1;l1<n;l1++)
	{
		Min=INF;
		Min2=INF;
		for(l2=0;l2<n;l2++)
		{
			if(d[l2])
			{
				for(l3=0;l3<n;l3++)
				{
					if(!d[l3]&&c[l3][l2]<Min)
					{
						Min=c[l3][l2];
						Min2=b[l3];
						Temp1=l2;
						Temp2=l3;
					}
					if(!d[l3]&&c[l3][l2]==Min&&b[l3]<Min2)
					{
						Min=c[l3][l2];
						Min2=b[l3];
						Temp1=l2;
						Temp2=l3;
					}

				}
			}
		}
		d[Temp2]=1;
		e[Temp1][Temp2]=e[Temp2][Temp1]=1;
		Sol+=Min;
	}
	Opt=Sol;
}

void Prim2(void)
{
	int Min,Min2,Temp1,Temp2;
	int l1,l2,l3;

	d[0]=-1;
	for(l1=1;l1<n;l1++)
	{
		Min=INF;
		Min2=INF;
		for(l2=0;l2<n;l2++)
		{
			if(d[l2])
			{
				for(l3=0;l3<n;l3++)
				{
					if(!d[l3]&&c[l3][l2]+b[l3]<Min)
					{
						Min=c[l3][l2]+b[l3];
						Temp1=l2;
						Temp2=l3;
					}
				}
			}
		}
		d[Temp2]=Temp1+1;
		Sol+=(Min-b[Temp2]);
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		for(l1=0;l1<n;l1++)
		{
			for(l2=0;l2<n;l2++)
			{
				e[l1][l2]=0;
			}
		}
		for(l1=1;l1<n;l1++)
		{
			l2=d[l1]-1;
			e[l1][l2]=e[l2][l1]=1;
		}
	}
}

void Do(void)
{
	MakeGraph();
	Prim();
	memset(d,0,sizeof(d));
	Sol=0;
	Prim2();
	memset(d,0,sizeof(d));
	Sol=0;
}

void Ot(void)
{
	int l1,l2;

	ofstream fout (o_fnm);
	fout << Opt << endl;
	for(l1=0;l1<n;l1++)
	{
		fout << e[l1][0];
		for(l2=1;l2<n;l2++)
		{
			fout << ' ' << e[l1][l2];
		}
		fout << endl;
	}
	fout.close();
}

int main(void)
{
	In();
	Do();
	Ot();

	return 0;
}