#include<Fstream.h>
#include<stdlib.h>
int N,M,Q;
long Data[101][11];
int check[11],sun[11],count,result[11],Cnt,impo[11][11];

ofstream fout("lock1.out");
void input(void)
{
	int i,j,b;
	long a;
	ifstream in("lock1.inp");
	in >> N >> M >> Q;
	for(i = 1;i<=Q;i++){
		in >> a >> b;
		if(b > 0){
			Data[++Cnt][0] = b;
			for(j = N;j>=1;j--){
				Data[Cnt][j] = a%10;
				check[a%10] = 1;
				a/=10;
			}
		}
	}
	for(i = 1;i<=N;i++){
		for(j = 1;j<=Cnt;j++){
			impo[i][Data[j][i]] = 1;
		}
	}
}
void back(int n)
{
	int i,j,cnt,che;
	if(n <= N){
		for(i = 0;i<M;i++){
			if(check[i] == 1 && impo[n][i] == 1){
				sun[n] = i;
				back(n+1);
			}
		}
	}
	else{
		for(i = 1;i<=Cnt;i++){
			cnt = che = 0;
			for(j = 1;j<=N;j++){
				if(Data[i][j] == sun[j]){
					cnt++;
				}
			}
			if(cnt != Data[i][0]){
				che = 1;
				break;
			}
		}
		if(che == 0){
			count++;
			if(count == 1){
				for(i = 1;i<=N;i++)
					result[i] = sun[i];
			}
			else{
				fout << "-1";
				exit(1);
			}
		}
	}
}
void main(void)
{
	int i;
	input();
	back(1);
	if(count == 0){
		fout << "-1";
		exit(1);
	}
	else{
		for(i = 1;i<=N;i++)
			fout << result[i];
	}
}




