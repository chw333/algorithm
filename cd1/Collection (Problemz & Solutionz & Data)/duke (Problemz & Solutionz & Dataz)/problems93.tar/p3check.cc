#include <stdlib.h>
#include <iostream.h>
#include <strstream.h>

const int MAX_STACK = 31;

struct Pancake{
    int stack[MAX_STACK];
    int numCakes;
};


int ReadCakes(Pancake &);
void FlipCakes(Pancake &);

main()
{
    Pancake p;

    while (ReadCakes(p)){
	FlipCakes(p);
    }
    exit(EXIT_SUCCESS);
}

int
ReadCakes(Pancake & p)
{
    char buf[1024];
    p.numCakes = 0;
    if (cin.getline(buf,1024)){
	istrstream input(buf);
	int diam;
	while (input >> diam){
	    p.stack[p.numCakes] = diam;
	    p.numCakes++;
	}
	return 1;
    }
    else{
	return 0;
    }
}

int IsSorted(const Pancake & p)
{
    int k;
    for(k=0; k < p.numCakes - 1;k++){
	if (p.stack[k] > p.stack[k+1]){
	    return 0;
	}
    }
    return 1;
}

int MaxIndex(const Pancake & p, int last)
{
    int max = 0;
    int k;
    for(k=1; k < last; k++){
	if (p.stack[k] > p.stack[max]){
	    max = k;
	}
    }
    return max;
}

void
FlipStack(Pancake & p, int index)
// pre: 0 <= index < p.numCakes     
// post: reverse pancakes from 0 --> index
{
    int temp;
    int mid = index/2;
    int k;
    for(k=0; k <= mid; k++){
	temp = p.stack[k];
	p.stack[k] = p.stack[index-k];
	p.stack[index-k] = temp;
    }
}

void
FlipCakes(Pancake & p)
{
    char buf[100];
    int flip;
    while (cin >> flip && flip != 0){
	if (IsSorted(p)){
	    cerr << "sorted prematurely" << endl;
	    exit(EXIT_FAILURE);
	}
	FlipStack(p,p.numCakes - flip);
    }
    if (!IsSorted(p)){
	cerr << " not sorted at end " << endl;
	exit(EXIT_FAILURE);
    }
    cin.getline(buf,100);
    
}
