#include<fstream.h>
#include<math.h>

void init(void);
bool process(void);
void out(void);

int x , y , x2 , y2;
int count;
int n;
ofstream op("spy.out");

void main(void){
	init();
	out();
}

void init(void){
	int i;
	ifstream in("spy.in");
	in >> n;
	for(i=1; i<=n; i++){
		in >> x >> y >> x2 >> y2;
		if(process()) count++;
	}
}

bool process(void){
	double dis1 = (double)((double)x2 + (double)y2);
	double dis2 = sqrt(pow(x , 2) + pow(y , 2));
	if((double)dis2 > (double)dis1 || (x > x2 && y > y2) || (x > y2 && y > x2)) return 1; else return 0;
}

void out(void){
	op << count;
}