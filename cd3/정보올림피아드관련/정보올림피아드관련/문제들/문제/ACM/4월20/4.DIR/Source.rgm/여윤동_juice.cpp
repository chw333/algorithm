#include<fstream.h>

void init(void);
void process(void);
void out(void);

int money[10001];
struct {int money , weight;} juice[501];
int e , f;
int n;

void main(void){
	init();
	if(f != 0) process();
	out();
}

void init(void){
	int i;
	ifstream in("juice.in");
	in >> e >> f;
	f -= e;
	in >> n;
	for(i=1; i<=n; i++)
		in >> juice[i].money >> juice[i].weight;
}

void process(void){
	int i , j;
	int min;
	for(i=1; i<=f; i++){
		min = 999999;
		for(j=1; j<=n; j++){
			if(i - juice[j].weight < 0) continue;
			if(money[i - juice[j].weight] + juice[j].money < min) min = money[i - juice[j].weight] + juice[j].money;
		}
		money[i] = min;
	}
}

void out(void){
	ofstream op("juice.out");
	if(money[f] < 999999) op << money[f]; else op << "impossible";
}