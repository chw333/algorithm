// 2002. 5 "Split"

#include <stdio.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_N 10000

int T, N;
int num[2][MAX_N];
int split_n;
FILE *inf, *outf;

void input_data()
{
	fscanf(inf, "%d\n", &N);	

	for (int i=0; i<N; i++)
		fscanf(inf, "%d", &num[0][i]);	
}

void solve()	
{
	int sw = 0;
	split_n = -1;
	int i, j;
	bool possible = true;

	while (possible)
	{
		num[1-sw][N-2] = num[sw][N-1];
		
		for (i=N-4; i>=0; i-=2)
			num[1-sw][i] = num[sw][i+1] - num[1-sw][i+2];
		
		j = i + 2;
		j = 1 - j;
		num[1-sw][j] = num[sw][0] - num[1-sw][1-j];

		for (i=j+2; i<N; i+=2)
			num[1-sw][i] = num[sw][i-1] - num[1-sw][i-2];

		split_n++;
		sw = 1-sw;		

		for (i=0; i<N; i++)
			if (num[sw][i] < 0) possible = false;
	}

	if (split_n == 0) split_n = -1;
}

void output_result()
{
	fprintf(outf, "%d\n", split_n);
}

void main()
{	
	inf = fopen(INPUT_FILE, "r");
	outf = fopen(OUTPUT_FILE, "w");

	fscanf(inf, "%d\n", &T);
	
	for(int i=0; i<T; i++) {
		input_data();
		solve();
		output_result();
	}

	fclose(inf);
	fclose(outf);
}