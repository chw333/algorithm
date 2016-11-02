#include <fstream.h>
#include <string.h>

ifstream in("round4.in");
ofstream out("round4.out");

int map[101];
char dir[101];
int data[101][2];
int n;
int result=99999;

void input()
{
	int i,j;

	in >> n;
	for(i=0;i<n;i++)
		for(j=0;j<2;j++)
			in >> data[i][j];
}
void proc(int s, int e, int cnt, int max, int mp[101])
{
	int i;
	int tmap1[101]={0,};
	int tmap2[101]={0,};

	if(cnt>=n) {
		if(result>max) result=max;
		return ;
	}
	memmove(tmap1,mp,sizeof(tmap1));
	if(s<=e) {
		for(i=s;i<=e;i++) {
			tmap1[i]++;
			if(tmap1[i]>=result) return;
			if(max<tmap1[i]) max=tmap1[i];
		}
		dir[cnt]='g';
	} else {
		i=s;
		while(i!=e) {
			if(i>100) i=1;
			tmap1[i]++;
			if(tmap1[i]>=result) return;
			if(max<tmap1[i]) max=tmap1[i];
			i++;
		}
		tmap1[i]++;
		if(tmap1[i]>=result) return;
		if(max<tmap1[i]) max=tmap1[i];
		dir[cnt]='b';
	}
	memmove(tmap2,tmap1,sizeof(tmap1));
	proc(data[cnt+1][0],data[cnt+1][1],cnt+1,max,tmap1); // go
	proc(data[cnt+1][1],data[cnt+1][0],cnt+1,max,tmap2); // back
}
void output()
{
	int i;
	out << result << endl;
	for(i=0;i<n;i++) {
		if(dir[i]=='g')
			out << data[i][0] <<" "<< data[i][1]<< " : C " << endl;
		else 
			out << data[i][0] <<" "<< data[i][1]<< " : CC " << endl;
	}
}
void main()
{
	input();
	proc(data[0][0],data[0][1],0,0,map);
	output();
}