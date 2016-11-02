#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
int n,c,r,dist[1000],cost[1000],site[1000],table[1000],track[1000];
int mcr,min,dst,cst;

ofstream out("gas.out");

void input(void)
{
	int i,t;

	ifstream in("gas.inp");
	in >> n >> c >> r;
	for(i=1; i<=n; i++){
		in >> t >> dist[i] >> cost[i];
		site[i]=site[i-1]+dist[i];
	}
}

void output(int next)
{
	if(next==0) return;	
	output(track[next]);
	
	cst=table[next]-table[track[next]];
	out << next << ' ' << cst/cost[next] << ' ' << cst << endl;
}

void main(void)
{
	int i,j;

	input();
	mcr=c*r;
	for(i=1; i<=n; i++){
		table[i]=999999999;
		for(j=0; j<=i-1; j++){
			dst=site[i]-site[j];
			if(dst > mcr) continue;
			cst=((dst)/r)*cost[i]+table[j];
			if(cst < table[i]){
				table[i]=cst;
				track[i]=j;
			}
		}
	}			
	if(table[n] == 999999999){out<< "-1" << endl;exit(0);}
	out << table[n] << endl;
	output(n);
}