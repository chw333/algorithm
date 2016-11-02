#include <fstream.h>
#include <math.h>

int sq(int x){
	return x * x;
}

void main(){
	int i, n, lightx, lighty, kitx, kity, cnt = 0;
	ifstream fin ("spy.in");
	fin >> n;
	for(i = 0 ; i < n ; i++){
		fin >> lightx >> lighty >> kitx >> kity;
		if((lightx > kitx && lighty > kity) || (lightx > kity && lighty > kitx) || sqrt(sq(lightx) + sq(lighty)) > sqrt(sq(kitx) + sq(kity))) cnt++;
	}	
	ofstream fout ("spy.out");
	fout << cnt;
}