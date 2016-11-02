#include <stdlib.h>
#include <stdio.h>

#define INFILE "quadtree05.in"
#define OUTFILE "quadtree05.out"
#define MAX 2048

extern unsigned _stklen=16384u;

#define WHITE 0
#define BLACK 1
#define INTER 2

typedef struct node
{
  int type;
  struct node *c1, *c2, *c3, *c4;
} NODE;

int N;
NODE *tree_a, *tree_b;

int nodes;

char line[MAX];
char *lptr;

NODE *read_tree(void)
{
  NODE *node;
  char ch;
  node=(NODE *)malloc(sizeof(NODE));

  ch=*lptr++;
  switch(ch)
  {
    case 'w': node->type=WHITE; break;
    case 'b': node->type=BLACK; break;
    case 'i': node->type=INTER;
              node->c1=read_tree();
              node->c2=read_tree();
              node->c3=read_tree();
              node->c4=read_tree(); break;
  }
  return node;
}

void input(void)
{
  FILE *f;
  f=fopen(INFILE, "rt");
  fscanf(f, "%d\n", &N);
  fgets(line, sizeof(line), f); lptr=line;
  tree_a=read_tree();
  fgets(line, sizeof(line), f); lptr=line;
  tree_b=read_tree();
  fclose(f);
}

int traverse(NODE *a, NODE *b)
{
  int x, y, z, t;
  nodes++;
  if(a->type!=INTER && b->type !=INTER)
    return a->type && b->type;
  if(a->type!=INTER)
  {
    x=traverse(a, b->c1);
    y=traverse(a, b->c2);
    z=traverse(a, b->c3);
    t=traverse(a, b->c4);
  }
  else if(b->type!=INTER)
  {
    x=traverse(a->c1, b);
    y=traverse(a->c2, b);
    z=traverse(a->c3, b);
    t=traverse(a->c4, b);
  }
  else
  {
    x=traverse(a->c1, b->c1);
    y=traverse(a->c2, b->c2);
    z=traverse(a->c3, b->c3);
    t=traverse(a->c4, b->c4);
  }
  if(x==y && y==z && z==t && t!=INTER)
  {
    nodes-=4;
    return x;
  }
  return INTER;
}

void solve(void)
{
  traverse(tree_a, tree_b);
}

void output(void)
{
  FILE *f;
  f=fopen(OUTFILE, "wt");
  fprintf(f, "%d\n", nodes);
  fclose(f);
}

main(void)
{
  input();
  solve();
  output();
  return 0;
}