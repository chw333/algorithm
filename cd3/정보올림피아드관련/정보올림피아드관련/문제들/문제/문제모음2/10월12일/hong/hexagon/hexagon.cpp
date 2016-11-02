#include <fstream.h>
#include <string.h>

ifstream in("hexagon.in");
ofstream out("hexagon.out");

int maxScore;
int rot[6]; // �ﰢ�� i�� �����̼� ���� ����, 0,1,2
int tri[6][3]; // �ﰢ�� 6���� ����.

int getEdge(int n, int shift)
{
    // n�� �ﰢ���� ���ؼ� ���� �����Ѵ�.
    // ���� ���� ���¿��� ȸ����Ų��.
    // shift 0: ���� �ﰢ���� �����ϴ� ��
    // shift 1: ���� �ﰢ���� �����ϴ� ��
    // shift 2: �������� �ܰ���(������ ���)
    return tri[n][(rot[n] + shift) % 3];
}
int matchNext(int n)
{
    // n�� �ﰢ���� ���� �����̼� ���°� true �̸�
    // ���� �ﰢ���� ���纻��. n = 0 - 5 
    return getEdge(n, 1) == getEdge((n+1)%6, 0);
}
void swap(int i, int j)
{
    // triangle[i] �� triangle[j]�� �ٲ۴�.
    int temp[3];
	memmove(temp,tri[i],3*sizeof(int));
    memmove(tri[i],tri[j],3*sizeof(int));
    memmove(tri[j],temp,3*sizeof(int));
}
void fit(int n)
{
    // �ﰢ����ȣ < n ������ �ﰢ���� ���� ���纻��. ��, n = 1 - 6
    // n = 6�̸�, ������ tri[5]�� tri[0]�� ���纻��.
    // �ִ밪 ����
    int i, r;
	int score=0;
    if (n == 6) { //  ���̻� �ﰢ���� ������
		if (matchNext(5)) {
			for (i = 0; i < 6; i++) score += getEdge(i,2);        
			if(score>maxScore) maxScore=score;
		}
    } else { // ���� �ﰢ���� ���纽
		for(i=n;i<6;i++) { // ���� �ִ� ���� �ﰢ����� ���纽
			swap(n,i); //�׻� ����� �ﰢ���� n���� ���´�.
			for (r=0;r<3;r++) { // 3�� ��������.
				rot[n] = r;
				if (matchNext(n-1)) fit(n+1);
			}
			swap(n,i); // �ٽ� ����.
		}
    }
} 
void inp()
{
	int r, n;
    for(n=0;n<6;n++) {
		for(r=0;r<3;r++) {
			in >> tri[n][r];
		}
	}
}
void oup()
{
	if(maxScore==0) out << "impossible";
	else out << maxScore;
}
void proc()
{
	int r;
	for (r=0;r<3;r++) {
		rot[0]=r;
        fit(1);
	}
}
void main()
{
	inp();
	proc();
	oup();
}