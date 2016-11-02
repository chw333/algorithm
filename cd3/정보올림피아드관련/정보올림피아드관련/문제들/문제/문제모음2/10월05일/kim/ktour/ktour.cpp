//지금 이 방법은 정점의 중복을 생각하지 않아 코딩하다 중단함.
//즉, CntList에는 CntList[i][j]에서 i개의 점을 방문한 경우의 j번호의 점들을
//    넣었는데, 이것은 1개의 점을 들를때에, a번을 방문했는데, 3개째의 점을 들을때,
//    다시, a번을 방문할 경우가 발생한다.

#include <fstream.h>

#define INFILE "ktour02.in"
#define OUTFILE "ktour.out"

#define MAXN 1000

int N, K;  //n은 노드수, k는 방문할 노드의 수
int BkList[MAXN+1][MAXN]; //들어오는 간선의 리스트.

int CntList[MAXN+1][MAXN];
int CntPath[MAXN+1][MAXN];


int check(int node)
{
	int i,j, ki, cnt;
	int newnode, newcnt;
	bool visit[MAXN+1];
	//node로 돌아오는 정점을 CntList[0][]에 초기화.
	//i가 0부터 시작하면, 정점의 개수와 번호를 한꺼번에 복사함.
	//초기화된 정점은 한번 방문한 점임.
	cnt=BkList[node][0];
	for(i=0; i<=cnt; i++) {
		CntList[0][i]=BkList[node][i];
		CntPath[0][i]=node;
	}
	//K개 방문하고 돌아오는 경로 찾기.
	for(ki=1; ki<K; ki++) {
		memset(visit, MAXN, 0);
		cnt=CntList[ki-1][0];
		for(i=1; i<=cnt; i++) {
			newnode=CntList[ki-1][i];
			newcnt=BkList[newnode][0];
			for(j=1; j<=newcnt; j++) {
				if(visit[
			}
		}

	}
}


void main()
{
	int i,j, node;
	int a, b, cnt;
	ifstream in(INFILE);
	in >> N >> K;

	cnt=(N)*(N-1)/2;
	for(i=0; i<cnt; i++) {
		in >> a >> b;
		BkList[b][0]++; //BkList[b][0]은 b에서 들어오는 간선의 개수.
		BkList[b][ BkList[b][0] ]=a;
	}

	for(node=1; node<=N; node++) {
		//탐색.
		if( check(node) ==1) {
			break;
		}
	}
}