#include <fstream.h>

#define INFILE "onewaybus10.in"
#define OUTFILE "onewaybus10.out"

#define MAXN 101
#define INFINIT 10000
int A, B;
int N, K;

int Arr[MAXN][MAXN];

int Visit[MAXN];
int DisDay[MAXN], DisTime[MAXN];
int Nearest[MAXN];
int Path[MAXN];

void main()
{
	int i,j, s, e, time;
	int day;

	ifstream in(INFILE);
	in >> A >> B;
	in >> N >> K;
	
	for(i=0; i<K; i++) {
		in >> s >> e >> time;
		Arr[s][e]=time;
	}

	//distance초기화
	for(i=1; i<=N; i++) {
		if(Arr[A][i]>0) {
			DisDay[i]=1; //하루
			DisTime[i]=Arr[A][i]; //시간
		} else if(Arr[i][A]>0) {
			DisDay[i]=2; //다음날
			DisTime[i]=Arr[i][A]; //시간
		} else {
			DisDay[i]=INFINIT;
			DisTime[i]=0;
		}
		Nearest[i]=A;
	}
	Visit[A]=1;

	//dijkstra
	//한 점은 이미 방문했고, 나머지의 최단 거리 계산
	int x, oddday;
	int day1, time1, day2, time2;

	for(i=1; i<N; i++) {
		//최소값 찾기
		day=INFINIT;
		time=0;
		for(j=1; j<=N; j++) {
			if(Visit[j]==1) continue;
			if(DisDay[j] < day) {
				x=j;
				day=DisDay[j];
				time=DisTime[j];
			} else if(DisDay[j] == day && DisTime[j] < time) {
				x=j;
				day=DisDay[j];
				time=DisTime[j];
			}
		}

		//최소 거리를 방문 표시
		Visit[x]=1;

		//x에서 방문하지 않은 노드 갱신
		for(j=1; j<=N; j++) {
			if(Visit[j]==1) continue;
			//if(Arr[x][j]==0 && Arr[j][x]==0) continue;

			//x에서 j점으로 가는 시간 계산
			oddday=DisDay[x]%2;
			if(oddday) {
				//홀수날 이다.
				day1=INFINIT;
				time1=0;
				if(Arr[x][j]>0) {
					//정방향이 있다면 같은 날에 갈 수 있다
					day1=DisDay[x];
					time1=DisTime[x]+Arr[x][j];
					if(time1 > 12) {
						//정방향으로 간다면 날짜를 2 더해야함.
						day1=DisDay[x]+2;
						time1=Arr[x][j];
					}
				}
				
				day2=INFINIT;
				time2=0;
				if(Arr[j][x]>0) {
					//역방향이 있다면 다음 날에 가야함.
					day2=DisDay[x]+1;
					time2=Arr[j][x];
				}
				
			} else {
				//짝수날 이다.
				day1=INFINIT;
				time1=0;
				if(Arr[j][x]>0) {
					//역방향이 있다면 같은 날에 갈 수 있다
					day1=DisDay[x];
					time1=DisTime[x]+Arr[j][x];
					if(time1 > 12) {
						//역방향으로 간다면 날짜를 2 더해야함.
						day1=DisDay[x];
						time1=Arr[j][x];
					}
				}
				
				day2=INFINIT;
				time2=0;
				if(Arr[x][j]>0) {
					//정방향이 있다면 다음 날에 가야함.
					day2=DisDay[x]+1;
					time2=Arr[x][j];
				}
			}

			if(day1 < day2) {
				day=day1;
				time=time1;
			} else if(day1 == day2 && time1 < time2) {
				day=day1;
				time=time1;
			} else {
				day=day2;
				time=time2;
			}


			if(DisDay[j] > day) {
				DisDay[j]=day;
				DisTime[j]=time;
				Nearest[j]=x;
			} else if(DisDay[j] == day && DisTime[j] > time) {
				DisDay[j]=day;
				DisTime[j]=time;
				Nearest[j]=x;
			}
		}
	}


	//dijkstra 끝.
	//출력
	
	int cnt=0, node;
	Path[cnt++]=node=B;
	while(1) {
		node=Nearest[node];
		Path[cnt++]=node;
		if(node==A) break;
	}

	ofstream out(OUTFILE);
	for(i=cnt-1; i>0; i--) {
		if(DisDay[Path[i-1]]%2==1) {
			time=Arr[Path[i]][Path[i-1]];
		} else {
			time=Arr[Path[i-1]][Path[i]];
		}
		out << Path[i] << " " << Path[i-1] << " " << 
			   DisDay[Path[i-1]] << " " << time << endl;
	}

}



/*
struct {
	int cnt;
	int dest[MAXN], time[MAXN];
} OddDay[MAXN], EvenDay[MAXN];

int Visit[MAXN];


#define MAXQ 10000
class QUE {
public:
	int Top;
	int Que[MAXQ],
		Day[MAXQ], Time[MAXQ];
	int Path[MAXQ];

	void In(int node, int day, int time, int prenode)
	{
		Que[Top]=node;
		Day[Top]=day;
		Time[Top]=time;
		Top++;

		if(Top==MAXQ) { cout << "inque error" << endl; }
	}

	void Out(int &node, int &day, int &time)
	{
		int i, idx, iday, itime;

		idx=-1;
		iday=MAXN;
		itime=MAXN;
		for(i=0; i<Top; i++) {
			
			if(Visit[Que[i]]==1) continue;
			
			if(Day[i] < iday ) {
				idx=i;
				iday=Day[i];
				itime=Time[i];
			} else if(Day[i] == iday && Time[i] < itime) {
				idx=i;
				iday=Day[i];
				itime=Time[i];
			}
		}
		
		node=idx;
		day=iday;
		time=item;

		//Que[idx]=Que[Top];
		//Day[idx]=Day[Top];
		//Time[idx]=Time[Top];

		//for(i=idx+1; i<Top; i++) {
		//	Que[i-1]=Que[i];
		//	Day[i-1]=Day[i];
		//	Time[i-1]=Time[i];
		//}

		//Top--;
		//if(Top<0) { cout << "inque error" << endl; }
	}
} Que;



void main()
{
	int i, s, e, time;
	int day;

	ifstream in(INFILE);
	in >> A >> B;
	in >> N >> K;
	
	for(i=0; i<K; i++) {
		in >> s >> e >> time;
		OddDay[s].dest[OddDay[s].cnt]=e;
		OddDay[s].time[OddDay[s].cnt]=time;
		OddDay[s].cnt++;

		EvenDay[e].dest[EvenDay[e].cnt]=s;
		EvenDay[e].time[EvenDay[e].cnt]=time;
		EvenDay[e].cnt++;
	}


	//출발지 삽입
	Que.In(A, 1,0,-1);
	int node, cnt;

	while(Que.Top!=0) {
		Que.Out(node, day, time);
		Visit[node]=1;
		if(node==B) break;

		cnt=
		for(
	}


	ofstream out(OUTFILE);

}
*/