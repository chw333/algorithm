#include <fstream.h>
#define ccw(ax, ay, bx, by, cx, cy) ((bx - ax) * (cy - ay) - (by - ay) * (cx - ax))

int n, cnt = 0;
double dotbx[20], dotby[20], dotrx, dotry;

void input(){
	int i;
	ifstream fin ("inside.in");
	fin >> n;
	for(i = 0 ; i < n ; i++)
		fin >> dotbx[i] >> dotby[i];
	fin >> dotrx >> dotry;
}

int check(int first, int second, int third){
	double ch1, ch2, ch3;
	ch1 = ccw(dotbx[first], dotby[first], dotbx[second], dotby[second], dotrx, dotry);
	ch2 = ccw(dotbx[second], dotby[second], dotbx[third], dotby[third], dotrx, dotry);
	ch3 = ccw(dotbx[third], dotby[third], dotbx[first], dotby[first], dotrx, dotry);
	if((ch1 > 0 && ch2 > 0 && ch3 > 0) || (ch1 < 0 && ch2 < 0 && ch3 < 0)) return 1;
	return 0;
}

void process(){
	int i, j, k;
	for(i = 0 ; i < n - 2 ; i++)
		for(j = i + 1 ; j < n - 1 ; j++)
			for(k = j + 1 ; k < n ; k++)
				if(check(i, j, k))
					cnt++;
}

void output(){
	ofstream fout ("inside.out");
	fout << cnt;
}

void main(){
	input();
	process();
	output();
}