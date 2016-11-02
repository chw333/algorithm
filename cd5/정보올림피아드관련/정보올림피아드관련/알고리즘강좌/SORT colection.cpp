#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<bios.h>
#include<dos.h>
#include<stdlib.h>

#define MAX 10000
#define CUT 1
#define DIS 10

static int room[MAX];
static int copy[MAX];
float first,end;
int number;

void print()
{
	int i,j;
	cleardevice();
	for(i=0;i<number;i++){
		circle(i+DIS,room[i]+DIS,1);
	}
	delay(5);
}

void bouble_sort()
{
	int i,j,t;
	int pro;
	for(i=0;i<number;i++){
		for(j=i;j<number;j++){
			if(room[i]>room[j]){
				t=room[i];
				room[i]=room[j];
				room[j]=t;
				pro=random(30);
				if(pro==0){
					print();
				}
			}
		}
	}
}

void shall_sort()
{
	int i,j,h,k,v;
	for(h=1;h<number;h=h*3+1);

	for(h/=3;h>=1;h/=3){
		for(i=0;i<h;i++){
			for(j=i+h;j<number;j+=h){
				k=j;
				v=room[k];
				while(k-h>=0&&room[k-h]>v){
					room[k]=room[k-h];
					k-=h;
				}
				room[k]=v;
				print();
			}
		}
	}
}

int int_cmp(const void *a, const void *b)
{
	int dd;
	dd=random(10);
	if(dd==1||dd==2||dd==3||dd==4||dd==5){
		print();
	}
	return *(int*)a-*(int*)b;
}

void insert_sort()
{
	int i,j,h,k,v;
	h=1;
	for(i=0;i<h;i++){
		for(j=i+h;j<number;j+=h){
			k=j;
			v=room[k];
			while(k-h>=0&&room[k-h]>v){
				room[k]=room[k-h];
				k-=h;
			}
			room[k]=v;
			print();
		}
	}
}

void main()
{
	FILE *fs=fopen("input1.txt","r");
	int gdriver = DETECT, gmode, errorcode;
	int i;
	initgraph(&gdriver, &gmode, "c:\\tc30\\bgi");
	fscanf(fs,"%d\n",&number);
	for(i=0;i<number;i++){
		fscanf(fs,"%d\n",&room[i]);
	}
	for(i=0;i<number;i++){
		copy[i]=room[i];
	}
	setcolor(getmaxcolor());
	cleardevice();
	printf("Shall Sort");
	getch();
	cleardevice();
	shall_sort();
	for(i=0;i<number;i++) room[i]=copy[i];
	cleardevice();
	printf("Quick Sort");
	getch();
	cleardevice();
	qsort((int*)room,320,sizeof(int),int_cmp);
	for(i=0;i<number;i++) room[i]=copy[i];
	cleardevice();
	printf("Bouble Sort");
	getch();
	cleardevice();
	bouble_sort();
	for(i=0;i<number;i++) room[i]=copy[i];
	cleardevice();
	printf("Insert Sort");
	getch();
	cleardevice();
	insert_sort();
	for(i=0;i<number;i++) room[i]=copy[i];
}
