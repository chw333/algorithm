#include<stdio.h>
#include<conio.h>
#include<string.h>

#define MAX 100

static char string_a[MAX];
static char string_b[MAX];
static char rull_a[MAX];
static char rull_b[MAX];

int check_P(int na,int nb,int ra,int rb)
{
	int i,j,pointa,pointb,more_long;
	if(na>nb) more_long=na;
	else more_long=nb;
	for(i=0;i<more_long;i++){
		pointa=pointb=0;
		if(string_a[i]==rull_a[0] && string_b[i]==rull_b[0]){
			for(j=i;j<more_long;j++){
				if(string_a[j]==rull_a[pointa]) pointa++;
				if(string_b[j]==rull_b[pointb]) pointb++;
			}
			if(pointa==ra&&pointb==rb) return 1;
		}
	}
	return 0;
}

int check_S(int na,int nb,int ra,int rb)
{
	int i,j,pointa,pointb,more_long,last;
	pointa=pointb=0;
	for(i=0;i<na;i++){
		if(string_a[i]==rull_a[pointa]){
			pointa++;
			last=i;
		}
	}
	if(pointa!=ra) return 0;
	for(i=last;i<nb;i++){
		if(string_b[i]==rull_b[pointb]){
			pointb++;
		}
	}
	if(pointb!=rb) return 0;
	return 1;
}

int check_E(int na,int nb,int ra,int rb)
{
	int i,j,pointa,pointb;
	pointa=pointb=0;
	for(i=0;i<na;i++){
		if(string_a[i]==rull_a[pointa]) pointa++;
	}
	for(i=0;i<na;i++){
		if(string_b[i]==rull_b[pointb]) pointb++;
	}
	if(pointa==ra&&pointb!=rb) return 1;
	if(pointa!=ra&&pointb==rb) return 1;
	return 0;
}
void main()
{
	FILE *fs=fopen("q5.inp","r");
	FILE *fp=fopen("q5.out","w");
	int na,nb,ra,rb;
	char in;
	fscanf(fs,"%s\n",&string_a[0]);
	fscanf(fs,"%s\n",&string_b[0]);
	fscanf(fs,"%s\n",&rull_a[0]);
	fscanf(fs,"%s\n",&rull_b[0]);
	na=strlen(string_a);
	nb=strlen(string_b);
	ra=strlen(rull_a);
	rb=strlen(rull_b);
	fscanf(fs,"%c\n",&in);
	if(in=='P'){
		if(check_P(na,nb,ra,rb)){
			fprintf(fp,"FOUND");
			return;
		}
		else{
			fprintf(fp,"NOT FOUND");
			return;
		}
	}
	if(in=='S'){
		if(check_S(na,nb,ra,rb)){
			fprintf(fp,"FOUND");
			return;
		}
		else{
			fprintf(fp,"NOT FOUND");
			return;
		}
	}
	if(in=='E'){
		if(check_E(na,nb,ra,rb)){
			fprintf(fp,"FOUND");
			return;
		}
		else{
			fprintf(fp,"NOT FOUND");
			return;
		}
	}
}


