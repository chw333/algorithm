#include<fstream.h>

#define i_fnm "number.inp"
#define o_fnm "number.out"
#define MAXN 1001
#define MAXX 2001

char Str[2][10]={"holsoon","jjaksoon"};
int a[MAXN],b[MAXX],c[MAXN],n,Cycle,Help,DDR;
long m;
unsigned long Sol;

void In(void)
{
	int l1;

	ifstream fin(i_fnm);
	fin >> n;
	for(l1=0;l1<n;l1++)
	{
		fin >> a[l1];
	}
	fin >> m;
	m++;
	fin.close();
}

void Dynamic(void)
{
	int l1,t1,l2,Big,Dep,index,From;
	DDR=0;

	Cycle=a[n-1];
	for(l1=1;l1<=Cycle;l1++)
	{
		b[l1]=l1+1;
		for(l2=0;l2<n;l2++)
		{
			if(a[l2]>l1)
			{
				break;
			}
			if(b[l1-a[l2]]+1<b[l1])
			{
				b[l1]=b[l1-a[l2]]+1;
			}
		}
		if(b[l1]>=m)
		{
			ofstream fout(o_fnm);
			fout << Str[l1&1] << " win at " << l1 << endl;
			fout.close();
			return;
		}
	}
	Help=1;
	DDR=1;
	for(Dep=0;Help;Dep++)
	{
		From=l1;
		c[0]=b[Cycle];
		for(t1=1;t1<=Cycle;l1++,t1++)
		{
			c[t1]=c[t1-1]+1;
			for(l2=1;l2<n;l2++)
			{
				index=l1-a[l2];
				if(From<=index)
				{
					if(c[t1-a[l2]]+1<c[t1])
					{
						c[t1]=c[t1-a[l2]]+1;
					}
				}
				else
				{
					index=a[l2]-t1;
					index=Cycle-index;
					if(b[index]+1<c[t1])
					{
						c[t1]=b[index]+1;
					}
				}
			}
			if(c[t1]>=m)
			{
				ofstream fout(o_fnm);
				fout << Str[l1&1] << " win at " << l1 << endl;
				fout.close();
				return;
			}
		}
		Help=0;
		for(t1=1;t1<=Cycle;t1++)
		{
			if(c[t1]!=b[t1]+1)
			{
				Help=1;
			}
			b[t1]=c[t1];
		}
		if(!Help&&DDR)
		{
			DDR=0;
			Help=1;
		}
		else if(!DDR&&Help)
		{
			DDR=1;
		}
	}

	Big=-1;
	for(l1=1;l1<=Cycle;l1++)
	{
		if(b[l1]>Big)
		{
			Big=b[l1];
			Sol=l1;
		}
	}
	Sol+=(unsigned long)Cycle*(m-Big+Dep);
	ofstream fout(o_fnm);
	fout << Str[Sol&1] << " win at " << Sol << endl;
	fout.close();
}

void Do(void)
{
	Dynamic();
}

int main(void)
{
	In();
	Do();

	return 0;
}