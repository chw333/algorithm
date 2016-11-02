#include<stdio.h>
#include<conio.h>

#define MAX 100

static int room[3][MAX];
static int check[MAX];
static int value[3][MAX];
static int data[MAX];

int multymin=9999,na,nb,nc;

void clrcheck(int number)
{
	int i;
	for(i=0;i<number;i++){
		check[i]=0;
		room[0][i]=0; room[1][i]=0; room[2][i]=0;
	}
}

void copy(int n1,int n2,int n3)
{
	int i;
	na=n1, nb=n2, nc=n3;
	for(i=0;i<n1;i++) value[0][i]=room[0][i];
	for(i=0;i<n2;i++) value[1][i]=room[1][i];
	for(i=0;i<n3;i++) value[2][i]=room[2][i];
}

void back_recur(int n1,int n2,int n3,int n,int number)
{
	int p1,p2,p3,min,max;
	int i,j;
	p1=p2=p3=0;
	for(i=0;i<n1;i++) p1+=room[0][i];
	for(i=0;i<n2;i++) p2+=room[1][i];
	for(i=0;i<n3;i++) p3+=room[2][i];
	if(p1<=p2 && p1<=p3) min=p1;
	else if(p2<=p1 && p2<=p3) min=p2;
	else min=p3;
	if(p1>=p2 && p1>=p3) max=p1;
	else if(p2>=p1 && p2>=p3) max=p2;
	else max=p3;
	if(max-min>=multymin){
		return;
	}
	if(number==n){
		p1=p2=p3=0;
		for(i=0;i<n1;i++) p1+=room[0][i];
		for(i=0;i<n2;i++) p2+=room[1][i];
		for(i=0;i<n3;i++) p3+=room[2][i];
		if(p1<=p2 && p1<=p3) min=p1;
		else if(p2<=p1 && p2<=p3) min=p2;
		else min=p3;
		if(p1>=p2 && p1>=p3) max=p1;
		else if(p2>=p1 && p2>=p3) max=p2;
		else max=p3;
		if(max-min<multymin){
			multymin=max-min;
			copy(n1,n2,n3);
		}
		return;
	}
	for(i=0;i<number;i++){
		if(!check[i]){
			check[i]=1;
			room[0][n1]=data[i];
			back_recur(n1+1,n2,n3,n+1,number);
			room[0][n1]=0;
			room[1][n2]=data[i];
			back_recur(n1,n2+1,n3,n+1,number);
			room[1][n2]=0;
			room[2][n3]=data[i];
			back_recur(n1,n2,n3+1,n+1,number);
			room[2][n3]=0;
			check[i]=0;
		}
	}
}

void main()
{
	FILE *fs=fopen("q1.inp","r");
	FILE *fp=fopen("q1.out","w");
	int i,j,number,sum;
	fscanf(fs,"%d\n",&number);
	for(i=0;i<number;i++) fscanf(fs,"%d ",&data[i]);
	for(i=0;i<number;i++){
		clrcheck(number);
		check[i]=1;
		room[0][0]=data[i];
		back_recur(1,0,0,1,number);
		room[0][0]=0;
		check[i]=0;
	}
	sum=0;
	for(i=0;i<na;i++) sum+=value[0][i];
	fprintf(fp,"%d ",sum);
	sum=0;
	for(i=0;i<nb;i++) sum+=value[1][i];
	fprintf(fp,"%d ",sum);
	sum=0;
	for(i=0;i<nc;i++) sum+=value[2][i];
	fprintf(fp,"%d\n",sum);
	for(i=0;i<na;i++) fprintf(fp,"%d ",value[0][i]);
	fprintf(fp,"\n");
	for(i=0;i<nb;i++) fprintf(fp,"%d ",value[1][i]);
	fprintf(fp,"\n");
	for(i=0;i<nc;i++) fprintf(fp,"%d ",value[2][i]);
}