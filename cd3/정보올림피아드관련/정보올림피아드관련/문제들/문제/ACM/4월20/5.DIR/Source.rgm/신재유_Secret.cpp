#include<fstream.h>
#include<stdlib.h>

ifstream in ("secret.in");
ofstream out ("secret.out");

int n, m, data[20000][3], check[2000], index[20000], min;

int sort_function(const void *a, const void *b)
{
	int *p = (int *) a, *q = (int *) b;
	if(data[*p][2] > data[*q][2]){
		return 1;
	}
	if(data[*p][2] < data[*q][2]){
		return -1;
	}
	return 0;
}

void input(void)
{
	int i;
	in >> n >> m;
	for(i = 0; i < m; i++){
		in >> data[i][0] >> data[i][1] >> data[i][2];
		data[i][0]--;
		data[i][1]--;
		index[i] = i;
	}
	qsort(index, m, sizeof(index[0]), sort_function);
}

void output(void)
{
	out << min;
}

void check_chainge(int a, int b)
{
	int imsi, i;
	if(a > b){
		imsi = a;
		a = b;
		b = imsi;
	}
	for(i = 0; i < n; i++){
		if(check[i] == b){
			check[i] = a;
		}
	}
}

void kruscal(void)
{
	int i, j, imsi, s, chk = 0;
	min = 0;
	for(i = 0; i < n; i++){
		check[i] = i + 1;
	}
	for(i = 0; i < m; i++){
		if(check[data[index[i]][0]] != check[data[index[i]][1]]){
			check_chainge(check[data[index[i]][0]], check[data[index[i]][1]]);
			chk++;
			min += data[index[i]][2];
		}
		imsi = 1;
		s = check[0];
		for(j = 1; j < n; j++){
			if(check[j] == s){
				imsi++;
			}
		}
		if(imsi == n){
			break;
		}
		if(chk == n - 2){
			s = index[i + 1];
			for(j = i + 1; j < m - 1; j++){
				index[j] = index[j + 1];
			}
			index[m - 1] = s;
		}
	}
}

void chainge(void)
{
}

void main(void)
{
	input();
	kruscal();
	chainge();
	output();
}