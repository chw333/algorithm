#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip.h>

#define MAXN 1000

int N;
int List[MAXN][2];
struct RECT {
	int x1, y1, x2, y2;
};


#define INFILE "poster10.in"
#define OUTFILE "poster10.out"

#define MAKEN 1000 //�ִ� 1000����.
#define RANGE 10000 //�ִ� 10000����.

void makedata()
{
	ofstream out(INFILE);
	out << MAKEN << endl;

	srand(time(NULL));
	int i, x, y;
	for(i=0; i<MAKEN; i++) {
		x=rand()%(RANGE+1);
		y=rand()%(RANGE+1);

		out << x << " " << y << endl;
	}
}



int check_1(struct RECT &p, struct RECT &q)
{
	int i, x, y, v;
	int plen, qlen;
	for(i=0; i<N; i++) {
		x=List[i][0];
		y=List[i][1];

		//1. p�� q�� ���ԵǾ� ������ ���.
		if(x>=p.x1 && x<=p.x2 && y>=p.y1 && y<=p.y2) continue;
		if(x>=q.x1 && x<=q.x2 && y>=q.y1 && y<=q.y2) continue;

		//2. ���Ե��� ������, p�� q�߿� ����� ������ ���� �ø�.
		plen= x-p.x2;
		v   = y-p.y2;
		if(v > plen) plen=v;

		qlen= q.x2-x;
		v   = q.y2-y;
		if(v > qlen) qlen=v;

		if(plen > qlen) {
			plen = qlen;
		}

		//3. ���� �ø���, p�� x2, y2�� ����
		//                q�� x1, y1�� ����

		p.x2 += plen;
		p.y2 += plen;
		q.x1 -= plen;
		q.y1 -= plen;
	}

	return p.x2-p.x1;
}


int check_2(struct RECT &p, struct RECT &q)
{
	int i, x, y, v;
	int plen, qlen;
	for(i=0; i<N; i++) {
		x=List[i][0];
		y=List[i][1];

		//1. p�� q�� ���ԵǾ� ������ ���.
		if(x>=p.x1 && x<=p.x2 && y>=p.y1 && y<=p.y2) continue;
		if(x>=q.x1 && x<=q.x2 && y>=q.y1 && y<=q.y2) continue;

		//2. ���Ե��� ������, p�� q�߿� ����� ������ ���� �ø�.
		plen= x-p.x2;
		v   = p.y1-y;
		if(v > plen) plen=v;

		qlen= q.x1-x;
		v   = y-q.y2;
		if(v > qlen) qlen=v;

		if(plen > qlen) {
			plen = qlen;
		}

		//3. ���� �ø���, p�� x2+, y1-
		//                q�� x1-, y2+

		p.x2 += plen;
		p.y1 -= plen;
		q.x1 -= plen;
		q.y2 += plen;
	}

	return p.x2-p.x1;
}



void poster()
{
	int i;
	ifstream in(INFILE);

	in >> N;
	for(i=0; i<N; i++) {
		in >> List[i][0] >> List[i][1];
	}

	//���� ���� x,y��ġ�� ���� ū x,y��ġ ���ϱ�
	int x1, x2, y1, y2;
	x1=x2=List[0][0];
	y1=y2=List[0][1];
	for(i=1; i<N; i++) {
		if(x1 > List[i][0]) x1=List[i][0];
		if(x2 < List[i][0]) x2=List[i][0];
		if(y1 > List[i][1]) y1=List[i][1];
		if(y2 < List[i][1]) y2=List[i][1];
	}

	//1�� ������� ũ�� �����ϱ�.
	//      +--+q    
	//  +--+|  |    p�� x2+,y2+�� ����
	//  |  |+--+    q�� x1-,y1-�� ����
	// p+--+
	struct RECT p1, q1;
	int len1;
	p1.x1=x1; p1.y1=y1; p1.x2=x1; p1.y2=y1;
	q1.x1=x2; q1.y1=y2; q1.x2=x2; q1.y2=y2;
	len1= check_1(p1, q1);


	//2�� ������� ũ�� �����ϱ�.
	// p+--+
	//  |  |+--+   p�� x2+,y1-�� ����
	//  +--+|  |   q�� x1-,y2+�� ����
	//      +--+q
	struct RECT p2, q2;
	int len2;
	p2.x1=x1; p2.y1=y2; p2.x2=x1; p2.y2=y2;
	q2.x1=x2; q2.y1=y1; q2.x2=x2; q2.y2=y1;
	len2= check_2(p2, q2);

	ofstream out(OUTFILE);
	if(len1 < len2) {
		out << len1 << endl;
		out << p1.x1 << " " << p1.y1 << endl;
		out << q1.x1 << " " << q1.y1 << endl;
	} else {
		out << len2 << endl;
		out << p2.x1 << " " << p2.y1 << endl;
		out << q2.x1 << " " << q2.y1 << endl;
	}
}


void main()
{
	//makedata();
	poster();
}
