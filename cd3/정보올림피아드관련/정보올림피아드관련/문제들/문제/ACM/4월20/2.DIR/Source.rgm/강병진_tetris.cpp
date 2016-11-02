#include <fstream.h>

int kr, kc, lr, lc, ks[100][100], ls[301][300], depth = 0;

void input(){
	int i, j;
	char c;
	ifstream fin ("tetris.in");
	fin >> kr >> kc;
	for(i = 0 ; i < kr ; i++)
		for(j = 0 ; j < kc ; j++){
			fin >> c;
			if(c == '#') ks[i][j] = 1;
			else ks[i][j] = 0;
		}
	fin >> lr >> lc;
	for(i = kr ; i < lr + kr ; i++)
		for(j = 0 ; j < lc ; j++){
			fin >> c;
			if(c == '#') ls[i][j] = 1;
			else ls[i][j] = 0;
		}
	lr += kr;
}

void process(int d){
	int i, j, k, ch;
	depth = d;
	if(d == lr + kr)
		depth = 999;
	else{
		for(i = 0 ; i < lc - kc + 1 ; i++){
			ch = 0;
			for(j = d ; j < d + kr ; j++)
				for(k = i ; k < i + kc ; k++)
					if(ls[j][k] + ks[j - d][k - i] == 2) ch = 1;
			if(ch == 0){
				for(j = d ; j < d + kr ; j++)
					for(k = i ; k < i + kc ; k++)
						if(ks[j - d][k - i] == 1 && ls[j + 1][k] == 1) ch = 1;
				if(ch == 0){
					process(d + 1);
					break;
				}
			}
		}
	}
}

void output(){
	ofstream fout ("tetris.out");
	if(depth == 999) fout << "pass";
	else fout << depth;
}

void main(){
	input();
	process(0);
	output();
}