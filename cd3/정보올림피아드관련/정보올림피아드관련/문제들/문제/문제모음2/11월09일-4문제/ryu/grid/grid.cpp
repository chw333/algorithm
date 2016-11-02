#include <fstream.h>
#include <math.h>
#include <iomanip.h>
#include <conio.h>

#define Mx 10
#define Nx 150
#define Kx 59049

ifstream in ("grid.in");
ofstream out("grid.out");

int T, M, N, K, NN, R;
int B[Mx][Nx];
int BT[Mx][3];
int D[2][Kx];

void input()
{
	int i, j, a, b, k;
	in>>N>>M>>k;
	R=0;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			B[i][j]=0;
		}
	}
	for(i=0; i<k; i++){
		in>>a>>b;
		B[b-1][a-1]=1;
	}
}

int isok(int m, int type)
{
	int i, j, l, c;
	if(type){ // ver
		l=3; c=2;
	}else{    // hor
		l=2; c=3;
	}
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			if((m+i)>=M || BT[m+i][2-j]) {
				return 0;
			}
		}
	}
	return 1;
}

void putorget(int m, int type, int gab)
{
	int i, j, l, c;
	if(type){ // ver
		l=3; c=2;
	}else{    // hor
		l=2; c=3;
	}
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			BT[m+i][2-j]=gab;
		}
	}
}
/*
void display(int p, int n, int prev)
{
	int i, j;
	cout << "N->" << NN << "   PC->" << p << "   NC->" << n << endl;
	cout << "PreK->" << prev << "   NowK->" << K << endl;

	for(i=0; i<M; i++){
		for(j=0; j<3; j++){
			cout<<setw(3)<<BT[i][j];
		}
		cout << endl;
	}
	cout << endl;

	for(i=0;i<pow(3,M); i++){
		cout << "Dpre " << setw(2) << i << "->" << D[(NN-1)%2][i] << endl;
	}
	for(i=0;i<pow(3,M); i++){
		cout << "Dnow " << setw(2) << i << "->" << D[NN%2][i] << endl;
	}
	getch();
}
*/
void Dynamic(int cnt)
{
	int i, t, prev=0;
	for(i=0; i<M; i++){
		t=0;
		if(BT[i][1]>1){
			t++;
			if(BT[i][0]>1){
				t++;
			}
		}
		prev+=pow(3,i)*t;
	}
	t=D[(NN-1)%2][prev]+cnt;
	if(D[NN%2][K]<t){
		D[NN%2][K]=t;
		if(R<t) {
			R=t;
		}
	}
//	display(t-cnt, cnt, prev);
}

void recur(int m, int cnt)
{
	if(m>=M-1) {
		Dynamic(cnt);
	} else {
		if(isok(m, 0)){ //hor
			putorget(m, 0, 2);
			recur(m+2, cnt+1);
			putorget(m, 0, 0);
		} 
		if(isok(m, 1)){ //ver
			putorget(m, 1, 2);
			recur(m+3, cnt+1);
			putorget(m, 1, 0);
		}
		recur(m+1, cnt);
	}
}

void process()
{
	int i, j, k, l, m, gab=pow(3,M);
	for(i=0; i<gab; i++) {
		D[0][i]=D[1][i]=0;
	}
	for(i=1; i<N; i++){
		for(j=0; j<gab; j++) {
			D[i%2][j]=0;
		}		
		for(j=0; j<gab; j++){
			for(k=0; k<M; k++){
				for(l=0; l<3; l++){
					if(i-2+l<0) BT[k][l]=1;
					else BT[k][l]=B[k][i-2+l];
				}
			}	
			m=0;
			k=j;
			while(k>0){
				if(k%3==1){
					BT[m][2]=3;
				} else if(k%3==2) {
					BT[m][2]=3;
					BT[m][1]=3;
				}
				k=k/3;
				m++;
			}
			K=j;
			NN=i;
			recur(0, 0);
		}
//		cout << i << endl;
	}
}

void output()
{
	out<<R;
}

void main()
{
	int i;
	in>>T;
	for(i=0; i<T; i++){
		if(i!=0) out<<endl;
		input();
		process();
		output();
	}
}