#include <stdio.h>
#include <fstream.h>

#define N 100

int n;
int acr1[N];// ¢Ù
int acr2[N];// ¢×
int hr[N];
int ans;

void i_f() {
	ifstream in ("nqueen.in");
	in >> n;
	in.close();
}

void pro(int p) {
	int i;
	int ar1,ar2;
	if (p==n) {
		ans++;
		return;
	}
	for(i=0;i<n;i++) {
		ar1=i-p+n-1;
		ar2=i+p;
		if (hr[i]==0 && acr1[ar1]==0 && acr2[ar2]==0) {
			hr[i]=1;
			acr1[ar1]=1;
			acr2[ar2]=1;
			pro(p+1);
			hr[i]=0;
			acr1[ar1]=0;
			acr2[ar2]=0;
		}
	}
}

void o_f() {
	ofstream out ("nqueen.out");
	out << ans << endl;
	out.close();
}

void main() {
	i_f();
	pro(0);
	o_f();
}
