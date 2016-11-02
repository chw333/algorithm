#include <stdio.h>
#include <conio.h>
#include <fstream.h>

void inputdata();
void fordfulkerson();
void findpath();
void output();
int n, m, ans;
char da[202][202];
int path[202];

ifstream in("piramid.in");
ofstream out("piramid.out");

/*
void inputdata()
{
    int i, j, a, d;
    in>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            d=((i-1)*n+j)*2-1;
            da[d][d+1]=1;
            if(j>1) da[d-1][d]=1;
            if(j<n) da[d+3][d]=1;
            if(i>1) da[d-n*2+1][d]=1;
            if(i<n) da[d+n*2+1][d]=1;
            in>>a;
            if(a==1) da[0][d]=1;
            if(i==1 || i==n || j==1 || j==n) da[d+1][201]=1;
        }
    }
}
*/
void init()
{
    int i, j, d, man, up, down, left, right;
    in >> n >> m;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
			d=i*n+j+1;
			left=d+1;
			right=d-1;
			up=(i-1)*n+j+1;
			down=(i+1)*n+j+1;
			if(i>0) da[d][up]=1;
			if(i<n-1) da[d][down]=1;
			if(j>0) da[d][left]=1;
			if(j<n-1) da[d][right]=1;
            in >> man;
            if(man==1) da[0][d]=1; //from start point
            if(i==0 || i==n-1 || j==0 || j==n-1) da[d][n*n+1]=1; // to end point
        }
    }
}

void fordfulkerson()
{
    int i,from,to;
    do
    {
        findpath();
        if(path[n*n+1]==0) break;
        i=n*n+1;
        do
        {
            from=path[i];
            to=i;
            da[from][to]=0;
            da[to][from]=1;
            i=from;
        } while (i!=0);
    } while (1);

    int d,l;
    int q[202]={0,},ch[202]={0,};
    l=1; d=0; q[l]=0; ch[0]=1;
    ans=0;
    do
    {
        d++;
        for(i=0;i<=n*n+1;i++)
        {
            if(da[i][q[d]]==1 && ch[i]==0)
            {
                ch[i]=1; l++; q[l]=i;
            }
        }
        if(da[q[d]][n*n+1]==1) ans++;
    } while (d<l);
}

void findpath()
{
    int i,d,l;
    int q[202]={0,},ch[202]={0,};
    l=1; d=0; q[1]=0; ch[0]=1; path[n*n+1]=0;
    do
    {
        d++;
        for(i=0;i<=n*n+1;i++)
        {
            if(da[q[d]][i]==1 && ch[i]==0)
            {
                ch[i]=1; path[i]=q[d];
                l++; q[l]=i;
            }
        }
        if(da[q[d]][n*n+1]==1 && ch[n*n+1]==0)
        {
            ch[n*n+1]=1; path[n*n+1]=q[d];
            break;
        }
    } while (d<l);
}

void output()
{
	out << ans;
    //if(ans==m) {out<<1;} else {out<<0;}
}

void main()
{
    //inputdata();
	init();
    fordfulkerson();
    output();
}
