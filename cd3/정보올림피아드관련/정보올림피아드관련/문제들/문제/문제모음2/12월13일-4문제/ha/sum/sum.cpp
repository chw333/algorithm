#include <fstream.h>

#define MAX 10002
#define TRUE 1
#define FALSE 0

void inputdata(void);
void process(void);
void outputdata(void);

int n,m,what;
int p[MAX];
int possible=TRUE;

void inputdata(void)
{
	int q,w,e;
	
	ifstream in("sum.in");
	in>>n>>m;
	q=n*(n-1)/2;
	if (m<-1*q) possible=FALSE;
	if (m>q) possible=FALSE;
	if ((q-m)%2==1) possible=FALSE;
	if (what<0) possible=FALSE;
	what=(q-m)/2;
	
}

void main(void)
{
	inputdata();
	if (possible) process();
	outputdata();
}

void outputdata(void)
{
	int q,w,e;
	ofstream out("sum.out");
	if (possible==FALSE) {
		out<<"NO"<<endl;
		return;
	}
	e=0;
	out<<e<<endl;
	for (q=n-1;q>=1;q--){
		e+=p[q];
		out<<e<<endl;
	}
}


void process(void)
{
	int q,w,e;
	int sum=0;
	
	for (q=n-1;q>=1;q--){
		p[q]=1;
		if (sum+q>what) continue;
		sum+=q;
		p[q]=-1;
	}
}

