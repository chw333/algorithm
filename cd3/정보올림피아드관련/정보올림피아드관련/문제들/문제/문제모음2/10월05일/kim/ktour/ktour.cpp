//���� �� ����� ������ �ߺ��� �������� �ʾ� �ڵ��ϴ� �ߴ���.
//��, CntList���� CntList[i][j]���� i���� ���� �湮�� ����� j��ȣ�� ������
//    �־��µ�, �̰��� 1���� ���� �鸦����, a���� �湮�ߴµ�, 3��°�� ���� ������,
//    �ٽ�, a���� �湮�� ��찡 �߻��Ѵ�.

#include <fstream.h>

#define INFILE "ktour02.in"
#define OUTFILE "ktour.out"

#define MAXN 1000

int N, K;  //n�� ����, k�� �湮�� ����� ��
int BkList[MAXN+1][MAXN]; //������ ������ ����Ʈ.

int CntList[MAXN+1][MAXN];
int CntPath[MAXN+1][MAXN];


int check(int node)
{
	int i,j, ki, cnt;
	int newnode, newcnt;
	bool visit[MAXN+1];
	//node�� ���ƿ��� ������ CntList[0][]�� �ʱ�ȭ.
	//i�� 0���� �����ϸ�, ������ ������ ��ȣ�� �Ѳ����� ������.
	//�ʱ�ȭ�� ������ �ѹ� �湮�� ����.
	cnt=BkList[node][0];
	for(i=0; i<=cnt; i++) {
		CntList[0][i]=BkList[node][i];
		CntPath[0][i]=node;
	}
	//K�� �湮�ϰ� ���ƿ��� ��� ã��.
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
		BkList[b][0]++; //BkList[b][0]�� b���� ������ ������ ����.
		BkList[b][ BkList[b][0] ]=a;
	}

	for(node=1; node<=N; node++) {
		//Ž��.
		if( check(node) ==1) {
			break;
		}
	}
}