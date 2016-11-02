#include <fstream.h>
#include <time.h>

char s[1000][1000];
int c, r, map[1000][1000], tot = 0;

void input(){
	int i, j;
	ifstream fin ("animal.in");
	fin >> c >> r;
	for(i = 1 ; i <= r ; i++)
		for(j = 1; j <= c ; j++)
			fin >> s[i][j];
	for(i = 0 ; i <= r + 1 ; i++) s[i][0] = s[i][c + 1] = '#';
	for(i = 1 ; i <= c ; i++) s[0][i] = s[r + 1][i] = '#';
}

void intl(){
	int i, j;
	for(i = 1 ; i <= r ; i++)
		for(j = 1 ; j <= c ; j++)
			map[i][j] = -1;
}

int scan(){
	int i, j, d = 1, flag;
	for(;;){
		flag = 0;
		for(i = 1 ; i <= r ; i++)
			for(j = 1 ; j <= c ; j++)
				if(map[i][j] == d - 1){
					if(s[i - 1][j] != '#' && map[i - 1][j] == -1){ map[i - 1][j] = d; flag = 1; }
					if(s[i + 1][j] != '#' && map[i + 1][j] == -1){ map[i + 1][j] = d; flag = 1; }
					if(s[i][j - 1] != '#' && map[i][j - 1] == -1){ map[i][j - 1] = d; flag = 1; }
					if(s[i][j + 1] != '#' && map[i][j + 1] == -1){ map[i][j + 1] = d; flag = 1; }
				}
		if(flag == 0) break;
		d++;
	}
	return d;
}

void process(){
	int i, j, ch, cnt;
	for(i = 1 ; i <= r ; i++){
		for(j = 1 ; j <= c ; j++){
			if(s[i][j] == '.'){
				ch = 0;
				if(s[i - 1][j] == '#' && s[i][j - 1] == '#') ch = 1;
				else if(s[i - 1][j] == '#' && s[i][j + 1] == '#') ch = 1;
				else if(s[i + 1][j] == '#' && s[i][j - 1] == '#') ch = 1;
				else if(s[i + 1][j] == '#' && s[i][j + 1] == '#') ch = 1;				
				if(ch == 1){
					intl();
					map[i][j] = 0;
					cnt = scan();
					if(cnt > tot) tot = cnt;
				}
			}
		}
	}
}

void output(){
	ofstream fout ("animal.out");
	fout << tot - 1;
}

void main(){
	input();
	process();
	output();
}