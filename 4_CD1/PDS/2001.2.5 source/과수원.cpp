#include<stdio.h>
#include<Fstream.h>
#define MAX 101
int N,X[MAX],Y[MAX],max,all_count;

void input(void)
{
	int i;
	ifstream in("°ú¼ö¿ø.txt");
	in >> N;
	for(i = 1;i<=N;i++)
		in >> X[i] >> Y[i];
}
void divide(int x1,int y1,int x2,int y2)
{
	int i,cnt,a[MAX];
	cnt = 0;
	all_count++;
	for(i = 1;i<=N;i++){
		if(x1 < X[i] && X[i] < x2 && y1 < Y[i] && Y[i] < y2)
			a[++cnt] = i;
	}
	if(cnt == 0){
		if(max < (x2-x1)*(y2-y1))
			max = (x2-x1)*(y2-y1);
	}
	else{
		for(i = 1;i<=cnt;i++){
			divide(X[a[i]],y1,x2,y2);
			divide(x1,y1,X[a[i]],y2);
			divide(x1,Y[a[i]],x2,y2);
			divide(x1,y1,x2,Y[a[i]]);
		}
	}
}
void main(void)
{
	input();
	divide(0,0,1000,1000);
	cout << max << endl;
	printf("\n%d",all_count);
}