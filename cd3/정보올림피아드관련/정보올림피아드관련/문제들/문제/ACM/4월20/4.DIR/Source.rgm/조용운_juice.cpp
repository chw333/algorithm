#include <stdio.h>
#include <fstream.h>

#define Num 1000
#define Mum 1000000
#define M 2000000000

int n,m;
int q[Num][2]; //v w
int d[Mum];
//int nr[Mum];

void i_f() {
	int i;
	int a,b;
	ifstream in ("juice.in");
	in >> a >> b;
	m=b-a;
	in >> n;
	for(i=0;i<n;i++) {
		in >> q[i][0] >> q[i][1];
	}
	in.close();
}

void pro() {
	int i,j;
	int v;
	d[0]=0;
	for(i=1;i<=m;i++) {
		d[i]=M;
	}
	for(i=0;i<n;i++) {
		for(j=q[i][1];j<=m;j++) {
			v=d[j-q[i][1]]+q[i][0];
			if (v<d[j]) {
				d[j]=v;
//				nr[j]=i;
			}
		}
	}
	/*v=m;
	for(;;) {
		cout << nr[v] << endl;
		v-=q[nr[v]][1];
		if (v==0) break;
	}*/
}

void o_f() {
	ofstream out ("juice.out");
	if (d[m]==M) out << "impossible";
	else out << d[m];
	out << endl;
	out.close();
}

void main() {
	i_f();
	pro();
	o_f();
}