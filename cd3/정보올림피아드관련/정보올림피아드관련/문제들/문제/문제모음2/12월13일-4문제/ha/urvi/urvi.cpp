#include <fstream.h>
#include <conio.h>

#define MAX 202

void inputdata(void);
void process(void);
void outputdata(void);
void roll(int );

int head;
int n;
int m[MAX], v[MAX];
int ns[MAX], s[MAX][MAX];
int rn, rd[MAX];
int answer;

void inputdata(void)
{
	int q,w,e;


	ifstream in("urvi00.in");
	in>>n;
	for (q=1;q<=n;q++){
		in>>m[q]>>v[q];
		w=m[q];
		ns[w]++;
		s[w][ns[w]]=q;
		if (m[q]==0) head=q;
	}
}

void main(void)
{
	inputdata();
	roll(head);
	answer=rd[n/2];
	outputdata();
}

void outputdata(void)
{
	int q,w,e;
	ofstream out("urvi.out");
	out<<answer<<endl;
}

void roll(int where)
{
	int q,w,e;
	int dn=1, d[MAX], d2[MAX];
	int son, sv;
	
	if (ns[where]==0) {
		rn=1; 
		rd[0]=0;
		return;
	}
	d[0]=0;
	for (q=1;q<=ns[where];q++){
		son=s[where][q]; sv=v[son];
		roll(son);

		//계산되어 나올 d2배열을 초기화한다. 
		for (w=0;w<dn;w++) d2[w]=d[w];
		for (w=dn;w<dn+rn;w++) d2[w]=-1;

		//정 방향으로 붙이기(자식과 자신을 같은 색깔로)
		for (w=0;w<rn;w++){
			for (e=0;e<dn;e++){
				if (d2[e+w]<rd[w]+d[e]) {
					d2[e+w]=rd[w]+d[e];					
				}
			}
		}

		//역 방향으로 붙이기(자식과 자신을 다른 색깔로)
		for (w=0;w<rn;w++){
			for (e=0;e<dn;e++){
				if (rn-w+e<0||rn-w+e>=rn+dn) continue;
				if (d2[rn-w+e]<rd[w]+d[e]+sv) {
					d2[rn-w+e]=rd[w]+d[e]+sv;
				}
			}
		}

		dn+=rn;
		for (w=0;w<dn;w++) d[w]=d2[w];
		
	}
	rn=dn;
	for (q=0;q<rn;q++) rd[q]=d[q];
}