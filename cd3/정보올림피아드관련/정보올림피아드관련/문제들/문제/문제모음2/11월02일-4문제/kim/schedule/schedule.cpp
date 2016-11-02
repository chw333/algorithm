#include <fstream.h>
#include <time.h>
#include <stdlib.h>

#define MAXN 30

int M, N; //M은 여자의 수, N은 남자의 수.
int FMale[MAXN];

struct DAY {
	int Cnt;
	int Man[MAXN][2]; //Man[][0] 여자 번호
};                    //Man[][1] 남자 번호
struct DAY Day[MAXN*2];
int DayCnt, MeetingDayCnt;

int Flow[MAXN+MAXN+2][MAXN+MAXN+2];
int BkFlow[MAXN+MAXN+2][MAXN+MAXN+2];
int EndNum;

int Path[MAXN*2];
int PathCnt;
int Visit[MAXN+MAXN+2];

#define INFILE "schedule10.in"
#define OUTFILE "schedule10.out"

#define MAKEM 30
#define MAKEN 30
#define NETCNT 400
int MakeNet[MAKEM][MAKEN];

void makedata()
{
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKEM << " " << MAKEN << endl;
	int i=0, j, cnt, s, e;
	while(i<NETCNT) {
		s=rand()%MAKEM;
		e=rand()%MAKEN;
		if(MakeNet[s][e]==0) {
			MakeNet[s][e]=1;
			i++;
		}
	}

	for(i=0; i<MAKEM; i++) {
		cnt=0; 
		for(j=0; j<MAKEN; j++) {
			if(MakeNet[i][j]==1) {
				cnt++;
			}
		}
		out << cnt;
		for(j=0; j<MAKEN; j++) {
			if(MakeNet[i][j]==1) {
				out << " " << j+1; 
			}
		}
		out << endl;
	}
}


int SearchPath(int node, int level)
{
	int i;
	Visit[node]=1;
	Path[level]=node;
	if(node==EndNum) {
		PathCnt=level+1;
		return 1;
	}
	for(i=1; i<=EndNum; i++) {
		if(Visit[i]==0 && Flow[node][i]!=0) {
			if(SearchPath(i, level+1)==1) {
				return 1;
			}
		}
	}
	//Visit[node]=0;
	return 0;
}



void schedule()
{
	int i,j, cnt;
	ifstream in(INFILE);
	in >> M >> N;
	
	//네트워크 플로의 관계 초기화.
	//0. 0은 출발점.
	//1. 1부터 M까지는 여자 번호
	//2. M+1부터 M+N번까지는 남자의 번호
	//3. M+N+1 도착점.
	EndNum=M+N+1;
	int b;
	for(i=1; i<=M; i++) {
		in >> cnt;
		FMale[i-1]=cnt;

		//1번처리
		Flow[0][i]=1;
		//2번처리
		for(j=0; j<cnt; j++) {
			in >> b;
			Flow[i][M+b]=1;
		}
	}
	//3번처리
	for(i=M+1; i<EndNum; i++) {
		Flow[i][EndNum]=1;
	}

	//Flow를 BkFlow에 저장.
	for(i=0; i<=EndNum; i++) {
		for(j=0; j<=EndNum; j++) {
			BkFlow[i][j]=Flow[i][j];
		}
	}
	

	//네트워크 플로
	int day, flowcnt;
	int n1, n2;

	day=0;
	for(;;) {
		//최대 매칭 구하기.
		flowcnt=0;
		for(;;) {
			PathCnt=0;
			for(i=0; i<=EndNum; i++) { Visit[i]=0; }
			
			if(SearchPath(0, 0)==0) { break; }
			flowcnt++;

			for(i=1; i<PathCnt; i++) {
				n1=Path[i-1];
				n2=Path[i];
				Flow[n1][n2]--; //flow 제거
				Flow[n2][n1]++; //역경로 만들기.
			}
		}
		if(flowcnt==0) {
			DayCnt=day;
			break;
		}
		MeetingDayCnt++;

		//day에
		//제거된 선 찾기.
		for(i=1; i<=M; i++) {
			for(j=M+1; j<EndNum; j++) {
				if(BkFlow[i][j]!=0 && Flow[i][j]==0) {
					Day[day].Man[ Day[day].Cnt ][0]= i-1;
					Day[day].Man[ Day[day].Cnt ][1]= j-M-1;
					Day[day].Cnt++;

					FMale[i-1]--;
					if( FMale[i-1]==0) {
						BkFlow[0][i]=0;
					}
					BkFlow[i][j]--;
					
					//BkFlow[j][EndNum]--;
				}
			}
		}

		//Flow복구
		for(i=0; i<=EndNum; i++) {
			for(j=0; j<=EndNum; j++) {
				Flow[i][j]=BkFlow[i][j];
			}
		}
		day++;
	}

	ofstream out(OUTFILE);
	out << MeetingDayCnt << endl;
	for(day=0; day<DayCnt; day++) {
		cnt=Day[day].Cnt;
		for(i=0; i<cnt; i++) {
			if(i!=0) out << " ";
			out << "(" << Day[day].Man[i][0]+1 << " "
				<< Day[day].Man[i][1]+1 << ")";
		}
		out << endl;
	}
}


void main()
{
	makedata();
	schedule();
}