#include <fstream.h>
#include <stdlib.h>
ifstream in("map.in");
ofstream out("map.out");

int table[26][26];
int mapcnt[1000];
int n;
int gnum=1;

int sf(const void *p, const void *q)
{
	int *a=(int *)p;
	int *b=(int *)q;

	return (*a>*b);
}

void inp()
{
	int i,j;

	in >> n;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			in >> table[i][j];
}
void oup()
{
	int i;
	out << gnum-1 << endl;
	qsort(&mapcnt[1],gnum-1,sizeof(mapcnt[0]),sf);
	for(i=1;i<=gnum-1;i++)
		out << mapcnt[i] << endl;
}
void find(int y, int x, int num)
{
	int i,j;

	if(y<0 || x <0 || y>=n || x>=n) return;
	if(table[y][x]==1) {
		mapcnt[num]++;
		table[y][x]=num+1;
		find(y,x+1,num);
		find(y,x-1,num);
		find(y+1,x,num);
		find(y-1,x,num);
	}
}
void proc()
{
	int i, j;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			if(table[i][j]==1) {
				find(i,j,gnum);
				gnum++;
			}
		}
	}
}
void main()
{
	inp();
	proc();
	oup();
}