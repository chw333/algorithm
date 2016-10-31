#include<math.h>
#include<stdio.h>
#include<fstream.h>
#define MAX 30001

int n,x[MAX],y[MAX],i,j,k,ti,tj;

void input(void)
{
	ifstream in("tilt.inp");
	in>>n;
	for(i=0;i<n;i++)
		in>>x[i]>>y[i];
}

void shell_sort(void)
{
	int gap,i,j,k,t;
	gap=n/2+1;
	while(gap>0){
		for(k=0;k<gap;k++){
			for(i=k+gap;i<=n;i=i+gap){
				for(j=i-gap;j>=k;j=j-gap){
					if(x[j]>x[j+gap]){
						t=x[j]; x[j]=x[j+gap]; x[j+gap]=t;
						t=y[j]; y[j]=y[j+gap]; y[j+gap]=t;
					}
					else break;
				}
			}
		}
		gap=gap/2;
	}
}

void process(void)
{
	
	double ttt,max=-9999;
	for(i=1;i<=n-1;i++){
		if(x[i+1]-x[i]!=0){
			ttt=abs(y[i+1]-y[i])/(double)(x[i+1]-x[i]);
			if(ttt>max){
				max=ttt;
				ti=i; tj=i+1;
			}
		}
	}
}

void main(void)
{	input();
	shell_sort();
	process();
	ofstream out("tilt.out");
	out<<x[ti]<<" "<<y[ti]<<" "<<x[tj]<<" "<<y[tj];
}

