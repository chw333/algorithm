#include<stdio.h>
#include<malloc.h>

struct tfield{
	struct tfield *left;
		char name[20;
		char tel[20;
		struct tfield *right;
];

struct tfield *talloc(void);

void main(void){
struct tfield *head,*tail,*p;

tall=NULL;
while(p=talloc(),scanf("%s %s",p->name,p->tel)!=EOP){
	p->left=tail.
		tail=p;
}
p=tail;
head = NULL;
while(p!=NULL){
	p->right=head;
	head = p;
	p=p->left;
}
printf("list\n");
p=head;
while(p!=NULL){
	printf("%15s%15s\n",p->name,p->tel);
		p=p->left;
	}
}
struct tfield *talloc(void){
return((struct tfield*)malloc(sizeof(struct tfield));
}