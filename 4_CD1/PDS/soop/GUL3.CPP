#include<stdio.h>
#include<conio.h>

#define MAX 100

typedef struct _Data{
	int index;
	int start;
	int end;
} Data;

static int QA[MAX/2][MAX];
static int QB[MAX];
static int qacount_array[MAX/2];
static int check[MAX];
int qacount=0,qbcount=0;

void sort(Data data[],int number)
{
	int i,j,minindex,min;
	Data t;
	for(i=0;i<number;i++){
		min=data[i].end;
		minindex=i;
		for(j=i;j<number;j++){
			if(data[j].end<min){
				min=data[j].end;
				minindex=j;
			}
		}
		t=data[i];
		data[i]=data[minindex];
		data[minindex]=t;
	}
}

void qA(Data data[],int number)
{
	int i,j,end;
	while(1){
		for(i=0;i<number;i++){
			if(!check[i]) break;
			if(i==number-1){
				return;
			}
		}
		end=0;
		for(i=0;i<number;i++){
			if(end<=data[i].start&&!check[i]){
				end=data[i].end;
				QA[qacount][qacount_array[qacount]++]=data[i].index;
				check[i]=1;
			}
		}
		qacount++;
	}
}

void qB(Data data[],int number)
{
	int i;
	int end=0;
	for(i=0;i<number;i++){
		if(end<=data[i].start){
			end=data[i].end;
			QB[qbcount++]=data[i].index;
		}
	}
}

void main()
{
	FILE *fs=fopen("q3.inp","r");
	FILE *fp=fopen("q3.out","w");
	Data data[MAX];
	int i,j,number;
	char a;
	fscanf(fs,"%d\n",&number);
	for(i=0;i<number;i++){
		fscanf(fs,"%c %d %d\n",&a,&data[i].start,&data[i].end);
		data[i].index=a-'A';
	}
	sort(data,number);
	qA(data,number);
	fprintf(fp,"(1)\n");
	fprintf(fp,"%d\n",qacount);
	for(i=0;i<qacount;i++){
		fprintf(fp,"%d. ",i+1);
		for(j=0;j<qacount_array[i];j++){
			fprintf(fp,"%c ",QA[i][j]+'A');
		}
		fprintf(fp,"\n");
	}
	qB(data,number);
	fprintf(fp,"(2)\n");
	fprintf(fp,"%d\n",qbcount);
	for(i=0;i<qbcount;i++){
		fprintf(fp,"%c ",QB[i]+'A');
	}
}

