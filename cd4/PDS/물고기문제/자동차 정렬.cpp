#include<fstream.h>
int N,Car,Work,Data[101][2],car[101][2];
void input(void)
{
	static int i,j,a[101],cnt,count=1;
	ifstream in("자동차 정렬.txt");
	in >> N >> Car >> Work;
	for(i = 1;i<=N;i++){
		in >> Data[i][0];
		a[Data[i][0]]++;
	}
	for(i = 1;i<=Car;i++){
		for(j = 1;j<=a[i];j++)
			Data[++cnt][1] = i;
		car[i][0] = count;
		car[i][1] = count+a[i]-1;
		count += a[i];
	}
}
void process(void)
{
	static int i,j,a,cnt=0,b,print[101][2],counter;
	for(i = 1;i<=N+1;i++){
		if(Data[i][0] != Data[i][1]){
			a = Data[i][0];
			for(j = car[a][0];j<=car[a][1];j++){
				if(Data[j][0] != Data[j][1]){
					b = a;
					a = Data[j][0];
					Data[j][0] = b;
					cnt++; j = car[a][0]-1;
					print[cnt][0] = a; print[cnt][1] = b;
				}
			}
		}
	}
	cnt-=Work; counter++;
	Work--;
	while(1){
		cnt -= Work;
		counter++;
		if(cnt < 1)
			break;
	}
	cout << counter;
}
void main(void)
{
	input();
	process();
}