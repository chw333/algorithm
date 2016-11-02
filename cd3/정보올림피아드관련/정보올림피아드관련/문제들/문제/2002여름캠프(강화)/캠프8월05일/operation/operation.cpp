#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INFILE "operation07.in"
#define OUTFILE "operation07.out"
#define INFINIT 1000
#define MAXN 1000

int A, K;
int List[MAXN];
struct {
	int Cnt;
	int Arr[MAXN];
	int List[MAXN];
} Num[MAXN];
int NumCnt;
int MinCnt=INFINIT;


int Calc(int a, int b)
{
	char astr[20], bstr[20];
	int alen, blen;
	int asum, bmax, bmin;
	int i, n;

	sprintf(astr, "%d", a);
	sprintf(bstr, "%d", b);
	alen=strlen(astr);
	blen=strlen(bstr);
	asum=0;
	for(i=0; i<alen; i++) {
		n=astr[i]-'0';
		asum+=n;
	}

	bmax=bstr[0]-'0';
	bmin=bstr[0]-'0';
	for(i=1; i<blen; i++) {
		n=bstr[i]-'0';
		if(n>bmax) bmax=n;
		if(n<bmin) bmin=n;
	}

	return asum*bmax+bmin;
}


void main()
{
	int i,j, start, end, last, n;
	int cnt, flag;

	ifstream in(INFILE);
	in >> A >> K;

	n=Calc(A, A);
	List[n]=1;

	Num[0].Cnt=1;
	Num[0].Arr[0]=A;
	Num[1].Cnt=1;
	Num[1].Arr[0]=n;
	NumCnt+=2;

	if(K <= 738) {
		for(;;) {
			flag=0;
			last=NumCnt/2;
			//last=NumCnt;
			for(start=0; start<=last; start++) {
				end=NumCnt-start-1;
				for(i=0; i<Num[start].Cnt; i++) {
					for(j=0; j<Num[end].Cnt; j++) {
						n=Calc(Num[start].Arr[i], Num[end].Arr[j]);
						//이미 찾아진 경우는 최소 회수로 간주할 수 없음
						if(List[n]==0) {
							List[n]=NumCnt;
							flag=1;
						//}
						//if(Num[NumCnt].List[n]==0) {
							cnt=Num[NumCnt].Cnt++;
							Num[NumCnt].Arr[cnt]=n;
							Num[NumCnt].List[n]=cnt;
						}

						n=Calc(Num[end].Arr[j], Num[start].Arr[i]);
						if(List[n]==0) {
							List[n]=NumCnt;
							flag=1;
						//}
						//if(Num[NumCnt].List[n]==0) {
							cnt=Num[NumCnt].Cnt++;
							Num[NumCnt].Arr[cnt]=n;
							Num[NumCnt].List[n]=cnt;
						}
						
					}
				}

			}

			if(flag==0) break;
			
			NumCnt++;
			if(List[K] != 0) break;
		}
	}

	ofstream out(OUTFILE);
	if(List[K]==0) {
		out << "NEVAR" << endl;
	} else {
		out << List[K] << endl;
	}

	/*
	for(i=0; i<NumCnt; i++) {
		cnt=Num[i].Cnt;
		for(j=0; j<cnt; j++) {
			out << Num[i].Arr[j] << " ";
		}
		out << endl;
	}*/

}