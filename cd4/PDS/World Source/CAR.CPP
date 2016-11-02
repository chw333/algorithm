#include<stdio.h>
#include<conio.h>

#define MAX 100

static int room[MAX];
static int count[MAX];

void init_count(int number,int kind)
{
	int i,j;
	for(i=0;i<number;i++){
		count[room[i]]++;
	}
	for(i=1;i<=kind;i++){
		count[i]+=count[i-1];
	}
}

int is_end(int number,int kind)
{
	int i,j;
	for(i=1;i<=kind;i++){
		for(j=count[i-1];j<count[i];j++){
			if(room[j]!=i) return 1;
		}
	}
	return 0;
}

void greedy(int number,int kind,int man)
{
	FILE *fp=fopen("car.out","w");
	int i,j,t,k,l;
	int point;
	init_count(number,kind);
	while(is_end(number,kind)){
		for(i=0;i<number;i++) fprintf(fp,"%d ",room[i]);
		fprintf(fp,"\n");
		for(i=1;i<=kind;i++){
			for(j=count[i-1];j<count[i];j++){
				if(room[j]!=i){
					point=room[j];
					room[j]=0;
					goto exit1;
				}
			}
		}
		exit1:
		for(i=0;i<man-1;i++){
			for(j=count[point-1];j<count[point];j++){
				if(room[j]!=point){
					t=room[j];
					if(room[j]==0){
						room[j]=point;
						for(k=1;k<=kind;k++){
							for(l=count[k-1];l<count[k];l++){
								if(room[l]!=k){
									point=room[l];
									room[l]=0;
									goto exit3;
								}
							}
						}
					}
					room[j]=point;
					point=t;
					break;
				}
			}
			exit3:
		}
		for(i=0;i<number;i++){
			if(!room[i]){
				room[i]=point;
				break;
			}
		}
	}
	for(i=0;i<number;i++) fprintf(fp,"%d ",room[i]);
}

void main()
{
	FILE *fs=fopen("car.in","r");
	int i,j,number,man,kind;
	fscanf(fs,"%d %d %d\n",&number,&man,&kind);
	for(i=0;i<number;i++){
		fscanf(fs,"%d ",&room[i]);
	}
	greedy(number,kind,man);
}