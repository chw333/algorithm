#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 

ifstream in ("npolpath.in");
ofstream out("npolpath.out");          

#define Nx  40

int N, S, T, M;
struct BUF {
	char last;
	char b[Nx];
	struct BUF *prev;
	struct BUF *next;
} FHead, FTail;

void input()
{
	struct BUF *b;
	in>>N>>S>>T;
//	N=8; S=1; T=4;
	b=(struct BUF *)calloc(1, sizeof(struct BUF));
	M++;
	b->last=S;
	b->b[S]=1;
	b->prev=&FHead;
	b->next=&FTail;
  	FHead.next=b;
	FTail.prev=b;
}

int push(struct BUF *b, int sw, int num)
{
	int i, j, k, br[3], flag=0, ftmp;
	struct BUF *t, *next;
	br[0]=b->last-1; if(br[0]<0) br[0]=N-1;
	br[1]=b->last+1; if(br[1]>N-1) br[1]=0;
	br[2]=b->last+N/2; if(br[2]>N-1) br[2]-=N;
	for(i=0; i<3; i++){
		j=br[i];
		if(j==S || (!sw && j==T)) continue;
		if(!b->b[j]){
			if(flag!=0){
				t=(struct BUF *)malloc(sizeof(struct BUF));
				M++;
				t->last=j;
				memcpy(t->b, b->b, N);
				t->b[j]=num;
				next=FHead.next;
				next->prev=t;
				FHead.next=t;
				t->prev=&FHead;
				t->next=next;
			} else {
				flag=1;
				ftmp=j;
				continue;
			}
		}
	}	
	if(flag){
		b->last=ftmp;
		b->b[ftmp]=num;
	}
	return flag;
}

void del(struct BUF *b)
{
	struct BUF *p, *n;
	p=b->prev; n=b->next;
	p->next=n;
	n->prev=p;
	free(b);
	M--;
}

void process()
{
	int num=1, sw=0;
	struct BUF *b, *t;
	while(num<N){
		b=FHead.next;
		if(num==N-1)sw=1;
		num++;
		while(b!=&FTail){
			t=b->next;
			if(!push(b,sw,num)) del(b);
			b=t;
		}
//		cout << num << " " << M << endl;        
	}
}

int cmp(char *a, char *b)
{
	int i;
	for(i=0; i<N; i++){
		if(a[i]==b[i]) continue;
		else if(a[i]>b[i]) return 1;
		return -1;
	}
	return 0;
}

void output()
{
	int i, j, mini, idx=0;
	struct BUF *b=FHead.next;
	char p[1000][Nx], *min;
	while(b!=&FTail){
		for(i=0; i<N; i++) p[idx][b->b[i]-1]=i;
		b=b->next;
		idx++;
	}
/*
	for(i=0; i<idx; i++){
		for(j=0; j<N; j++){
			cout << (int) p[i][j] << " ";
		}
		cout << endl;
		getch();
	}
*/
	min=p[0]; mini=0;
	for(i=1; i<idx; i++){
		if(cmp(p[i], min) < 0) {
			min=p[i];
			mini=i;
		}
	}
	if(idx==0) out << "-1";
	else {
		for(i=0; i<N; i++){
			if(i!=0) out << " ";
			out << (int)min[i];
		}		
	}
}

void main()
{
	input();
	process();
	output();
}