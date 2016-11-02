#include<stdio.h>
#include<fstream.h>

static int data[200],copy[200],check[200];
int n,min=999999999,sum;

int abs(int a)
{
	if (a < 0) return a*(-1);
	else	   return a;
}

void greedy(int i)
{
	int j,k;
	for (j=0;j<n;j++){
		if (data[i] == copy[j] && i == j && check[j] == 0){
			check[j] = 1;
			break;
		}
		if (data[i] == copy[j] && check[j] == 0){
			check[j] = 1;
			k = abs(j-i);
			if (k < 0) k = 0;
			sum += (20+k);
			break;
		}
	}
}

void pro()
{
	int i,j,k,t,cnt=0,cp=0;

	while(cnt != n){
		sum = 0;
		for (i=0;i<n;i++){
			greedy(i);
		}
		if (min > sum) min = sum;

		t = data[0];
		for (i=0;i<n-1;i++){
			data[i] = data[i+1];
			check[i] = 0;
		}
		data[n-1] = t;
		check[n-1] = 0;
		cnt++;
	}

}

void sort()
{
	int i,j,t,gap,a,b;
	
	for(gap=1;gap<n/3;gap=3*gap+1);
	while(gap>0){
		for(i=gap;i<n;i=i++)
			for(j=i-gap;j>=0;j-=gap){
				if (copy[j]>copy[j+gap]){
					t = copy[j];
					copy[j] = copy[j+gap];
					copy[j+gap] = t;
				}
			}
		gap/=3;
	}
}
void input()
{
	int i;

	ifstream in ("cowsort.inp");

	in >> n;

	for (i=0;i<n;i++){
		 in >> data[i];
		 copy[i] = data[i];
	}
}

void main()
{
	ofstream out ("cowsort.out");
	input();
	sort();
	pro();
	out << min;
}