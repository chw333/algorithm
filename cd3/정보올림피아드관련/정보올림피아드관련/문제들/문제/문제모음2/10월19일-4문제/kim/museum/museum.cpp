#include <fstream.h>
#include <iomanip.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define INFILE "museum.in"
#define OUTFILE "museum.out"
#define INFINIT 100000000
#define MAXN 30

struct TRI {
	int shape, left, right, line;
	int adj[3];
};
int N;
TRI Tri[MAXN*MAXN];
int StartIdx[MAXN*MAXN];
int EndIdx[MAXN*MAXN];
int EndNum;
int Min;
int Change[MAXN*MAXN*3][2];
int ChangeCnt;

clock_t StartTime, CurTime;

int TestCnt[MAXN*MAXN];



#define MAKEN 3
int MakeStartIdx[MAXN*MAXN];
int MakeEndIdx[MAXN*MAXN];

void makedata()
{
	srand(time(NULL));
	int i, endnum=MAKEN*MAKEN;
	int v1, v2, tmp;

	for(i=0; i<endnum; i++) {
		MakeStartIdx[i]=i+1;
	}
	for(i=0; i<endnum; i++) {
		v1=rand()%endnum;
		v2=rand()%endnum;
		tmp=MakeStartIdx[v1];
		MakeStartIdx[v1]=MakeStartIdx[v2];
		MakeStartIdx[v2]=tmp;
	}

	for(i=0; i<endnum; i++) {
		MakeEndIdx[i]=i+1;
	}
	for(i=0; i<endnum; i++) {
		v1=rand()%endnum;
		v2=rand()%endnum;
		tmp=MakeEndIdx[v1];
		MakeEndIdx[v1]=MakeEndIdx[v2];
		MakeEndIdx[v2]=tmp;
	}

	ofstream out(INFILE);
	out << MAKEN << endl;
	for(i=0; i<endnum; i++) {
		if(i!=0) out << " ";
		out << MakeStartIdx[i];
	}
	out << endl;
	for(i=0; i<endnum; i++) {
		if(i!=0) out << " ";
		out << MakeEndIdx[i];
	}
}


void print()
{
	int i,j, endnum=N*N;
	int idx, linenum;

	idx=0; linenum=1;
	for(i=0; i<N; i++) {
		for(j=0; j<linenum; j++) {
			cout << setw(3) << StartIdx[idx];
			idx++;
		}
		cout << endl;
		linenum+=2;
	}
	cout << endl;
}


int go_upleft(int num)
{
	//정삼각형이면, 위 왼쪽이 0번
	//역삼각형이면, 위가 2번.
	if(Tri[num].shape==0) {
		return Tri[num].adj[0];
	} else {
		return Tri[num].adj[2];
	}
}
int go_upright(int num)
{
	//정삼각형이면, 위 왼쪽이 1번
	//역삼각형이면, 위가 2번.
	if(Tri[num].shape==0) {
		return Tri[num].adj[1];
	} else {
		return Tri[num].adj[2];
	}
}
int go_downleft(int num)
{
	//역삼각형이면, 아래 왼쪽이 0번.
	//정삼각형이면, 아래가 2번
	if(Tri[num].shape==1) {
		return Tri[num].adj[0];
	} else {
		return Tri[num].adj[2];
	}
}
int go_downright(int num)
{
	//역삼각형이면, 아래 왼쪽이 1번.
	//정삼각형이면, 아래가 2번
	if(Tri[num].shape==1) {
		return Tri[num].adj[1];
	} else {
		return Tri[num].adj[2];
	}
}



int calc(int index[MAXN*MAXN])
{
	int i,j, idx, v;
	int sum=0, cnt, num;
	for(i=0; i<EndNum; i++) {
		//이동해야할 위치 찾기
		for(j=0; j<EndNum; j++) {
			if( index[i] == EndIdx[j] ) {
				idx=j;
				break;
			}
		}

		//나의 위치와 이동해야할 위치의 차이 계산
		//나=i, 이동위치=idx
		if( Tri[i].line == Tri[idx].line) {
			//같은 줄이면 옆으로 이동.
			cnt=i-idx;
			if(cnt<0) cnt=-cnt;
		} else {
			cnt=0;
			//윗줄로 이동
			num=i;
			if(Tri[i].line > Tri[idx].line) {
				//왼쪽에 있음.
				if(Tri[idx].left < Tri[idx].right) {
					while(1) {
						if(Tri[num].left==Tri[idx].left) {
							while(1) {
								num=go_upright(num);
								cnt++;
								if(Tri[num].line==Tri[idx].line) {
									break;
								}
							}
							break;
						}
						num=go_upleft(num);
						cnt++;
						if(Tri[num].line==Tri[idx].line) {
							break;
						}
					}
				//오른쪽에 있음.
				} else {
					while(1) {
						if(Tri[num].right==Tri[idx].right) {
							while(1) {
								num=go_upleft(num);
								cnt++;
								if(Tri[num].line==Tri[idx].line) {
									break;
								}
							}
							break;
						}
						num=go_upright(num);
						cnt++;
						if(Tri[num].line==Tri[idx].line) {
							break;
						}
					}
				}
				
				//같은 줄인데, 위치가 다르면
				v=num-idx;
				if(v<0) v=-v;
				cnt+=v;

			//아래줄로 이동
			} else {
				//왼쪽에 있음.
				if(Tri[idx].left < Tri[idx].right) {
					while(1) {
						num=go_downleft(num);
						cnt++;
						if(Tri[num].line==Tri[idx].line) {
							break;
						}
						if(Tri[num].right==Tri[idx].right) {
							while(1) {
								num=go_downright(num);
								cnt++;
								if(Tri[num].line==Tri[idx].line) {
									break;
								}
							}
							break;
						}
					}

				//오른쪽에 있음.
				} else {
					while(1) {
						num=go_downright(num);
						cnt++;
						if(Tri[num].line==Tri[idx].line) {
							break;
						}
						if(Tri[num].left==Tri[idx].left) {
							while(1) {
								num=go_downleft(num);
								cnt++;
								if(Tri[num].line==Tri[idx].line) {
									break;
								}
							}
							break;
						}
					}
				}

				//같은 줄인데, 위치가 다르면
				v=num-idx;
				if(v<0) v=-v;
				cnt+=v;
			}
		}
		sum+=cnt;
		TestCnt[i]=cnt;

	}
	return sum;
}




void museum()
{
	StartTime=clock();
	int i,j;
	int idx, linecnt, leftnum, rightnum;
	int startnum, newnum, endnum;
	ifstream in(INFILE);
	in >> N;
	EndNum=endnum=N*N;
	for(i=0; i<endnum; i++) {
		in >> StartIdx[i];
		StartIdx[i]--;
	}
	for(i=0; i<endnum; i++) {
		in >> EndIdx[i];
		EndIdx[i]--;
	}

	//삼각형의 정보를 초기화 함.
	idx=0;
	linecnt=0;
	for(i=0; i<N; i++) {
		leftnum=0;
		rightnum=linecnt-leftnum;
		startnum=idx;
		for(j=0; j<=linecnt; j++) {
			Tri[idx].line=i; //윗줄에서 몇번째 줄. 번호는 0번부터.
			Tri[idx].left=leftnum/2; //왼쪽에서 몇번째. 번호는 0번부터.
			Tri[idx].right=rightnum/2; //오른쪽에서 몇번째. 번호는 0번부터.
			leftnum++;
			rightnum--;
			Tri[idx].shape=j%2;  //모양이 정삼각형인지 역삼각형인지= 정삼각형은 0, 역삼각형은 1
			
			//왼쪽
			if(idx-1 >= startnum) {
				Tri[idx].adj[ 0 ]=idx-1;
			} else {
				Tri[idx].adj[ 0 ]=-1;
			}
			//오른쪽
			if(idx+1 <= startnum+linecnt) {
				Tri[idx].adj[ 1 ]=idx+1;
			} else {
				Tri[idx].adj[ 1 ]=-1;
			}

			//위 또는 아래
			if(Tri[idx].shape==0) {
				//정삼각형이면, 아래
				newnum=idx+linecnt+2;
				if(newnum < endnum) {
					Tri[idx].adj[ 2 ] = newnum;
				} else {
					Tri[idx].adj[ 2 ] = -1;
				}
			} else {
				//역삼각형이면, 위
				Tri[idx].adj[ 2 ] = idx-linecnt;
			}
			idx++;
		}
		linecnt+=2;
	}

	//두개의 위치를 바꾸는 모든 경우 초기화
	linecnt=1;
	ChangeCnt=0;
	for(i=1; i<N; i++) {
		startnum=i*i;
		startnum++;
		for(j=0; j<linecnt; j++) {
			//항상 역삼각형 모양으로 잡아서 세팅.
			Change[ChangeCnt][0]=Tri[startnum].adj[2];
			Change[ChangeCnt][1]=startnum;
			ChangeCnt++;

			Change[ChangeCnt][0]=startnum-1;
			Change[ChangeCnt][1]=startnum;
			ChangeCnt++;

			Change[ChangeCnt][0]=startnum;
			Change[ChangeCnt][1]=startnum+1;
			ChangeCnt++;

			startnum+=2;
		}
		linecnt++;
	}

	/*
	int cnt=calc(StartIdx);
	for(i=0; i<endnum; i++) {
		cout << setw(3) << StartIdx[i];
	}
	cout << endl;
	for(i=0; i<endnum; i++) {
		cout << setw(3) << EndIdx[i];
	}
	cout << endl;
	for(i=0; i<endnum; i++) {
		cout << setw(3) << TestCnt[i];
	}
	cout << endl;
	cout << cnt << endl;

	for(i=0; i<ChangeCnt; i++) {
		cout << setw(3) << Change[i][0];
	}
	cout << endl;
	for(i=0; i<ChangeCnt; i++) {
		cout << setw(3) << Change[i][1];
	}
	*/

	/*
	//국소탐색 = 근사로 풀었다가 다시 푼다.
	srand(time(NULL));
	int tmp, changeNum[2];
	int v, value=calc(StartIdx);
	int cnt=0;
	while(1) {
		CurTime=clock();
		if( ((double)(CurTime-StartTime))/CLK_TCK > 7.9) { 
			//cnt=INFINIT;
			//break;
		}
	
		v=rand()%ChangeCnt;
		changeNum[0]=Change[v][0];
		changeNum[1]=Change[v][1];
		//바꾸기
		tmp=StartIdx[ changeNum[0] ];
		StartIdx[ changeNum[0] ] = StartIdx[ changeNum[1] ];
		StartIdx[ changeNum[1] ] = tmp;
		
		v=calc(StartIdx);
		if(v >= value) {
			//복구
			tmp=StartIdx[ changeNum[0] ];
			StartIdx[ changeNum[0] ] = StartIdx[ changeNum[1] ];
			StartIdx[ changeNum[1] ] = tmp;
			continue;
		}
		cnt++;
		cout << cnt << endl;
		value=v;
		print();
		if(v==0) {
			break;
		}
	}
	Min=cnt;
	cout << cnt << endl;
	*/


	ofstream out(OUTFILE);
	out << Min;

}


void main()
{
	//makedata();
	museum();
}