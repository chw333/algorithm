#include<stdio.h>
#include<conio.h>

int root = -1, n = 0;
int data[20];
int l[20],r[20];

void infix(int cur)
{
	if (cur >= 0)
	{
		printf("(");
		infix(l[cur]);
		printf("%d", data[cur]);
		infix(r[cur]);
		printf(")");
	}
	if (cur == root) printf("\n");
}

int insert(int key, int cur, int par)
{
	if (cur < 0)
	{
		n++;
		data[n] = key;
		l[n] = -1;
		r[n] = -2;
		if (par < 0)
			root = n;
		else
		{
			if (l[par] == cur)
				l[par] = n;
			else
				r[par] = n;
		}
		return 0;
 }

	if (data[cur] > key)              // key < data[cur]
		return insert(key, l[cur], cur);
	else
	if (data[cur] == key)             // key == data[cur]
		return -1;
	else
		return insert(key, r[cur], cur);     // data[cur] < key
}

int search(int cur)
{

}

void main()
{
	clrscr();
	infix(root);
	insert(10, root, -1);
	infix(root);
	insert(5, root, -1);
	infix(root);
	printf("insert 15 : %d \n", insert(15, root, -1));
	infix(root);        	printf("insert 15 : %d \n", insert(15, root, -1));
	infix(root);
}