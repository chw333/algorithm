#include <stdio.h>
#include <fstream.h>

#define N 50

int n;
double q[N][2];
double xy[2];
int ans;

void i_f() {
	int i;
	ifstream in ("inside.in");
	in >> n;
	for(i=0;i<n;i++) {
		in >> q[i][0] >> q[i][1];
	}
	in >> xy[0] >> xy[1];
	in.close();
}

double ccw(int p1,int p2) {
	double a,b,c,d;
	double ccw_v;
	a=q[p2][0]-q[p1][0];
	b=q[p2][1]-q[p1][1];
	c=xy[0]-q[p1][0];
	d=xy[1]-q[p1][1];
	ccw_v=a*d-b*c;
	return ccw_v;
}

int right(int a,int b,int c) {
	double ccw_a,ccw_b,ccw_c;
	ccw_a=ccw(a,b);
	ccw_b=ccw(b,c);
	ccw_c=ccw(c,a);
	if ((ccw_a<0 && ccw_b<0 && ccw_c<0) || (ccw_a>0 && ccw_b>0 && ccw_c>0)) return 1;
	return 0;
}

void pro() {
	int i,j,k;
	for(i=0;i<n;i++) {
		for(j=i+1;j<n;j++) {
			for(k=j+1;k<n;k++) {
				if (right(i,j,k)) ans++;
			}
		}
	}
}

void o_f() {
	ofstream out ("inside.out");
	out << ans << endl;
	out.close();
}

void main() {
	i_f();
	pro();
	o_f();
}