// IOI2002 2002. 6 초중등부 침몰하는 배(sinking)

#include <stdio.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_M 100
#define MAX_N 100
#define MAX MAX_M * MAX_N

int M, N, A;
int T[MAX_M][MAX_N], TT[MAX_M][MAX_N];
int path[MAX_M][MAX_N];
char dir[5] = { ' ', 'U', 'L', 'R', 'D' };
int res_n, res_y, res_x;
char res[MAX];
bool found;
int stx, sty;
int q[MAX][2];
int rear, front;

void Input_data()
{
	int i, j;
	char ch;
	FILE *inf;

	inf = fopen(INPUT_FILE, "r");

	fscanf(inf, "%d %d %d\n", &M, &N, &A);	

	for (i=0; i<M; i++)
	{
		for (j=0; j<N; j++)
		{
			fscanf(inf, "%c", &ch);
			if (ch == 'F') T[i][j] = MAX;
			if (ch == 'Y') {
				sty = i;	stx = j;
			}
			if (ch == 'S') T[i][j] = -1;
		}
		fscanf(inf, "\n");
	}

	fclose(inf);
}

void insert(int y, int x, int dir, int count)
{
	rear++;
	q[rear][0] = y;	q[rear][1] = x;
	if (T[y][x] == -1) {
		found = true;		res_y = y;		res_x = x;
	}
	T[y][x] = count;
	path[y][x] = dir;
}

void remove(int &y, int &x)
{
	y = q[front][0];	x = q[front][1];
	front++;
}

void sink()
{
	int i, j;

	for (i=0; i<M; i++)
		for (j=0; j<N; j++)
			if (T[i][j] == MAX)
			{
				if (i>0) TT[i-1][j] = MAX;
				if (j>0) TT[i][j-1] = MAX;
				if (i<M-1) TT[i+1][j] = MAX;
				if (j<N-1) TT[i][j+1] = MAX;
			}

	for (i=0; i<M; i++)
		for (j=0; j<N; j++)
			if (TT[i][j] == MAX) T[i][j] = MAX;
}

void Solve()
{
	int y, x;
	int bound;
	int count = 0;

	insert(sty, stx, 0, count+1);
	
	bound = rear+1;		

	while (rear>=front)
	{
		remove(y, x);

		if (front > bound)
		{
			count++;
			if ((count > A) && ((count-1) % A == 0)) sink();
			bound = rear+1;
		}

		if (T[y][x] == MAX) continue;
		if ((y>0) && (T[y-1][x] <= 0)) insert(y-1, x, 4, count+2);
		if ((y<M-1) && (T[y+1][x] <= 0)) insert(y+1, x, 1, count+2);
		if ((x>0) && (T[y][x-1] <= 0)) insert(y, x-1, 3, count+2);
		if ((x<N-1) && (T[y][x+1] <= 0)) insert(y, x+1, 2, count+2);

		if (found) {
			res_n = count+1;	break;
		}
	}
}

void next(int &y, int &x)
{
	switch (path[y][x])
	{
		case 1 : y--;	break;
		case 2 : x--;	break;
		case 3 : x++;	break;
		case 4 : y++;
	}
}

void Output_result()
{
	int i;
	FILE *ouf;

	ouf = fopen(OUTPUT_FILE, "w");

	if (!found) fprintf(ouf, "Impossible\n");
	else
	{
		fprintf(ouf, "%d\n", res_n);
		res[res_n] = '\0';
		for (i=res_n-1; i>=0; i--)
		{			
			res[i] = dir[5-path[res_y][res_x]];
			next(res_y, res_x);
		}

		fprintf(ouf, "%s\n", res);
	}

	fclose(ouf);
}

void main()
{
	Input_data();
	Solve();
	Output_result();
}