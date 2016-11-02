#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip.h>

#define MAXN 1000

int N;
int NodeTri[MAXN][MAXN];
int Adjecnt[MAXN][MAXN];
int Element[MAXN];
int Set[MAXN];


#define INFILE "triangulation06.in"
#define OUTFILE "triangulation.out"



void main()
{
	int i,j, a, b, c, tmp;
	int cnt, idx;
	ifstream in(INFILE);
	in >> N;
	for(i=0; i<N-2; i++) {
		in >> a >> b >> c;
		
		//���� ������ �����ϴ� �ﰢ���� �ﰢ���� ��ȣ��
		//��������� ����.
		//print();

		NodeTri[a][0]++;
		cnt=NodeTri[a][0];
		NodeTri[a][cnt]=i;
		for(j=1; j<cnt; j++) {
			idx=NodeTri[a][j];
			Adjecnt[idx][i]=1;
			Adjecnt[i][idx]=1;
		}

		//print();

		NodeTri[b][0]++;
		cnt=NodeTri[b][0];
		NodeTri[b][cnt]=i;
		for(j=1; j<cnt; j++) {
			idx=NodeTri[b][j];
			Adjecnt[idx][i]=1;
			Adjecnt[i][idx]=1;
		}

		//print();

		NodeTri[c][0]++;
		cnt=NodeTri[c][0];
		NodeTri[c][cnt]=i;
		for(j=1; j<cnt; j++) {
			idx=NodeTri[c][j];
			Adjecnt[idx][i]=1;
			Adjecnt[i][idx]=1;
		}

		//print();

		//���� �ﰢ�������� �Ǵ�
		//��ȣ������ ���� a < b < c
		if(a > b) {
			tmp=a;
			a=b;
			b=tmp;
		}
		if(a > c) {
			tmp=c;
			c=b;
			b=a;
			a=tmp;
		} else {
			if(b > c) {
				tmp=c;
				c=b;
				b=c;
			}
		}

		//���� ��ȣ���� �Ǵ�
		if(a+1==b) {
			Element[i]=1;
		} else {
			if(b+1==c) {
				Element[i]=1;
			} else {
				if(a==0 && c==N-1) {
					Element[i]=1;
				}
			}
		}
		
	}


	//print();

	//���� �ﰢ���� �������ִ� �ﰢ������ �Ǵ�.
	int max=0;
	for(i=0; i<N; i++) {
		if(Element[i]==0) continue;

		if(Set[i]==0) {
			Set[i]=1;
			max++;
		}

		for(j=0; j<N; j++) {
			if(Adjecnt[i][j]==1 && Set[j]==0) {
				Set[j]=1;
				max++;
			}
		}
	}

	ofstream out(OUTFILE);
	out << max;
}
