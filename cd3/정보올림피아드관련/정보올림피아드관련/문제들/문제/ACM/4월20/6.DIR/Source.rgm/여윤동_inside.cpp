#include<fstream.h>

void init(void);
void process(void);
int ccw(int , int , int);
void out(void);

int n , count;
struct {int x , y;} point[22];

void main(void){
	init();
	process();
	out();
}

void process(void){
	int i , j , k;
	int cc1, cc2 , cc3;
	for(i=1; i<=n - 2; i++)
		for(j=i + 1; j<=n - 1; j++)
			for(k=j + 1; k<=n; k++){
				cc1 = ccw(i , j , n + 1);
				cc2 = ccw(j , k , n + 1);
				cc3 = ccw(k , i , n + 1);
				if(cc1 == 0 || cc2 == 0 || cc3 == 0) continue;
				if(cc1 == cc2 && cc2 == cc3) count++;
			}
}

int ccw(int from , int by , int to){
	int h;
	h = (point[from].x - point[by].x) * (point[to].y - point[by].y) - (point[from].y - point[by].y) * (point[to].x - point[by].x);
	if(h > 0) return 1; else if(h == 0) return 0; else return -1;
/*	a b 
	c d
	a* d- b* c */
}

void init(void){
	int i;
	double d;
	ifstream in("inside.in");
	in >> n;
	for(i=1; i<=n + 1; i++){
		in >> d;
		point[i].x = (int)((double)((double)d + (double)1) * (double)100);
		in >> d;
		point[i].y = (int)((double)((double)d + (double)1) * (double)100);
	}
}

void out(void){
	ofstream op("inside.out");
	op << count;
}