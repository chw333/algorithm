#include<fstream.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define Infilename "patch.inp"
#define Outfilename "patch.out"

int Input();
void Process();
void Output();

int pos(int);
void Patch(int);
void erase();

int N,M,l[101],Bug[21],count[2]={0,0},min=32767,min2=32767,sol[201],imsi[201];
long double cc=0;

char B[101][21],F[101][21];
clock_t start=clock(),end=clock();

int main(void){
	if(!Input()){
		cout<<"File not found - "<<Infilename;
		return EXIT_FAILURE;
	}
	Process();
	Output();
	return EXIT_SUCCESS;
}

int Input(){
	int a;
	ifstream fin(Infilename);
	fin>>N>>M;
	for(int i=1;i<=M;i++){
		fin>>l[i];
		fin>>B[i];
		fin>>F[i];
	}

	fin.close();
	return 1;
}

void Process(){
	int a,temp;
	randomize();
	erase();
	while((end-start)/CLK_TCK<=4.5){
		cc++;
		end=clock();
		do a=random(M)+1;while(!pos(a));
		Patch(a);
		temp=0;for(int i=1;i<=N;i++)if(Bug[i]==1)temp++;
		if(temp==0){
			if(count[1]<min||count[1]==min&&count[0]<min2){
				for(int k=1;k<=count[0];k++)
					sol[k]=imsi[k-1];
				sol[0]=count[0];
				min=count[1];
				min2=count[0];
			}
			count[1]=0;
			count[0]=0;

			erase();
		}
	}
}

void Output(){
	ofstream fout(Outfilename);
	if(min==32767){fout<<0;return;}
	fout<<min<<endl;
	for(int i=1;i<=sol[0];i++)
		fout<<sol[i]<<" ";
    cout<<cc;
	fout.close();
}

void erase(){
	for(int i=1;i<=N;i++)Bug[i]=1;
}

int pos(int n){
	for(int i=1;i<=N;i++)
		if(B[n][i-1]=='-'&&Bug[i]==1)return 0;
		else if(B[n][i-1]=='+'&&Bug[i]==0)return 0;
	return 1;
}

void Patch(int n){
	for(int i=1;i<=N;i++)
		if(F[n][i-1]=='-')Bug[i]=0;
		else if(F[n][i-1]=='+')Bug[i]=1;
	imsi[count[0]++]=n;
	count[1]+=l[n];
}