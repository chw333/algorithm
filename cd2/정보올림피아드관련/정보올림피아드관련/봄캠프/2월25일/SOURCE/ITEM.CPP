#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX 102

void inputdata(void);
void greedy(void);

int n,m;
int a[2*MAX][MAX];
int b[2*MAX][MAX];
int ap[2*MAX];
int gcheck[MAX];
int tp[2*MAX], check[MAX];
void inputdata(void)
{
	int q,w,e;

	ifstream in("item.inp");
	in>>n>>m;
	for (q=1;q<=n;q++){
		for (w=1;w<=m;w++){
			in>>a[q][w];
			if (a[q][w]==1) {
				b[q][0]++;
				b[q][b[q][0]]=w;
			}
		}
	}
}

void main(void)
{
	int q,w,e;
	int loop,loop2;
	int what, what2;
	int temp, ccheck;
	int k=1000;

	inputdata();
	greedy();

	clock_t start, end;
	start=clock();
	for (;;){
		for (loop=1;loop<=1000;loop++){
			what=rand()%(tp[0])+1;
			if (tp[0]!=n) what2=rand()%(n-tp[0])+tp[0]+1; else what=rand()%n+1;
			ccheck=0;
			
			
			for (w=1;w<=b[tp[what2]][0];w++) check[b[tp[what2]][w]]++;
			for (w=1;w<=b[tp[what]][0];w++) {
				check[b[tp[what]][w]]--;
				if (check[b[tp[what]][w]]==0) ccheck=1;
			}

			if (ccheck==0) {
				temp=tp[what]; tp[what]=tp[what2];  tp[what2]=temp;
			}
			else if (rand()%10000>k) {
				temp=tp[what]; tp[what]=tp[what2];  tp[what2]=temp;
			}else {
				for (w=1;w<=b[tp[what2]][0];w++) check[b[tp[what2]][w]]--;
				for (w=1;w<=b[tp[what]][0];w++) check[b[tp[what]][w]]++;
			}
			ccheck=0;
			for (loop2=1;loop2<=m;loop2++) {
				if (check[loop2]==0) {ccheck=1; break;}
			}
			if (ccheck==0){
				for (q=1;q<=tp[0];q++){
					e=0;
					for (w=1;w<=b[tp[q]][0];w++){
						if (check[b[tp[q]][w]]<2) {e=1; break; }
					}
					if (e==0) {
//						cout<<"....."<<endl;
//						for (w=1;w<=m;w++) cout<<check[w]<<" "; cout<<endl;
						for (w=1;w<=b[tp[q]][0];w++) check[b[tp[q]][w]]--;						
						temp=tp[q]; tp[q]=tp[tp[0]]; tp[tp[0]]=temp;
						tp[0]--;
						for (w=0;w<=tp[0];w++){
							ap[w]=tp[w];
//							cout<<ap[w]<<" "; 
						}
//						cout<<"  ";
//						for (w=1;w<=3;w++) cout<<check[w]<<" "; 
//						cout<<endl; getch();
						break;
					}
				}
			}
//			for (q=1;q<=4;q++) cout<<tp[q]<<" "; cout<<endl;
		}
		k*=1.5;
		end=clock();
		if ((end-start)/CLOCKS_PER_SEC>4.5) break;
	}

	ofstream out("item.out");
	out<<ap[0]<<endl;
	for (q=1;q<=ap[0];q++) out<<ap[q]<<" "; out<<endl;
}


void greedy(void)
{
	int q,w,e;
	int max, what, count;
	int adfad[MAX*2];for (q=1;q<=n;q++) adfad[q]=0;

	for (q=1;q<=m;q++){
		if (gcheck[q]==0) {
			max=-1;
			for (w=1;w<=n;w++){
				count=0;
				for (e=q;e<=m;e++){
					if (a[w][e]==0&&gcheck[e]==0) break;
					count++;
				}
				if (count>max) {
					max=count; 
					what=w;
				}
			}
//			cout<<q<<" "<<what<<endl;
			for (w=1;w<=b[what][0];w++){
				gcheck[b[what][w]]++;
			}
//			for (w=1;w<=m;w++) cout<<gcheck[w]<<" "; cout<<endl;

		ap[0]++;
		ap[ap[0]]=what;
		adfad[what]=1;

		}

	}
	for (q=0;q<=n;q++) tp[q]=ap[q];
	for (q=1;q<=m;q++) check[q]=gcheck[q];
	w=ap[0];
	for (q=1;q<=n;q++) if (adfad[q]==0) tp[++w]=q;
}