// 2002. 3 "Super Snooker"

#include <stdio.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_NUM 1000
#define MAX_BALL 25
#define MAX_K MAX_NUM * MAX_BALL / 2

int N;
int pt1, pt2, st, en;
int k[MAX_K+1];
int res;
FILE *inf, *outf;

int find_target()
{
	int i;
	int sum;

	sum = pt1 + pt2;
	for(i=st; i<=en; i++)
		sum += i;
	
	if (sum%2) res = 0;
	if (pt1>pt2) return sum/2-pt1;
	else  return sum/2-pt2;
}

void solve()	
{
	int i, j;
	int target;

	res = 1;
	target = find_target();
	if (!res) return;

	k[0] = 1;
	for (i=1; i<=target; i++)
		k[i] = 0;

	for (i=st; i<=en; i++) {
		if (k[target]) return;
		for (j=target-i; j>=0; j--)
			if (k[j]) k[j+i] = 1;
	}

	if (!k[target]) res = 0;
}

void output_result()
{
	fprintf(outf, "%d\n", res);
}

void main()
{	
	int i;
	
	inf = fopen(INPUT_FILE, "r");
	outf = fopen(OUTPUT_FILE, "w");

	fscanf(inf, "%d\n", &N);
	
	for(i=0; i<N; i++) {
		fscanf(inf, "%d %d %d %d", &pt1, &pt2, &st, &en);
		solve();
		output_result();
	}

	fclose(inf);
	fclose(outf);
}