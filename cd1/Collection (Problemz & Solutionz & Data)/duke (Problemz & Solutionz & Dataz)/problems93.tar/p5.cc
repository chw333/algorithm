#include <iostream.h>
#include <string.h>

// author: Owen Astrachan
// for internet programming contest 1993 (problem 5)

extern "C"{
    int atoi(char *);
}

struct Tree{
    int info;
    Tree * left, * right;
};

Tree * ReadTree();
void Level(Tree *);
int IsSpecified(Tree *);
int currentNode;

const int MAX_NODES = 300;
Tree * nodes[MAX_NODES];          // grab max nodes up front

void
ZeroNodes()
// postcondition: all nodes are illegal (no children, 0 info)     
{
    int k;
    for(k=0; k < MAX_NODES; k++){
	nodes[k]->info = 0;
	nodes[k]->left = nodes[k]->right = NULL;
    }
    currentNode = 0;
}

void
InitNodes()
// postcondition: nodes allocated and zero'd
{
    int k;
    for(k=0; k < MAX_NODES; k++){
	nodes[k] = new Tree;
    }
    ZeroNodes();
}

main()
{
    Tree *t;

    InitNodes();
    
    while (t = ReadTree()){
	if (!IsSpecified(t)){
	    cout << "not complete" << endl;
	}
	else{
	    Level(t);
	}
    }
}

void
AddTree(Tree * & t, char *s, int val)
// add node with 'val' using path 's' to tree 't'     
{
    if (t == NULL){
	t = nodes[currentNode++];
    }
    
    if (*s){
	if (*s == 'L'){
	    AddTree(t->left,s+1,val);         // go left
	}
	else{
	    AddTree(t->right,s+1,val);        // go right
	}
    }
    else{
	if (t->info == 0){
	    t->info = val;
	}
	else{
	    t->info = -1;                     // already seen it
	}
    }
}

Tree *
ReadTree()
{
    char buf[100];
    Tree * t = NULL;
    ZeroNodes();
    while (cin >> buf){
	if (strcmp(buf,"()") == 0){
	    break;
	}
	else{
	    buf[strlen(buf)-1] = '\0'; // remove ')'
	    char *b = buf;
	    while (*b != ','){         // look for comma
		b++;
	    }
	    *b = '\0';
	    AddTree(t,b+1,atoi(buf+1));
	}
    }
    return t;
}

int
IsSpecified(Tree *t)
// postcondition: returns 1 iff tree is properly specified (see problem)
{
    if (t == NULL){
	return 1;
    }
    else if (t->info <= 0){
	return 0;
    }
    else {
	return IsSpecified(t->left) && IsSpecified(t->right);
    }
}

void
Level(Tree *t)
// print tree in level order     
{

	// make a local queue, stick nodes on it (get breadth-first)
    
    Tree * local[MAX_NODES];
    int first = 0;             // front of queue
    int last = 1;              // end of queue
    int size = 1;              // size of queue
    local[first] = t;          // queue up the root

    while(size > 0){
	Tree *temp = local[first];         // dequeue
	first++;                           // set for next element
	size--;                  
	cout << " " << temp->info;
	if (temp->left){
	    local[last++] = temp->left;    // queue up left-child
	    size++;
	}
	if (temp->right){
	    local[last++] = temp->right;
	    size++;
	}
    }
    cout << endl;
}
