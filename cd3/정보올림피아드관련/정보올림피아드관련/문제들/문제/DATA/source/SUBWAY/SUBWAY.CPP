#include <fstream.h>
#include <iostream.h>
#include <process.h>

#define MAX 100
ifstream in ("subway0.in");
ofstream out ("subway0.out");

int T[MAX][MAX]={0,};
int MRoot=0;
int Near[MAX];
int M, N;

void input()
{
	int i, j;
	in>>M>>N;
	for(i=0;i<M;i++) {
		for(j=0;j<M;j++) {
			in>>T[i][j];
		}
	}
}
void output()
{
   int p,i;
   int index[MAX];
   int cnt=0;
   p=N-1;
   out<<MRoot<<endl;
   index[cnt++]=N;
   while(Near[p]!=-1){
	  index[cnt++]=Near[p]+1;
	  p=Near[p];
   }
   cnt--;
   for(i=cnt;i>=0;i--) {
	  out<<index[i]<<" ";
   }
}
void init()
{
   int i;

   for(i=0;i<M;i++){
	  Near[i]=-1;
   }
}
void proc()
{
   int i,j,min,length[MAX],check[MAX],p;

   for(i=0;i<M;i++){
	  length[i]=999;
	  check[i]=0;
   }
   length[0]=0;
   Near[0]=-1;
   for(j=0;j<M;j++){
	  min=999;
	  for(i=0;i<M;i++){
		 if(check[i]==0 && length[i]<min){
			p=i; min=length[i];
		 }
	  }
	  check[p]=1;
	  if(min==999){
		 out<<"No Pass";
		 exit(0);
	  }
	  for(i=0;i<M;i++){
		if(length[p]+T[p][i]<length[i]){
		   length[i]=length[p]+T[p][i];
		   Near[i]=p;
		}
	  }
   }
   MRoot=length[N-1];
}
void main()
{
   input();
   init();
   proc();
   output();
}