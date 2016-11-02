#include<fstream.h>
#include<math.h>

ifstream in ("spy.in");
ofstream out ("spy.out");

void main(void)
{
	int a, b, x, y, S;
	long double S2;
	int n, i, cnt = 0;
	in >> n;
	for(i = 0; i < n; i++){
		in >> a >> b >> x >> y;
		if(a > x && b > y){
			cnt++;
			continue;
		}
		if(a > y && b > x){
			cnt++;
			continue;
		}
		S = a * a + b * b;
		S2 = (long double) sqrt(S);
		if(x + y < S2){
			cnt++;
			continue;
		}
	}
	out << cnt;
}