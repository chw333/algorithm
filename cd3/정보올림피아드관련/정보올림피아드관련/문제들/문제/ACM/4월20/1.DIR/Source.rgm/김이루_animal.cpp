#include <fstream.h>

int tx,ty;
int table[1005][1005];
int check[1005][1005];
bool cc[1005][1005];



int q[2][100005];
int dab;
int cn;


void Input_Data()
{
	int i,j;
	char d[1003];
	ifstream in ("animal.in");
	{
		in >> tx >> ty;
		for(i=0;i<ty;i++)
		{
			in >> d;
			for(j=0;j<tx;j++)
			{
				if(d[j]=='#')
					check[i][j]=-1;
			}
		}
	}in.close();
	for(i=0;i<ty;i++)
		for(j=0;j<tx;j++)
		{
			if(check[i][j]==0) check[i][j]=1;
			if(check[i][j-1]==-1 && check[i][j] != -1) check[i][j]+=1;
			if(check[i][j+1]==-1 && check[i][j] != -1) check[i][j]+=2;
			if(check[i-1][j]==-1 && check[i][j] != -1) check[i][j]+=4;
			if(check[i+1][j]==-1 && check[i][j] != -1) check[i][j]+=8;
		}
}


void B(int yy,int xx)
{
	int i,j;
	int y[4]={-1,1,0,0};
	int x[4]={0,0,-1,1};


	for(i=0;i<ty;i++)
		for(j=0;j<tx;j++)
		{
			table[i][j]=-1;
		}
	cn=1;
	q[0][0]=yy;
	q[1][0]=xx;
	table[yy][xx]=0;

	for(i=0;;i++)
	{
		if(i>cn) break;
		for(j=0;j<4;j++)
		{
			if(q[0][i]>0 && q[0][i]<ty-1 && q[1][i]>0 && q[1][i]<tx-1 && check[ q[0][i]+y[j] ][ q[1][i]+x[j] ]>0 && table[ q[0][i]+y[j] ][ q[1][i]+x[j] ]==-1)
			{
				table[ q[0][i]+y[j] ][ q[1][i]+x[j] ]=table[q[0][i]][q[1][i]]+1;
				q[0][cn]=q[0][i]+y[j];
				q[1][cn]=q[1][i]+x[j];	
				cn++;
				if(dab<table[ q[0][i]+y[j] ][ q[1][i]+x[j] ]) dab=table[ q[0][i]+y[j] ][ q[1][i]+x[j] ];
			}
		}
	}
}

void Process()
{
	int i,j;
	for(i=0;i<ty;i++)
	{
		for(j=0;j<tx;j++)
		{
			if(check[i][j]==6 || check[i][j]==7 || check[i][j]==8 || check[i][j]==10 || check[i][j]==11 || check[i][j]==12 || check[i][j]==14 || check[i][j]==15)
			{
				B(i,j);
			}
		}
	}
}

void Output_Data()
{
	ofstream out ("animal.out");
	{
		if(dab==0) out << "1";
		else out << dab;
	}out.close();
}


void main()
{
	Input_Data();
	Process();
	Output_Data();
}


