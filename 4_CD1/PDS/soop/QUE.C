#include <stdio.h>

#define N 5

#define Push(A) { que[en] = A; en++; }
#define Pop(A) { A = que[st]; st++; }

#define Empty (st == en)
#define Full (en == N)

main()
{
	int que[N];
	int st = 0, en = 0;
	int temp;

	// Insert
	if (!Full) Push(1);

	// Delete
	if (!Empty)
	{
		Pop(temp);
		printf("%d \n", temp);
	}
}