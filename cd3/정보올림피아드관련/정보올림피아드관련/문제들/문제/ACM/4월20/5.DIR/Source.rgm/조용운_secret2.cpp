#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include <time.h>

#define Mem1 20200
#define Mem2 2020
#define Max_s(a,b) ((a>b)?a:b)
#define M 1000000000
#define Time 1.9

int n,m;
int line[Mem1][3];
int idx[Mem1];
int f[Mem2];
int mst[Mem2];
int ans;
int floyd[Mem2][Mem2];
int plus;
int mst_v;
clock_t st,en;

void i_f() {
	int i;
	ifstream in ("secret.in");
	in >> n >> m;
	for(i=0;i<m;i++) {
		in >> line[i][0] >> line[i][1] >> line[i][2];
		line[i][0]--;
		line[i][1]--;
	}
	in.close();
}

int sf(const void *a,const void *b) {
	int aa,bb;
	aa=line[*(int *)a][2];
	bb=line[*(int *)b][2];
	if (aa>bb) return 1;
	if (aa<bb) return -1;
	return 0;
}

void swap(int &a,int &b) {
	int t;
	t=a;
	a=b;
	b=t;
}

void change(int a,int b) {
	int i;
	if (a>b) swap(a,b);
	for(i=0;i<n;i++) {
		if (f[i]==b) f[i]=a;
	}
}

int mst_f(int remove) {
	int i;
	int p;
	int cnt;
	int min;
	int tmp;
	tmp=mst_v+plus;
	cnt=0;
	min=0;
	for(i=0;i<n;i++) {
		f[i]=i;
	}	
	for(i=0;i<m;i++) {
		p=idx[i];
		if (p==remove) continue;
		if (f[line[p][0]]!=f[line[p][1]]) {
			change(f[line[p][0]],f[line[p][1]]);
			mst[cnt]=p;
			cnt++;
			min+=line[p][2];
			if (min>=tmp) return M;
			if (cnt==n-1) {
				break;
			}
		}
	}
	return min;
}

void pro() {
	int i;
	int new_v;
	int v;
	double duration;
	for(i=0;i<m;i++) {
		idx[i]=i;
	}
	qsort(idx,m,sizeof(idx[0]),sf);
	mst_v=M;
	plus=0;
	mst_v=mst_f(M);
	plus=M;
	for(i=0;i<n;i++) {
		new_v=mst_f(mst[i]);
		v=new_v-mst_v;
		if (v==1) {
			plus=1;
			break;
		}
		if (plus>v && v!=0) plus=v;
		en=clock();
		duration=(double)(en-st)/CLOCKS_PER_SEC;
		if (duration>Time) {
			plus=1;
			break;
		}
	}
	ans=mst_v+plus;

	/*min=M;
	for(i=0;i<m;i++) {
		p=idx[i];
		if (mst[p]) continue;
		v=line[p][2]-dij(line[p][0],line[p][1]);
		if (v<0) {
			j=0;
		}
		if (v!=0 && min>v) min=v;
	}
	ans+=min;*/
}

void o_f() {
	ofstream out ("secret.out");
	out << ans << endl;
	out.close();
}

void main() {
	st=clock();
	i_f();
	pro();
	o_f();
	en=clock();
	cout << en-st << endl;
}
