#include <fstream.h>

#define maxN 1100
int m[2]; // 두개의 공장
int n;    // 기계의 개수
int ability[2][maxN]; // 두개의 공장에서 각 기계의 분당 처리 능력
int table[2][10000];	// 두개의 공장에서 시간당 처리되는 일의 양
int ans[2]; // 0-첫번째 공장의 일이 종료되는 시각, 1-두번째 공장의 일이 종료되는 시각

ifstream in ("job.in");
ofstream out ("job.out");
int job(int sw)
{
	int t,j,i;
	int jn=n; // 처리해야할 일
	int temp[10000];
	for(t=1;;t++){
		for(j=0;j<m[sw];j++){
			if((t%ability[sw][j])==0) {
				jn--; 
			    table[sw][t]++;
				if(jn<=0) {
					if(sw==1) {
						for(i=t;i>=1;i--) temp[t-i+1]=table[sw][i];
						for(i=1;i<=t;i++) table[sw][i]=temp[i];
					}
					return t;
				}
			}
		}
	}
}
void input()
{
	int i,j;

	in >> n >> m[0] >> m[1];
	for(i=0;i<2;i++) {
		for(j=0;j<m[i];j++) {
			in >> ability[i][j];
		}
	}
	in.close();
}
void output()
{
	out << ans[0] << " " << ans[1] << endl;
	out.close();
}
void proc()
{
	int i,t0=1,t1=1,temp[2],redun=0, delay=1;
	for(i=0;i<2;i++) temp[i]=job(i);
	ans[0]=temp[0];
	for(;;){
		if(table[0][t0]+redun>=table[1][t1]) {
			redun=table[0][t0]+redun-table[1][t1];
			t0++; t1++;
		} else {
			redun=table[0][t0]+redun;
			t0++;
			delay++;
		}
		if(t1>temp[1]) break;
	}
	ans[1]=temp[1]+delay;
}
void main()
{
	input();
	proc();
	output();
}
