#include <fstream.h>

#define novisit -9999999
ifstream in("gugan.in");
ofstream out("gugan.out");
int N,M;
int data[1000];
int table[1000][1000];
int result;

void input()
{
	in >> N >> M;

	for(int i=1;i<=N;i++) in >> data[i];
}

void output()
{
	out << result;
}

int memoryf(int i, int j) // from 1 to i, j group
{
	int k;
	int sum=0;

	if(j==0) return 0;
	if(table[i][j]==novisit){
		if(i!=j*2-1) {
			table[i][j]=memoryf(i-1,j);
		} 
		for(k=i;k>=j*2-1;k--){
			sum=sum+data[k];
			if(sum+memoryf(k-2,j-1)>table[i][j]){
					table[i][j]=sum+memoryf(k-2,j-1);
			}
		}
	}
	return (table[i][j]);
}

void proc()
{
	int s,ss;
	for(s=1;s<=N;s++)
		for(ss=1;ss<=M;ss++)
			table[s][ss]=novisit;
	result=memoryf(N,M); // M group, N data
}

void main()
{
	input();
	proc();
	output();
}