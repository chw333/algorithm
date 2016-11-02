#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFILE "street05.in"
#define OUTFILE "street05.out"
#define MAXNODE 50

typedef int matrix[MAXNODE][MAXNODE];

matrix A, B;
int N, S, weight[MAXNODE], paths[MAXNODE];

void calcweight(void)
{
    int i, j;
    for (i=0; i<N; i++) for (j=0; j<N; j++) weight[i] += A[i][j] - A[j][i];
}

int *mulmatrix(matrix A, matrix B)
{
    matrix C;
    int i, j, k;
    memset(C, 0, sizeof(C));
    for (i=0; i<N; i++)
		for (j=0; j<N; j++)
			for (k=0; k<N; k++)
				C[i][j] += A[i][k] * B[k][j];
    return (int *)memcpy(A, C, sizeof(C));
}

int cdecl intcmp(const void *a, const void *b)
{
    return *((int *) a) - *((int *) b);
}

void cdecl main(void)
{
    FILE *fin, *fout;
    int i, j, carry = 0;

    fin = fopen(INFILE, "rt");
    fscanf(fin, "%i\n%i\n", &N, &S);
    for (i=0; i<N; i++) for (j=0; j<N; j++) fscanf(fin, "%i", &A[i][j]);
    fclose(fin);
    memcpy(B, A, sizeof(B));

    calcweight();
    for (i=0; i<N; i++)
      if (!weight[i]) continue;
      else if (abs(weight[i]) == 1)
        if (!carry) carry = weight[i];
        else if (!(carry + weight[i])) carry = 2;
        else { carry = 3; break; }
      else { carry = 3; break; }

    fout = fopen(OUTFILE, "wt");
    if ((!carry) || (carry == 2)) {
        fprintf(fout, "YES\n");
        if (!carry) fprintf(fout, "%i\n", N);
        else fprintf(fout, "1\n");
    } else fprintf(fout, "NO\n");
    for (i=1; i<S; i++) mulmatrix(A, B);
    for (i=0; i<N; i++) paths[i] = A[i][i];
    qsort(paths, N, sizeof(int), intcmp);
    for (i=0; i<N; i++) fprintf(fout, "%i ", paths[i]);
    fprintf(fout, "\n");
    fclose(fout);
}
