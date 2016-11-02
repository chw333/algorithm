#include<stdio.h>
#include<conio.h>
#include<limits.h>

#define MAX 9
#define number MAX

static char remember[MAX];
static int room[MAX];
static int path[MAX];

void e(int x)
{
	if(room[x-1]==2) room[x-1]=1;
	else room[x-1]=2;
}

int is_right()
{
	int i,j;
	for(i=0;i<number;i++){
		if(room[i]==2) return 0;
	}
	return 1;
}

void char2int()
{
	int i,j;
	for(i=0;i<number;i++){
		if(remember[i]=='w') room[i]=1;
		else room[i]=2;
	}
}

void b1() { e(1); e(2);	e(4);	e(5); }
void b2() {	e(1); e(2); e(3); e(4); e(5); e(6); }
void b3() {	e(2); e(3); e(5); e(6); }
void b4() { e(1); e(2); e(4); e(5); e(7); e(8); }
void b5() { e(1); e(2); e(3); e(4); e(5); e(6); e(7); e(8); e(9); }
void b6() {	e(2); e(3); e(5); e(6); e(8); e(9); }
void b7() {	e(4); e(5); e(7); e(8); }
void b8() { e(4); e(5); e(6); e(7); e(8); e(9); }
void b9() { e(5); e(6); e(8); e(9); }

void get_x()
{
	int i,j,k,l,m,n,o,p,q;
	int min=INT_MAX;
	int count;
	char2int();
	for(i=0;i<2;i++) for(j=0;j<2;j++) for(k=0;k<2;k++) for(l=0;l<2;l++) for(m=0;m<2;m++) for(n=0;n<2;n++) for(o=0;o<2;o++) for(p=0;p<2;p++)
		for(q=0;q<2;q++){
			if(i) b1(); if(j) b2(); if(k) b3(); if(l) b4(); if(m) b5(); if(n) b6(); if(o) b7();	if(p) b8(); if(q) b9();
			if(is_right()){
				count=0;
				if(i) count++; if(j) count++; if(k) count++; if(l) count++; if(m) count++; if(n) count++; if(o) count++; if(p) count++; if(q) count++;
				if(count<=min){
					min=count;
					path[0]=i; path[1]=j; path[2]=k; path[3]=l; path[4]=m; path[5]=n; path[6]=o; path[7]=p; path[8]=q;
				}
			}
			if(i) b1(); if(j) b2(); if(k) b3();	if(l) b4(); if(m) b5();	if(n) b6();	if(o) b7(); if(p) b8(); if(q) b9();
		}
}

void main()
{
	FILE *fs=fopen("input.txt","r");
	FILE *fp=fopen("output.txt","w");
	int i,j,oil;
	fscanf(fs,"%d\n",&oil);
	for(i=0;i<oil;i++){
		fscanf(fs,"%s\n",&remember[0]);
		get_x();
		for(j=0;j<number;j++){
			if(path[j]) fprintf(fp,"%d",j+1);
		}
		fprintf(fp,"\n");
	}
}
