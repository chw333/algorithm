#include <fstream.h>
#include <string.h>
#include <stdlib.h>

#define InFile "cd2.in"
#define OutFile "cd1.out"
#define MaxN 100
#define MaxValue 2000000000
#define HiLimit 680
#define LoLimit 350
#define BkValue 100
#define BkTitleValue 1000
#define BkPageValue 2000

int N;
int Bk[MaxN];
int MinValue=MaxValue;
int MinBk=MaxValue;
int AnsBk[MaxN];
int AnsTableSum[MaxN+1];
int VisitTableSum[MaxN+1];

int Visit[MaxN];
int TableSum[MaxN+1];

int sortf(const void *a, const void *b)
{
	int *p=(int *)a, *q=(int *)b;
	return *p-*q;
}


void checkBk(int node, int num)
{
	int i,j, n, sum;
	if(node==N) {
		sum=0;
		for(i=1; i<=num; i++) {
			if(TableSum[i]<LoLimit) return;
			n=(TableSum[i]+BkValue-1)/BkValue;
			sum+=n*BkPageValue + BkTitleValue;
		}

		if(sum < MinValue) {
			MinValue=sum;
			MinBk=num;
			for(i=0; i<N; i++) {
				AnsBk[i]=Visit[i];
			}
			
			for(i=0; i<num; i++) {
				AnsTableSum[i]=TableSum[i+1];
			}
			qsort(AnsTableSum, num, sizeof(AnsTableSum[0]), sortf);

		} else if(sum == MinValue) {
			for(i=0; i<num; i++) {
				VisitTableSum[i]=TableSum[i+1];
			}
			qsort(VisitTableSum, num, sizeof(VisitTableSum[0]), sortf);
			for(i=0; i<num; i++) {
				if(VisitTableSum[i] == AnsTableSum[i]) {
				} else if(VisitTableSum[i] < AnsTableSum[i]) {
					MinBk=num;
					for(j=0; j<num; j++) {
						AnsTableSum[j]=VisitTableSum[j];
					}
					break;
				} else break;
			}
		}
		return;
	}

	for(i=1; i<=num; i++) {
		TableSum[i]+=Bk[node];
		if(TableSum[i] <= HiLimit) {
			Visit[node]=i;
			checkBk(node+1, num);
			Visit[node]=0;
		}
		TableSum[i]-=Bk[node];
	}
}


int main(int argc, char* argv[])
{
	int i,j, n, num, sum=0, v;
	//ifstream in(InFile);
	cout << "동화 파일의 개수 ? ";
	cin >> N;
	char instr[100], *p;
	for(i=0; i<N; i++) {
		//in >> n >> Bk[i];
		cin >> instr;
		p=strtok(instr, ",");
		p=strtok(NULL, ",");
		Bk[i]=atoi(p);
		sum+=Bk[i];
	}
	for(i=0; i<N; i++) {
		for(j=0; j<i; j++) {
			if(Bk[i] == Bk[j] ) {
				cout << "입력오류!" << endl;
				return 0;
			}
		}
	}

	sum=(sum+HiLimit-1)/HiLimit;

	num=sum;
	for(;;) {
		Visit[0]=1;
		for(i=1; i<=num; i++) {
			TableSum[i]=0;
		}
		TableSum[1]=Bk[0];

		checkBk(1, num);

		num++;
		n=(LoLimit+BkValue-1)/BkValue;
		v=num*( BkTitleValue+ n*BkPageValue);
		if(MinBk < v) break;
	}


	//ofstream out(OutFile);
	cout << endl;
	cout << "최소 비용 : " << MinValue << endl;
	cout << "사용된 CD 개수 : " << MinBk << endl;

	for(i=0; i<MinBk; i++) {
		cout << "CD " << i+1 << " : ";
		cout << AnsTableSum[i];		
		cout << endl;
	}

	return 0;
}
