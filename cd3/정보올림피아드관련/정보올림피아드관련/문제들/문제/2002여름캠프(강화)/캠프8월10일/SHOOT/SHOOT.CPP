/* SHO.CPP - by Zeljko Svedic (67 lines) */

#include <stdio.h>

#define FLAG 21345

struct { int pr,dr; } co[1001];

FILE *in=fopen("shoot.in","rt"),
    *out=fopen("shoot.out","wt");

int r, c, brp[1001], rj[1001];

void ucitaj(void)
{
	fscanf(in,"%i%i",&r,&c);

	for(int i=0;i<1001;i++) brp[i]=0;

	for(i=0;i<c;i++) {
		fscanf(in,"%i%i",&co[i].pr,&co[i].dr);
		co[i].pr--; brp[co[i].pr]++;
		co[i].dr--; brp[co[i].dr]++;
		rj[i]=0;
	}
}

void rijesi(void)
{
	int minimum,tm,mini,i,j;

	for(j=0;j<c;j++)
	{
		minimum=FLAG+1;

		for(i=0;i<c;i++)
			if(!rj[i]) {
				tm=(brp[co[i].pr] < brp[co[i].dr]) ? brp[co[i].pr]:brp[co[i].dr];
				if(tm<minimum) { minimum=tm; mini=i; }
			}

		if(brp[co[mini].pr]==minimum) {
			rj[mini]=co[mini].pr+1;
			brp[co[mini].pr]=FLAG;
			brp[co[mini].dr]--;
		}else{
			rj[mini]=co[mini].dr+1;
			brp[co[mini].dr]=FLAG;
			brp[co[mini].pr]--;
		}
	}

	for(i=0;i<r;i++) if(brp[i]<1111) { fprintf(out,"NO\n"); return; }

	for(i=0;i<c;i++) fprintf(out,"%i ",rj[i]);
	fprintf(out,"\n");
}

void main(void)
{
	int x,br;

	fscanf(in,"%i",&x);
	for(br=0;br<x;br++) { ucitaj(); rijesi(); }

	fclose(in); fclose(out);
}