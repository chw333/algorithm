#include<fstream.h>

#define MAX 20000000

ifstream in ("juice.in");
ofstream out ("juice.out");

int e, f, m, n, p[500], w[500], d[10001];

void input(void)
{
	int i;
	in >> e >> f;
	m = f - e;
	in >> n;
	for(i = 0; i < n; i++){
		in >> p[i] >> w[i];
	}
}

void output(void)
{
	if(d[m] == MAX){
		out << "impossible";
	}
	else{
		out << d[m];
	}
}

void prs(void)
{
	int s, i, j;
	for(i = 1; i <= m; i++){
		d[i] = MAX;
	}
	d[0] = 0;
	for(i = 0; i < n; i++){
		for(j = w[i]; j <= m; j++){
			s = p[i] + d[j - w[i]];
			if(s < d[j]){
				d[j] = s;
			}
		}
	}
}

void main(void)
{
	input();
	prs();
	output();
}
