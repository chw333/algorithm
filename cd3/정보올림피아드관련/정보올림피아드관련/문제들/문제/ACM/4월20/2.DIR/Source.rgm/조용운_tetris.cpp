#include <stdio.h>
#include <fstream.h>

#define N 500

int by,bx;
int fx,fy;
int bl[N][N];
int fl[N][N];
int check[N][N];

void i_f() {
	char a;
	int i,j;
	ifstream in ("tetris.in");
	in >> by >> bx;
	for(i=0;i<by;i++) {
		for(j=0;j<bx;j++) {
			in >> a;
			if (a=='#') bl[i][j]=1;
		}
	}
	in >> fy >> fx;
	for(i=by;i<fy+by;i++) {
		for(j=bx;j<fx+bx;j++) {
			in >> a;
			if (a=='#') fl[i][j]=1;
		}
	}
	in.close();
}

void find() {
}

void pro() {
	find();
}

void o_f() {
	ofstream out ("tetris.out");
	out << "pass" << endl;
	out.close();
}

void main() {
	i_f();
	pro();
	o_f();
}