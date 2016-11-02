#include <iostream.h>
#include <strstream.h>

// author: Owen Astrachan
// for internet programming contest 1993 (problem 3)

const int MAX_STACK = 35;

struct Pancake{
    int stack[MAX_STACK];
    int numCakes;
};


int ReadCakes(Pancake &);
void FlipCakes(Pancake &);
void WriteCakes(const Pancake &);

main()
{
    Pancake p;

    while (ReadCakes(p)){
	WriteCakes(p);
	FlipCakes(p);
    }
}

void
WriteCakes(const Pancake & p)
{
    int k;
    for(k=0; k < p.numCakes - 1; k++){
	cout << p.stack[k] << " ";
    }
    cout << p.stack[k] << endl;
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
// postcondition: returns 1 iff stack p is sorted     
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
// postcondition: return index of largest pancake before 'last'
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
    int last = p.numCakes;
    while (!IsSorted(p)){
	int index = MaxIndex(p,last);
	if (index != last-1 && index != 0){  // put biggest on top
	    FlipStack(p,index);
	    cout << " " << p.numCakes - index;
	}
	if (index != last-1){                // put biggest on bottom
	    FlipStack(p,last-1);
	    cout << " " << p.numCakes - last + 1;
	}
	last--;
    }
    cout << " 0" << endl;
}
