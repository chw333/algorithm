#include<fstream.h>
#include<stdlib.h>
#include<conio.h>

#define Infilename "lock.inp"
#define Outfilename "lock.out"

int Input();
void Process();
void Output();

int Tar[11][201],N,M,Q;
int Num[101][2]

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
	ifstream fin(Infilename);
	fin>>N>>M>>Q;
	for(int i=1;i<=Q;i++)
		fin>>Num[Q][0]>>Num[Q][1];
	fin.close();
}

void Process(){

}

void Output(){
	ofstream fout(Outfilename);
	fout.close();
}