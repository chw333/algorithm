#include <fstream.h>

ifstream in("hamil.in");
ofstream out("hamil.out");

int visit[13];
int table[13][13];
int mincost=99999,n,cost;

void inp()
{
	int i, j;
	in >> n;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			in >> table[i][j];
}
void oup()
{
	out << mincost;
}
void tour(int s, int cnt, int cost)
{
	int i,j;

	if(s==0 && visit[s] && cnt==n) {
		if(cost<mincost) mincost=cost;
		return;
	}
	if(cnt>=n) return;
	if(visit[s]) return;
	visit[s]=1;
	for(i=0;i<n;i++) {
		if(s!=i && table[s][i]) {
			tour(i,cnt+1,cost+table[s][i]);
		}
	}
	visit[s]=0;
}
void proc()
{
	tour(0,0,0);
}
void main()
{
	inp();
	proc();
	oup();
}
