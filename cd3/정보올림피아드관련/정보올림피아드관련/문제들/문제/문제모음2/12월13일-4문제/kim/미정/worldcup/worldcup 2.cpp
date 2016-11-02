#include <fstream.h>

#define MAXN 30

int N;
struct LIST {
	int a, b;  //a, b�� ����
};
struct LIST List[MAXN*MAXN]; //n(n-1)/2�� ��Ⱑ ����.
int ListCnt;


//0 = �����
//1..N-1 =��¥
//N..N+N*(N-1)/2-1 =���� ���
//N+N*(N-1)/2..N+N*(N-1)/2+N-2 =����
//N+N*(N-1)/2+N-1 = ������.
int Flow[MAXN*MAXN/2+MAXN*2+2][MAXN*MAXN/2+MAXN*2+2];
int BkFlow[MAXN*MAXN/2+MAXN*2+2][MAXN*MAXN/2+MAXN*2+2];
int PlayNum, PlayEndNum, CityNum, EndNum;

int Nation[MAXN];
int Path[MAXN*3];
int PathCnt;
int Visit[MAXN*MAXN/2+MAXN*2+2];

#define INFILE "worldcup02.in"
#define OUTFILE "worldcup.out"


int CheckPath()
{
	int i,j, n1, n2;
	for(i=0; i<=EndNum; i++) {
		for(j=0; j<=EndNum; j++) {
			BkFlow[i][j]=Flow[i][j];
		}
	}
	for(i=1; i<PathCnt; i++) {
		n1=Path[i-1];
		n2=Path[i];
		BkFlow[n1][n2]--; //flow ����
		BkFlow[n2][n1]++; //����� �����.
	}

	int idx;
	for(i=1; i<PathCnt; i++) {
		//dayüũ
		/*
		if(Path[i]>=1 && Path[i]<PlayNum) {
			for(j=0; j<N; j++) { Nation[j]=0; }

			idx=Path[i];
			for(j=PlayNum; j<=PlayEndNum; j++) {
				if(BkFlow[idx][j]==0) {
					n1=List[j-PlayNum].a;
					n2=List[j-PlayNum].b;
					if(Nation[n1]==0 && Nation[n2]==0) {
						Nation[n1]=1;
						Nation[n2]=1;
					} else {
						return 0;
					}
				}
			}
		}
		*/
		//cityüũ
		if(Path[i]>=CityNum && Path[i]<EndNum) {
			for(j=0; j<N; j++) { Nation[j]=0; }
			
			idx=Path[i];
			for(j=PlayNum; j<=PlayEndNum; j++) {
				if(BkFlow[j][idx]==0) {
					n1=List[j-PlayNum].a;
					n2=List[j-PlayNum].b;
					if(Nation[n1]==0 && Nation[n2]==0) {
						Nation[n1]=1;
						Nation[n2]=1;
					} else {
						return 0;
					}
				}
			}
		}
	}

	return 1;
}


int SearchPath(int node, int level)
{
	Path[level]=node;
	if(node==EndNum) {
		PathCnt=level+1;
		if(CheckPath()==1) 
			return 1;
		else 
			return 0;
	}

	Visit[node]=1;
	int i,j, n1,n2,flag;
	for(i=1; i<=EndNum; i++) {
		if(Visit[i]==0 && Flow[node][i]!=0) {
			//day���� ��� üũ.
			flag=0;
			if(node>=1 && node<PlayNum) {
				for(j=0; j<N; j++) { Nation[j]=0; }
				for(j=PlayNum; j<=PlayEndNum; j++) {
					if(Flow[node][j]==0) {
						n1=List[j-PlayNum].a;
						n2=List[j-PlayNum].b;
						if(Nation[n1]==0 && Nation[n2]==0) {
							Nation[n1]=1;
							Nation[n2]=1;
						} else {
							flag=1;
							break;
						}
					}
				}
			}
			if(flag==0 && SearchPath(i, level+1)==1) {
				return 1;
			}
		}
	}
	Visit[node]=0;
	return 0;
}



void main()
{
	int i,j;
	ifstream in(INFILE);
	in >> N;
	N=8;
	
	for(i=0; i<N; i++) {
		for(j=i+1; j<N; j++) {
			List[ListCnt].a=i;
			List[ListCnt].b=j;
			ListCnt++;
		}
	}

	//��Ʈ��ũ �÷��� ���� �ʱ�ȭ.
	//0. 0 = �����
	//1. 1..N-1 =��¥
	//2. N..N+N*(N-1)/2-1 =���� ���
	//3. N+N*(N-1)/2..N+N*(N-1)/2+N-2 =����
	//4. N+N*(N-1)/2+N-1 = ������.

	PlayNum=N;
	PlayEndNum=N+ListCnt-1;
	CityNum=PlayEndNum+1;
	EndNum=CityNum+N-1;
	for(i=1; i<=N-1; i++) {
		//1��ó��
		Flow[0][i]=N/2;
		//2��ó��
		for(j=PlayNum; j<=PlayEndNum; j++) {
			Flow[i][j]=1;
		}
	}
	//3��ó��
	for(i=PlayNum; i<=PlayEndNum; i++) {
		for(j=CityNum; j<EndNum; j++) {
			Flow[i][j]=1;
		}
	}
	//4��ó��
	for(i=CityNum; i<EndNum; i++) {
		Flow[i][EndNum]=N/2;
	}

	
	//��Ʈ��ũ �÷�
	int n1, n2;
	int day, flowcnt;

	//�ִ� ��Ī ���ϱ�.
	flowcnt=0;
	for(;;) {
		PathCnt=0;
		for(i=0; i<=EndNum; i++) { Visit[i]=0; }
		
		if(SearchPath(0, 0)==0) { break; }
		flowcnt++;

		for(i=1; i<PathCnt; i++) {
			n1=Path[i-1];
			n2=Path[i];
			Flow[n1][n2]--; //flow ����
			Flow[n2][n1]++; //����� �����.
		}
	}
	
		
	ofstream out(OUTFILE);
	if(flowcnt!=N*(N-1)/2) {
		out << "no";
	} else {

		//day��
		//���ŵ� �� ã��.
		
	}
}