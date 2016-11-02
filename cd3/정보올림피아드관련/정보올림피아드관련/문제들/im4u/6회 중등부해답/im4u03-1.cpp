// 2002. 3 "Hanoi"

#include <stdio.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_N 100
#define MAX_K 40

int N;
int m;
int k[MAX_K], k_num;
char k_str[MAX_K];
int bin[MAX_N];
int res[3];
FILE *inf, *outf;

void initialize_res()
{
	res[0] = 0;	res[1] = 0;	res[2] = 0;
}
		
void trans_to_binary()
{
	int st, b_pt;
	int i;

	k_num = 0;
	for(i=0; i<(signed)strlen(k_str); i++)
		k[k_num++] = (int)k_str[i] - 48;

	st = 0;		b_pt = 100;

	while(1) {
		for(i=st; i<k_num-1; i++) {
			k[i+1] += (k[i] % 2) * 10;
			k[i] = k[i] / 2;
		}
		bin[--b_pt] = k[k_num-1] % 2;
		k[k_num-1] = k[k_num-1] / 2;

		while (k[st] == 0) {
			st++;
			if (st == k_num) return;
		}
	}
}

void solve()	
{
	int i;
	int a = 0, b = 1, c = 2;
	int temp;

	for(i=MAX_N-m; i<MAX_N; i++)
		if (bin[i]) {
			res[c]++;
			temp = a;	a = b;	b = temp;
		}
		else {
			res[a]++;
			temp = b;	b = c;	c = temp;
		}
}

void output_result()
{
	fprintf(outf, "%d %d %d\n", res[0], res[1], res[2]);
}

void main()
{	
	int i;	

	inf = fopen(INPUT_FILE, "r");
	outf = fopen(OUTPUT_FILE, "w");

	fscanf(inf, "%d\n", &N);
	
	for(i=0; i<N; i++) {
		initialize_res();
		fscanf(inf, "%d %s", &m, k_str);
		trans_to_binary();
		solve();
		output_result();
	}

	fclose(inf);
	fclose(outf);
}