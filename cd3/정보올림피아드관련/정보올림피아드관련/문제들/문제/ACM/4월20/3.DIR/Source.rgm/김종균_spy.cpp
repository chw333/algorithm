#include <fstream.h>
#include <math.h>
#include <stdlib.h>

int spy[400][4],n,cnt;

void input()
{
	int i,j,imsi;
	ifstream in("spy.in");
	in >> n;
	for(i=0;i<n;i++){
		for(j=0;j<4;j++)
			in >> spy[i][j];
		if(spy[i][0]>spy[i][1]){
			imsi=spy[i][1]; spy[i][1]=spy[i][0]; spy[i][0]=imsi;
		}
		if(spy[i][2]>spy[i][3]){
			imsi=spy[i][3]; spy[i][3]=spy[i][2]; spy[i][2]=imsi;
		}
	}
	in.close();
}
void play()
{
	int i;
	for(i=0;i<n;i++)
	{
		
		if(spy[i][0]<spy[i][2] && spy[i][1]<spy[i][3]){	cnt++; continue;}
		else if( (pow(spy[i][2],2)+pow(spy[i][3],2))*2 > spy[i][1]*2+spy[i][1])cnt++;
	}
}
void output()
{
}
void main()
{
	input();
	play();
	output();
}
