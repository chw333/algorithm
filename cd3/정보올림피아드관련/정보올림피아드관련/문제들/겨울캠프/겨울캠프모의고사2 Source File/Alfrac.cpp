#include<fstream.h>

#define FILEIN "ALFRAC.INP"
#define FILEOUT "ALFRAC.OUT"

const short MAX=27;
const short MAXC=27;

short F;
char f[MAX][MAXC];
short fs[MAX],fl[MAX];

char x[MAXC];
bool xt[MAXC];
short xk[MAXC];
short xs,xl;

void input()
{
	short i;
	char buf[256];
	ifstream fp(FILEIN);
	F=0;
	for(fp>>buf;buf[0]!='#';F++)
	{
		for(i=0;buf[i]!='/';i++)
			f[F][i]=buf[i];
		fs[F]=i;
		for(i++;buf[i];i++)
			f[F][i-1]=buf[i];
		fl[F]=i-1;
		fp>>buf;
	}
}

void prepare(short k)
{
	short i,j;
	xs=fs[k];
	xl=fl[k];
	for(i=0;i<xs;i++)
	{
		x[i]=f[k][i];
		xt[i]=true;
		xk[i]=0;
	}
	for(;i<xl;i++)
	{
		x[i]=f[k][i];
		xt[i]=false;
		xk[i]=0;
	}
	
	for(i=1;i<xl;i++)
		for(j=i;j>0 && x[j-1]>x[j];j--)
		{
			char temp=x[j];
			x[j]=x[j-1];
			x[j-1]=temp;
			bool temp2=xt[j];
			xt[j]=xt[j-1];
			xt[j-1]=temp2;
		}
}

bool core()
{
	short i,j,k=1;
	if(xt[0]!=true || xt[1]!=false)
		return false;
	xk[0]=xk[1]=0;
	for(i=2;i<xl;i++)
	{
		if(xt[i]==true)
		{
			for(j=i-1;j>0;j--)
				if(xt[j]==false)
					break;
			if(xk[j]<0)
			{
				xk[i]=xk[j]-1;
				xk[j]=1;
			}
			else
			{
				xk[j]++;
				xk[i]=-1;
			}
		}
		else
		{
			xk[0]++;
			xk[i-1]--;
		}
	}
	xk[0]++;
	xk[xl-1]--;
	return true;
}

ofstream fp(FILEOUT);

void output()
{
	short i,j,k=0;
	for(j=xk[0];j>0;j--)
		fp<<'(';
	fp<<x[0];
	for(i=1;i<xl;i++)
	{
		fp<<'/';
		if(xk[i]>0)
		{
			for(j=xk[i];j>0;j--)
				fp<<'(';
			fp<<x[i];
		}
		else if(xk[i]<0)
		{
			fp<<x[i];
			for(j=xk[i];j<0;j++)
				fp<<')';
		}
		k+=xk[i];
	}
	fp<<endl;
}

void main()
{
	input();
	for(short i=0;i<F;i++)
	{
		prepare(i);
		if(core())
			output();
		else
			fp<<"None"<<endl;
	}
}
