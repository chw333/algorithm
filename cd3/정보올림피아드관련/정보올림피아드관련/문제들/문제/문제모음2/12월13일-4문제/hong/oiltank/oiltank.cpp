#include <fstream.h>
#include <stdio.h>

#define MAXS 111
#define MAXO 211

ifstream in("oiltank.in");
ofstream out("oiltank.out");

struct _o {
	int Di; // 이전 주유소에서 현재 주유소까지 떨어진 거리
	double P; // 현재 정유소에서 기름 가격
} O[MAXS]; // 주유소 정보

double Cost[MAXS][MAXO], A; // 비용 다이나믹 테이블 ,최종 목적지 까지 가는데 드는 최소 비용
int Di, Oc; // 목적지까지의 최대 거리,  주유소 개수


void inp()
{
	int i, j;

	in >> Di;
	O[0].Di=0;
	O[0].P=99999999; // 어차피 채울 수 없으니깐 무한대의 액수만큼 비용이 든다고 본다.
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
