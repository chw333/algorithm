#include <fstream.h>
#include <stdio.h>

#define MAXS 111
#define MAXO 211

ifstream in("oiltank.in");
ofstream out("oiltank.out");

struct _o {
	int Di; // ���� �����ҿ��� ���� �����ұ��� ������ �Ÿ�
	double P; // ���� �����ҿ��� �⸧ ����
} O[MAXS]; // ������ ����

double Cost[MAXS][MAXO], A; // ��� ���̳��� ���̺� ,���� ������ ���� ���µ� ��� �ּ� ���
int Di, Oc; // ������������ �ִ� �Ÿ�,  ������ ����


void inp()
{
	int i, j;

	in >> Di;
	O[0].Di=0;
	O[0].P=99999999; // ������ ä�� �� �����ϱ� ���Ѵ��� �׼���ŭ ����� ��ٰ� ����.
	Oc++;
	for(i=1;!in.eof();i++) {
		in >> O[i].Di >> O[i].P;
		Oc++;
	}
	O[Oc].Di=Di;
	O[Oc++].P=99999999;
	for(i=0;i<Oc;i++) 
		for(j=0;j<=200;j++)
			Cost[i][j]=99999999;
}

void oup()
{
	char s[100];
	if(A!=99999999) { sprintf(s,"%.0lf",A); out << s; } else out << "impossible";
}

void proc()
{
	int i,j,k;
	Cost[0][100]=0;
	for(i=0;i<Oc;i++) {
		for(j=0;j<=200;j++) {
			for(k=i;k<Oc && (O[k].Di-O[i].Di)<=j;k++) {
				if(Cost[k][j-(O[k].Di-O[i].Di)]>Cost[i][j]) {
					Cost[k][j-(O[k].Di-O[i].Di)]=Cost[i][j];
				}
			}
			for(k=j+1;k<=200;k++) {
				if(Cost[i][k]>(Cost[i][j]+(double)(k-j)*O[i].P)) {
					Cost[i][k]=Cost[i][j]+(double)(k-j)*O[i].P;
				}
			}
		}
	}
	A=Cost[Oc-1][100];
}

void main()
{
	inp();
	proc();
	oup();
}
