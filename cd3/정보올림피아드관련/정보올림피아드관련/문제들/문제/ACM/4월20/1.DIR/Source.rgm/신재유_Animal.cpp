#include<fstream.h>
#include<stdlib.h>
#include<time.h>

ifstream in ("animal.in");
ofstream out ("animal.out");

int k[1000001];

void main(void)
{
	int a, b, c, d, e, f, i, j;
	char i_data[100];
	srand((unsigned)time(NULL));
	in >> a >> b;
	c = 0;
	for(i = 0; i < a; i++){
		in >> i_data;
		for(j = 0; j < b; j++){
			if(i_data[j] == '.'){
				c++;
			}
		}
	}
	for(i = 0; i < 1000000; i++){
		d = rand() % c;
		k[d]++;
	}
	e = 0;
	for(i = 0; i < c; i++){
		if(e < k[i]){
			e = k[i];
			f = i;
		}
	}
	out << f;
}