#include<stdio.h>
#include<Conio.h>
#include<stdlib.h>

void input()
{
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n"&n);
		for(i=0;i<n;i++)fscanf(fp,"%d ",&dt[i]);
	fclose(fp);
}

void process()
{
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(dt[i] < dt[j]){
				int imsi;
				imsi = dt[i];dt[i] = dt[j]; dt[j] = imsi;
			}
		}
	} 
}

void output()
{
	int i,go;
	for(i=0;i<n;i++){
		if(go != dt[i]){go = dt[i];k++;}
		else
			printf("%d",k);
	}

}

void main(void)
{
	input();
	process();
	output();
}