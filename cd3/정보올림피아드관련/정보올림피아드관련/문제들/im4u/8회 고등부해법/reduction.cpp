// 2002. 5 ���� "Reduction"

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_N 100
#define MAX_LEN 100

struct node{
	node *left;
	node *right;
};

int T, N;
char s[MAX_LEN * 3], res[MAX_LEN * 100];
long term_n[MAX_N+1];
int pt, res_n;
bool reform;
FILE *inf, *outf;

void input_data()
{
	fscanf(inf, "%d\n", &N);	
	fscanf(inf, "%s", s);
}

// ������ȹ���� �̿��Ͽ� �ҹ��� 1 �ذ�
void solve_1()	
{
	int i, j;

	term_n[1] = 1;

	for (i=2; i<=N; i++)
	{
		term_n[i] = 0;
		for (j=1; j<i; j++)
			term_n[i] += term_n[j] * term_n[i-j];
	}
}

// �־��� ���� Ʈ���� ǥ��
void make_tree(node *p)
{
	p->left = NULL;		
	p->right = NULL;

	while(1)
	{
		pt++;
		if (s[pt] == '(') 
			if (p->left == NULL) {
				p->left = (node *) malloc(sizeof(node));		
				make_tree(p->left);
			}
			else {
				p->right = (node *) malloc(sizeof(node));		
				make_tree(p->right);			
			}
		else if (s[pt] == ')') return;
	}
}

// ���� ���̴� �Լ�
void reduction(node *p)
{
	node *A, *B, *C;

	if (p != NULL && p->left != NULL && p->left->left != NULL)
		if (p->left->left->left == NULL)
		{
			A = p->left->left->right;
			B = p->left->right;
			C = p->right;
			p->left = (node *) malloc(sizeof(node));		
			p->left->left = A;
			p->left->right = C;
			p->right = (node *) malloc(sizeof(node));		
			p->right->left = B;
			p->right->right = C;
			reform =  true;
		}
		else reduction(p->left);
	else if (p->right != NULL) reduction(p->right);
}

// Ʈ���� traverse�Ͽ� �ٽ� ��Ʈ������ ��ȯ
void traverse_tree(node *p)
{
	if (p == NULL)
		res[res_n++] = 'X';
	else
	{
		res[res_n++] = '(';
		traverse_tree(p->left);
		traverse_tree(p->right);
		res[res_n++] = ')';
	}
}

// �ҹ��� 2
void solve_2()	
{
	node *tree = NULL;

	// ��Ʈ������ �Ǿ��ִ� ���� Ʈ���� ǥ��
	if (s[0] == '(') {
		pt = 0;
		tree = (node *) malloc(sizeof(node));		
		make_tree(tree);
	}

	// Ʈ������ ���� ������ ���� ��
	do {
		reform = false;
		reduction(tree);
	} while (reform);

	// Ʈ���� �ٽ� ��Ʈ������ ��ȯ
	res_n = 0;
	traverse_tree(tree);
	res[res_n] = '\0';
}

// ��� ���
void output_result()
{
	fprintf(outf, "%d\n", term_n[N]);
	fprintf(outf, "%s\n", res);
}

void main()
{	
	inf = fopen(INPUT_FILE, "r");
	outf = fopen(OUTPUT_FILE, "w");

	fscanf(inf, "%d\n", &T);
	
	for(int i=0; i<T; i++) {
		input_data();
		solve_1();
		solve_2();
		output_result();
	}

	fclose(inf);
	fclose(outf);
}