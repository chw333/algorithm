#include<fstream.h>

int N,M;
int Arr[100][100];
int distence[100],path[100];
int visit[100];
int input1[100],input2[100],input3[100];

void init()
{
	int i;

	ifstream in("secret.in");
	in >> N >> M;
	for(i=0; i<M; i++){
		in >> input1[i] >> input2[i] >> input3[i];
	}
}

void make_arr()
{
	int i,j;

	for(i=0; i<M; i++){
		Arr[input1[i]-1][input2[i]-1]=input3[i];
		Arr[input2[i]-1][input1[i]-1]=input3[i];
	}
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(Arr[i][j]==0) Arr[i][j]=9999;
		}
	}
}

void first_small_tree()
{
	int i,j,min,index=0,cnt=0;

	for(i=0; i<N; i++){
		distence[i]=Arr[0][i];
	}
	visit[0]=1;
	for(i=0; i<N; i++){
		min=9999;
		for(j=0; j<N; j++){
			if(min>distence[j] && visit[j]==0){
				min=distence[j];
				index=j;
			}
		}
		visit[index]=1;
		for(j=0; j<N; j++){
			if(distence[j]>Arr[index][j] && visit[j]==0){
				distence[j]=Arr[index][j];
				path[j]=index;
			}
		}
	}
}

void output()
{
	int i,sum=0;

	for(i=0; i<N; i++){
		if(distence[i]!=9999) sum+=distence[i];
	}
	ofstream out("secret.out");
	out << sum+1;
}

void main()
{
	init();
	make_arr();
	first_small_tree();
	output();
}