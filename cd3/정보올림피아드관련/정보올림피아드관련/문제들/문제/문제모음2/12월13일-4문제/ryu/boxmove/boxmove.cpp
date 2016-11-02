#include <fstream.h>
#include <string.h>
#include <math.h>

#define Nx 7
#define Ax 4782969
ifstream in ("boxmove05.in");
ofstream out("boxmove05.out");

int N, Q[Ax], Qs, Qe, Min, Count, MaxCount;
char B[2*Nx+1],S[Ax];

void get_s(char *p, int g)
{
	int i, t, gg=g;
	for(i=N*2-1; i>=0; i--){
		t=pow(3,i);
		if(gg>=2*t){
			gg-=2*t;
			p[i]='X';
		}else if(gg>=t){
			gg-=t;
			p[i]='O';
		}else{
			p[i]='.';
		}
	}
}

int get_i(char *b)
{
	int i, g=0, t;
	for(i=0; i<N*2; i++){
		switch(b[i]) {
			case '.': t=0; break;
			case 'O': t=1; break;
			case 'X': t=2; break;
		}
		g+=t*pow(3,i);
	}
	return g;
}

int is_final(char *p)
{
	int i, o=0, x=0;
	for(i=0; i<2*N; i++){
		if(p[i]=='O') o++;
		else if(p[i]=='X') x++;
		if(o==N-1) break;
	}
	if(x) return 0;
	else return 1;
}

int input()
{
	int tmp;
	in>>N;
	in.getline(B,2*N+1);
	in.getline(B,2*N+1);
	tmp=get_i(B);
	if(is_final(B)) return 1;
	else {
		S[tmp]=++Min;
		Q[Qe++]=tmp;
		Count ++;
		return 0;
	}
}

void output()
{
	if(Ax<=MaxCount)cout << "Error\n";
	cout<<MaxCount;
    out << Min;
}

int moving(char *p, int s)
{
	int i, bp;
	for(i=0; i<2*N-1; i++) {
		if(p[i]=='.') { bp=i;	break; }
	}
	if(bp-1<=s && s<=bp+1) return 0;
	p[bp]=p[s];     p[s]='.';
	p[bp+1]=p[s+1]; p[s+1]='.';
	return 1;
}

int bfs(int min)
{
	int i, tmp;
	char t1[2*Nx], t2[2*Nx];
	while(S[Q[Qs]]==min){
		get_s(t1, Q[Qs++]);
		if(Qs==Ax) Qs=0;
		Count --;
		for(i=0; i<2*N-1; i++){
			memcpy(t2, t1, 2*N);
			tmp=moving(t2, i);
			if(tmp){
				tmp=get_i(t2);
				if(!S[tmp]){
					if(is_final(t2)) {
						return 1;
					}
					S[tmp]=min+1;
					Q[Qe++]=tmp;
					if(Qe==Ax) Qe=0;
					Count ++;
					if(MaxCount<Count)MaxCount=Count;
				}
			}
		}
	}
	return 0;
}

void process()
{
	int ret=0;
	while(1) {
		ret=bfs(Min);
		if(ret) break;
		Min++;		
	}
}

void main()
{
	if(!input()) process();
	output();
}