#include<fstream.h>
//#include<conio.h>
int xx,yy,cnt,p[1000][1000],bs[1000][1000],visit[1000][1000],max;
void init()
{
	int i,j;
	char a[1000];
	ifstream in ("animal.in");
	in >> xx >> yy;
	for(i=0;i<yy;i++){
		in >> a;
		for(j=0;j<xx;j++){
			if(a[j]=='#')
				p[j][i]=-1;
			else
				p[j][i]=0;
		}
	}
	in.close();
}
void outt()
{
	int i,j;
	for(i=0;i<xx;i++){
		for(j=0;j<yy;j++)
			if(p[i][j]==-1)
				cout << p[i][j];
			else
				cout << " " << p[i][j];
		cout << endl;
	}
	cout << endl << endl;
//	getch();
}
void ff(int x, int y)
{
	int f=0;
	visit[x][y]=1;
	cnt++;
	if(p[x+1][y]!=-1 && visit[x+1][y]==0 && x<xx-1){
		f=1;
		ff(x+1,y);
	}
	if(p[x-1][y]!=-1 && visit[x-1][y]==0 && x>0){
		f=1;
		ff(x-1,y);
	}
	if(p[x][y+1]!=-1 && visit[x][y+1]==0 && y<yy-1){
		f=1;
		ff(x,y+1);
	}
	if(p[x][y-1]!=-1 && visit[x][y-1]==0 && y>0){
		f=1;
		ff(x,y-1);
	}
	if(f==0 && cnt>max)
		max=cnt;
	visit[x][y]=0;
	cnt--;
}
void animal()
{
	int i,j,f=0;
	for(i=0;i<xx;i++)
		for(j=0;j<yy;j++)
			if(p[i][j]==0){
				max=0;
				ff(i,j);
				bs[i+1][j]=bs[i-1][j]=bs[i][j+1]=bs[i][j-1]=0;
				p[i][j]=max-1;
			}
}
void output()
{
	int i,j,max=0;
	ofstream out ("animal.out");
	for(i=0;i<xx;i++)
		for(j=0;j<yy;j++)
			if(p[i][j]>max)
				max=p[i][j];
	out << max;
	out.close();
}
void main()
{
	init();
	animal();
	output();
}