#include <fstream.h>

ifstream in ("animal.in");
ofstream out("animal.out");

static int c,r,box[1005][1005],cnt,max,qiz;
static int check[1005][1005];
static int point[1005][1005];


void ch(int y,int x,int anycnt)
{
		if(box[y+1][x]==0)
	{
		if(check[y+1][x]<anycnt)
		{

			check[y+1][x]=anycnt;
		}
		if(point[y+1][x]!=-1)
		{
			point[y+1][x]=anycnt;
		}

	}
	if(box[y-1][x]==0)
	{
		if(check[y-1][x]<anycnt)
		{

			check[y-1][x]=anycnt;
		}
		if(point[y-1][x]!=-1)
		{
			point[y-1][x]=anycnt;
		}
	}
	if(box[y][x+1]==0)
	{
		if(check[y][x+1]<anycnt)
		{

			check[y][x+1]=anycnt;
		}
		if(point[y][x+1]!=-1)
		{
			point[y][x+1]=anycnt;
		}
	}
	if(box[y][x-1]==0)
	{
		if(check[y][x-1]<anycnt)
		{

			check[y][x-1]=anycnt;
		}
				if(point[y][x-1]!=-1)
		{
			point[y][x-1]=anycnt;
		}
	}
}
void bfs(int anycnt)
{
	int i,j;
	int pz;
	pz=0;
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			if(point[i][j]==anycnt-1 && box[i][j]==0)
			{
				pz=1;
				point[i][j]=-1;
				ch(i,j,anycnt);
			}
		}
	}
	if(pz==0)
	{
		return;
	}
	bfs(anycnt+1);
}
	
void main(void)
{
	static int i,j,z,x;
	static char a;

	in >> c >> r;

	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			in >> a;
			if(a=='#')
			{
				box[i][j]=1;
			}
			else { box[i][j]=0; cnt++; }
		}
	}

	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			if(box[i][j]==0)
			{
				point[i][j]=1;
				qiz++;
				bfs(2);

				for(z=1;z<=r;z++)
				{
					for(x=1;x<=c;x++)
					{
						point[z][x]=0;
					}
				}
			}
		}
	}
	max=0;
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			if(check[i][j]>max)
			{
				max=check[i][j];
			}
		}
	}
	if(max>0){
		out << max-2;
	}
	else { out << 0;}
}