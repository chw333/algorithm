// IOI2002 2002. 7 마지막 자리수(last digit)

#include <stdio.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

int a[20] = {0, 1, 4, 7, 6, 5, 6, 3, 6, 9, 0, 1, 6, 3, 6, 5, 6, 7, 4, 9};
int res[100];
int T, N;
FILE *inf, *ouf;

void Solve()
{
	int i;
	int sum = 0;

	for (i=0; i<=99; i++)
	{
		sum += a[i%20];
		res[i] = sum % 10;
	}
}

void Input_data()
{
	char p = '0', q = '0', r;

	fscanf(inf, "%c", &r);

	while (!feof(inf) && (r != '\n'))
	{
		p = q;
		q = r;
		fscanf(inf, "%c", &r);
	}

	N = (p - 48) * 10 + (q - 48);
}

void Output_result()
{
	fprintf(ouf, "%d\n", res[N]);
}

void main()
{	
	inf = fopen(INPUT_FILE, "r");
	ouf = fopen(OUTPUT_FILE, "w");

	Solve();

	fscanf(inf, "%d\n", &T);
	
	for(int i=0; i<T; i++) {
		Input_data();
		Output_result();
	}

	fclose(inf);
	fclose(ouf);
}