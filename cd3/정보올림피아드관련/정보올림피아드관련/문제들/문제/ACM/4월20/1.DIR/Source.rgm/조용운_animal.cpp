#include <stdio.h>
#include <fstream.h>

#define N 300

int n;
int x,y;
int q[N][N];
int cnt;
int ans;

void i_f() {
	int i,j;
	char a;
	ifstream in ("animal.in");
	in >> x >> y;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			in >> a;
			if (a=='.') cnt++;
			else q[i][j]=1;
		}
	}
	in.close();
}

void pro() {
}

void o_f() {
	ofstream out ("animal.out");
	ans=(x+y+cnt)/3+1;
	out << ans << endl;
	out.close();	
}

void main() {
	i_f();
	pro();
	o_f();
}
