/*

   The algorithm does a breadth-first search in a graph
   always choosing the cheapest options first.
   Vertices that need to be visited are stored in a sorted
   list (sorted by the price needed to get to that vertex).
   algorithm starts by inserting the starting node in the
   list.
   One step of the algorithm does:
      - take the first element in the list - the next cheapest
        path in the graph
      - visit the vertex defined by that element
      - if the vertex was already visited then:
           - if the preavious distance was smaller - do nothing
             (because we traverse tgraph in such way that
              the preavious cost was also smaller)
      - else put all the neighbours on the list and update
        distance
   Algorithm stops when the list empties.

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 100
#define LIST_SIZE 3000
#define A_LOT 30000
#define NO -1

int number_of_coins,number_of_cities,number_of_roads;
int were[MAX_CITIES];

typedef struct {
    int money,node,distance;
} car;

car list[LIST_SIZE];
int head;

typedef struct {
    char from,to,cost,length;
} road;

road roads[MAX_CITIES * MAX_CITIES];

FILE *fp;

void read_input(void)
{
  int i;
  int c1,c2,c3,c4;

  // reading from "ROADS.IN"
  fp = fopen("ROADS.IN","rt");
  fscanf(fp,"%d %d %d",&number_of_coins,&number_of_cities,&number_of_roads);
  for (i = 0;i < number_of_cities;++i)
    were[i] = NO;
  for (i = 0;i < number_of_roads;++i) {
    fscanf(fp,"%d %d %d %d",&c1,&c2,&c3,&c4);;
    roads[i].from = c1 - 1;
    roads[i].to = c2 - 1;
    roads[i].length = c3;
    roads[i].cost = c4;
  }
  fclose(fp);
}

void initlist(void)
{
  list[0].money = A_LOT;
  list[0].node = A_LOT;
  head = 1;
  return;
}

int empty(void)
{
  return (head == 1);
}

void insert(car a)
{
  int i,j;
  i = head;
  while (list[i - 1].money <= a.money) {
    if (list[i - 1].node == a.node) {
        if (list[i - 1].distance <= a.distance)
          return;
        if ((list[i - 1].money == a.money) &&
            (a.distance < list[i - 1].distance)) {
          list[i - 1] = a;
          return;
        }
    }
    --i;
  }
  if (i == head) {
    list[i] = a;
    ++head;
    return;
  }
  for (j = head;j > i;--j)
    list[j] = list[j - 1];
  
  list[i] = a;
  ++head;
  return;
}

void first(car *a)
{
  *a = list[--head];
  return;
}

// compare function for "qsort"
int sort_func(const void *a,const void *b)
{
  if (((road *) a)->from > ((road *) b)->from)
    return 1;
  if (((road *) a)->from < ((road *) b)->from)
    return -1;
  return 0;
}

void solve(void)
{
  int i,j;
  int start[MAX_CITIES];
  car t,tmp;

  qsort(roads,number_of_roads,sizeof(roads[0]),sort_func);
  j = 0;
  for (i = 0;i < number_of_cities;++i) {
    while ((roads[j].from < i) && (j < number_of_roads))
      ++j;
    if (j == number_of_roads)
      --j;
    start[i] = j;
  }

  t.money = 0;
  t.node = 0;
  t.distance = 0;
  initlist();
  insert(t);

  while (!empty()){
    first(&t);
    if ((were[t.node] == NO) || (t.distance < were[t.node])) {
      were[t.node] = t.distance;
      for (i = start[t.node];roads[i].from == t.node;++i)
        if (t.money + roads[i].cost <= number_of_coins) {
          tmp.money = t.money + roads[i].cost;
          tmp.node = roads[i].to;
          tmp.distance = t.distance + roads[i].length;
          insert(tmp);
        }
    }
  }
}

void write_output(void)
{
  // writing to "ROADS.OUT"
  fp = fopen("ROADS.OUT","wt");
  fprintf(fp,"%d\n",were[number_of_cities - 1]);
  fclose(fp);
}

int main(void)
{
  read_input();
  solve();
  write_output();
  return 0;
}
