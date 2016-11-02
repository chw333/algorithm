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
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			out << (int)da[i][j] << " ";
		}
		out << endl;
	}
}

void fordfulkerson()
{
    int i,from,to;
    do
    {
        findpath();
        if(path[201]==0) break;
        i=201;
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
        for(i=1;i<=n*n*2;i++)
        {
            if(da[i][q[d]]==1 && ch[i]==0)
            {
                ch[i]=1; l++; q[l]=i;
            }
        }
        if(da[q[d]][201]==1) ans++;
    } while (d<l);
}

void findpath()
{
    int i,d,l;
    int q[202]={0,},ch[202]={0,};
    l=1; d=0; q[1]=0; ch[0]=1; path[201]=0;
    do
    {
        d++;
        for(i=1;i<=n*n*2;i++)
        {
            if(da[q[d]][i]==1 && ch[i]==0)
            {
                ch[i]=1; path[i]=q[d];
                l++; q[l]=i;
            }
        }
        if(da[q[d]][201]==1 && ch[201]==0)
        {
            ch[201]=1; path[201]=q[d];
            break;
        }
    } while (d<l);
}

void output()
{
    if(ans==m) {out<<1;} else {out<<0;}
}

void main()
{
    inputdata();
    fordfulkerson();
    output();
}
