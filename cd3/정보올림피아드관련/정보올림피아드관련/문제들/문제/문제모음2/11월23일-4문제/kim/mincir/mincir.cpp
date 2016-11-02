#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip.h>


#define MAXN 100
#define INFINIT 1000000

int N; 
int Grape[MAXN][MAXN];
int MinValue=INFINIT;
int MinPath[MAXN], MinPathCnt;

int Distance[MAXN];
int Nearest[MAXN];
int Visit[MAXN];

#define INFILE "mincir09.in"
#define OUTFILE "mincir09.out"

#define MAKEN 90
#define MAKEG 1000
#define RANGE 300
int Arr[MAXN][MAXN];
int Set[MAXN];

void makedata()
{
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKEN << endl;
	out << MAKEG << endl;

	int i,j, a, b, w, cnt, num;
	
	//����Ʈ�� ����.
	for(i=0; i<MAKEN; i++) {
		Set[i]=i;
	}
	cnt=0;
	for(;;) {
		a=rand()%MAKEN;
		b=rand()%MAKEN;
		w=rand()%RANGE+1;

		//���� �����̸� ��ȯ�� ��.
		if(Set[a]==Set[b]) { continue; }

		cnt++;
		Arr[a][b]=w;
		Arr[b][a]=w;
		num=Set[b];
		for(i=0; i<MAKEN; i++) {
			if(Set[i]==num) {
				Set[i]=Set[a];
			}
		}

		if(cnt==MAKEN-1) break;
	}
	
	//������ ������ ������ ����.
	for(;;) {
		a=rand()%MAKEN;
		b=rand()%MAKEN;
		w=rand()%RANGE+1;

		if(a==b) continue;
		if(Arr[a][b]!=0) continue;

		cnt++;
		Arr[a][b]=w;
		Arr[b][a]=w;

		if(cnt==MAKEG) break;
	}
	

	cnt=0;
	for(i=0; i<MAKEN; i++) {
		for(j=i+1; j<MAKEN; j++) {
			if(Arr[i][j]!=0) {
				out << i+1 << " " << j+1 << " " << Arr[i][j] << endl;
				cnt++;
			}
		}
	}
	//out << cnt;
}



int shortestpath(int start, int end)
{
	int i, j, min, x;
	//�ʱ�ȭ.
	for(i=0; i<N; i++) {
		if(Grape[start][i]==0) {
			Distance[i]=INFINIT;
		} else {
			Distance[i]=Grape[start][i];
		}
		Nearest[i]=start;
		Visit[i]=0;
	}
	Visit[start]=1;


	//���ͽ�ũ��.
	for(i=1; i<N; i++) {
		//�ּ�ã��
		min=INFINIT;
		x=INFINIT;
		for(j=0; j<N; j++) {
			if(Visit[j]==0 && Distance[j] < min) {
				min=Distance[j];
				x=j;
			}
		}
		
		//����� ������ ����.
		if(x==INFINIT) { return INFINIT; }

		//�湮üũ
		Visit[x]=1;

		//�����ϱ�
		for(j=0; j<N; j++) {
			if(Visit[j]==0 && Grape[x][j]!=0 && Distance[x]+Grape[x][j] < Distance[j]) {
				Distance[j]=Distance[x]+Grape[x][j];
				Nearest[j]=x;
			}
		}
	}

	return Distance[end];
}



void mincir()
{
	int i,j, g, a,b, w;
	ifstream in(INFILE);

	in >> N >> g;
	for(i=0; i<g; i++) {
		in >> a >> b >> w;
		a--; b--;
		Grape[a][b]=w;
		Grape[b][a]=w;
	}

	int v, num;
	for(i=0; i<N; i++) {
		for(j=i+1; j<N; j++) {
			if(Grape[i][j]>0) {
				num=Grape[i][j];
				Grape[i][j]=0;
				v=shortestpath(i, j);
				v+=num;
				Grape[i][j]=num;

				if(v < MinValue) {
					MinValue=v;
					//�н�����.
					num=j;
					MinPathCnt=0;
					MinPath[0]=num;
					MinPathCnt++;
					while(1) {
						num=Nearest[num];
						MinPath[MinPathCnt]=num;
						MinPathCnt++;
						if(num==i) break;
					}

				}
			}
		}
	}

	ofstream out(OUTFILE);
	out << MinValue << endl;
	out << MinPathCnt << endl;
	out << MinPath[MinPathCnt-1]+1;
	for(i=0; i<MinPathCnt; i++) {
		out << " " << MinPath[i]+1;
	}
	
}


void main()
{
	makedata();
	mincir();
}