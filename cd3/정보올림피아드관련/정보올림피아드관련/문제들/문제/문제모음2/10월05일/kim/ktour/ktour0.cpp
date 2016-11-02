#include <fstream.h>

#define INFILE "ktour10.in"
#define OUTFILE "ktour10.out"

#define MAXN 1000

int N, K;  //n은 노드수, k는 방문할 노드의 수
int Arr[MAXN][MAXN];

int InList[MAXN][MAXN], OutList[MAXN][MAXN]; 
int InCnt[MAXN], OutCnt[MAXN];
int InMark[MAXN], OutMark[MAXN], Mark[MAXN];

int Path[MAXN], AnsPath[MAXN];
int Visit[MAXN];

int FillNum1[MAXN], FillNum2[MAXN];
int FillCnt1, FillCnt2;

void fill1(int start)
{
	int i, idx, cnt;
	OutMark[start]=1;
	FillNum1[FillCnt1]=start;
	FillCnt1++;
	
	cnt=OutCnt[start];
	for(i=0; i<cnt; i++) {
		idx=OutList[start][i];
		if(OutMark[idx]==0) {
			fill1(idx);
		}
	}
}

void fill2(int start)
{
	int i, idx, cnt;
	InMark[start]=1;
	FillNum2[FillCnt2]=start;
	FillCnt2++;
	
	cnt=InCnt[start];
	for(i=0; i<cnt; i++) {
		idx=InList[start][i];
		if(OutMark[idx]==1 && InMark[idx]==0) {
			fill2(idx);
		}
	}
}



int dfs(int node, int end, int level)
{
	int i, cnt, res;
	int idx;
	Visit[node]=1;
	Path[level]=node;

	cnt=OutCnt[node];
	
	level++;
	if(level == K) {
		for(i=0; i<cnt; i++) {
			idx=OutList[node][i];
			if(idx==end) {
				Visit[node]=0;
				return 1;
			}
		}
		Visit[node]=0;
		return 0;
	}

	for(i=0; i<cnt; i++) {
		idx=OutList[node][i];
		if(idx<=end) continue;
		if(Visit[idx]==0 && OutMark[idx]==1 && InMark[idx]==1) {
			res=dfs(idx, end, level);
			if( res == 1 ) {
				Visit[node]=0;
				return 1;
			}
		}
	}

	Visit[node]=0;
	return 0;
}


void main()
{
	int i,j, flag=0;
	int a, b, cnt;
	ifstream in(INFILE);
	in >> N >> K;

	cnt=(N)*(N-1)/2;
	for(i=0; i<cnt; i++) {
		in >> a >> b;
		a--; b--;
		Arr[a][b]=1;

		OutList[a][OutCnt[a]]=b;
		InList[b][InCnt[b]]=a;
		OutCnt[a]++;
		InCnt[b]++;
	}
		
	for(i=0; i<N; i++) {
		//if(Mark[i]==1) continue;
		
		for(j=0; j<N; j++) {
			InMark[j]=0;
			OutMark[j]=0;
		}

		FillCnt1=0;
		fill1(i);
		
		FillCnt2=0;
		fill2(i);

		//cout << i << ":" << FillCnt2 << endl;
		
		if(FillCnt2 < K) continue;



		//경로 탐색
		if( dfs(i, i, 0) ==1) {
			flag=1;
			break;
		}
		
	}


	ofstream out(OUTFILE);
	if(flag==0) {
		out << 0;
	} else {
		for(i=0; i<K; i++) {
			if(i!=0) out << " ";
			out << Path[i]+1;
		}
	}

}