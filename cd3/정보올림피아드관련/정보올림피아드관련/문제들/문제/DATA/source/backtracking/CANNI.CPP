#include <fstream.h>

ifstream in("canni.in");
ofstream out("canni.out");

char table[11][11][11][11][2];
struct b_ {
	int m;
	int g;
} boat[100];
int n,b;
int bcnt;
int minmove=99999;

void input()
{
	int i, j;
	in >> n >> b;
	for(i=0;i<=b;i++) { //man
		for(j=0;j<=b;j++) { //ghost
			if(i==0 && j==0) continue;
			if((i>=j || i==0) && i+j<=b) {
				boat[bcnt].m=i;
				boat[bcnt].g=j;
				bcnt++;
			}
		}
	}
}
void output()
{
	if(minmove==99999) out << "impossible"; else out << minmove-1;
}
void move(int lm, int lg, int rm, int rg, int bt, int cnt)
{
	int i;
	if(lm<0 || lg<0 || rm <0 || rg <0 || lm >n || lg >n || rm >n || rg >n) return;
	if(table[lm][lg][rm][rg][bt]!=0) return;
	if(lm==0 && lg==0 && rm==n && rg==n && bt==1) {
		if(minmove>cnt) minmove=cnt;
		return;
	}
	table[lm][lg][rm][rg][bt]=cnt;
	for(i=0;i<bcnt;i++) {
		if(bt==0) move(lm-boat[i].m, lg-boat[i].g, rm+boat[i].m, rg+boat[i].g, 1, cnt+1);
		else move(lm+boat[i].m, lg+boat[i].g, rm-boat[i].m, rg-boat[i].g, 0, cnt+1);
	}
	table[lm][lg][rm][rg][bt]=0;
}
void proc()
{
	move(n,n,0,0,0,1);
}
void main()
{
	input();
	proc();
	output();
}