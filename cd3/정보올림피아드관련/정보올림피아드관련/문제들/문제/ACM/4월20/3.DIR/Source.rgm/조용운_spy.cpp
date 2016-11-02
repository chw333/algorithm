#include <stdio.h>
#include <fstream.h>
#include <math.h>

int n;
int ans;

int right(double a,double b,double c,double d) {
	double i;
	double h,w;
	double h1,h2,w1,w2;
	double sinq;
	double radian;
	radian=3.1415926535/180;
	sinq=1;
	for(i=0;i<=45;i+=0.01) {
		h1=c*sin(i*radian)/sinq;
		w1=c*sin((90-i)*radian)/sinq;
		h2=d*sin((90-i)*radian)/sinq;
		w2=d*sin(i*radian)/sinq;
		h=h1+h2;
		w=w1+w2;
		if ((h<a && w<b) || (h<b && w<a)) {
			return 1;
		}
	}
	return 0;
}

void i_f() {
	int i;
	double a,b,c,d;
	ifstream in ("spy.in");
	in >> n;
	for(i=0;i<n;i++) {
		in >> a >> b >> c >> d;
		if (right(a,b,c,d)) ans++;
	}
	in.close();
}

void o_f() {
	ofstream out ("spy.out");
	out << ans << endl;
	out.close();
}

void main() {
	i_f();
	o_f();
}