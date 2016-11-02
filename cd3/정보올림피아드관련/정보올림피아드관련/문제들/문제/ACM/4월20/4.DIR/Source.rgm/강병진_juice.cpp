#include <fstream.h>

int e, f, n, p[1000], w[1000], d[20000], v[20000];

void input(){
	int i;
	ifstream fin ("juice.in");
	fin >> e >> f >> n;
	f -= e;
	for(i = 0 ; i < n ; i++)
		fin >> p[i] >> w[i];
	d[0] = 0;
	for(i = 1 ; i <= 10000 ; i++){ d[i] = 2000000000; v[i] = -1; }
}

void process(){
	int i, j;

	for(i = 1 ; i <= f ; i++)
		for(j = 0 ; j < n ; j++)
			if(i >= w[j])
				if(d[i] > d[i - w[j]] + p[j]){
					v[i] = i - w[j];
					d[i] = d[i - w[j]] + p[j];
				}
}

void output(){
	int i;
	i = f;
	for(;;){
		i = v[i];
		if(i == -1) break;
		if(i == 0) break;
	}
	ofstream fout ("juice.out");
	if(i == 0) fout << d[f]; else fout << "impossible";
}

void main(){
	input();
	process();
	output();
}