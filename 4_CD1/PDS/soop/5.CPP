#include<stdio.h>
void(treevalk(struct tnode *p)
{
 struct connect{
	struct tnode *node;
	char *parent;
	char direct;
 }q[128],w[128];
 int i,child,n,level;

 child=1;level=0;
	[0],node=p;q[0],