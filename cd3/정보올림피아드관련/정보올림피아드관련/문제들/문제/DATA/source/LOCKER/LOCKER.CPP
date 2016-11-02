#include <fstream.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
ifstream in("locker4.in");
ofstream out("locker4.out");

char indata[100];
char A[10];
char B[10];
char B2[10];
char C[10];
char D[10];
int door[101];
void input()
{
	int i,j,k;
	int cnt=0;
	in >> indata;
	for(i=0;i<strlen(indata);i++){
		switch(indata[i]){
			case 'A':
				j=1;
				while(!isalpha(indata[i+j]) && indata[i+j]){
					A[j-1]=indata[i+j];
					j++;
				}
				A[j-1]='\0';
				break;
			case 'B':
				j=1;
				while(!isalpha(indata[i+j]) && indata[i+j]){
					if(indata[i+j]=='-') {
						k=1;
						while(!isalpha(indata[i+j+k]) && indata[i+j+k]){
							B2[k-1]=indata[i+j+k];
							k++;
						}
						B2[k-1]='\0';
						break;
					}
					B[j-1]=indata[i+j];
					j++;
				}
				B[j-1]='\0';
				break;
			case 'C':
				j=1;
				while(!isalpha(indata[i+j]) && indata[i+j]){
					C[j-1]=indata[i+j];
					j++;
				}
				C[j-1]='\0';
				break;
			case 'D':
				j=1;
				while(!isalpha(indata[i+j]) && indata[i+j]){
					D[j-1]=indata[i+j];
					j++;
				}
				D[j-1]='\0';
				break;
		}
	}
}
void output()
{
	int i;
	int ans=0;

	for(i=1;i<=100;i++) {
		if(door[i]==1) ans=ans+1;
	}
	out << ans;
}
void proc()
{
	int i;
	door[atoi(A)]=1-door[atoi(A)]; 
	for(i=atoi(B);i<=atoi(B2);i++){
		door[i]=1-door[i];
	}
	for(i=1;i<=100;i++) {
		if(i%atoi(C)==0) door[i]=1-door[i];
		if(atoi(D)%i==0) door[i]=1-door[i];
	}
}

void main()
{
	input();
	proc();
	output();
}