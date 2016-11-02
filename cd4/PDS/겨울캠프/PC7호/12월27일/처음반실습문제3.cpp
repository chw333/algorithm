#include<stdio.h>
#include<conio.h>
main()
{
	int cnt,dt[100],dt1[100],i,j,stac[100],t,p;
	FILE *fp;
	fp = fopen("input3.txt","r");
		fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt;i++){fscanf(fp,"%d ",&dt[i]);dt1[i] = dt[i];}
		
		for(i=0;i<cnt-1;i++){
			for(j=i+1;j<cnt;j++){
				if(dt1[i]>dt1[j]){
					int imsi;
					imsi = dt1[i];dt1[i] = dt1[j];dt1[j] = imsi;
				}
			}
		}
		t=-1;
		p=0;
		for(i=0;i<cnt;i++){
			if(dt[i] == dt1[i]){
			printf("sx");
				p++;
			dt[i] = 0;
			}
			
			if(dt[i] != dt1[i]){
				t++;
				stac[t] = dt[i];
				dt[i] = 0;
				printf("s");
			}
start:
			if(stac[t] == dt1[p]){
				printf("x");
				t--;
				p++;
				if(stac[t] == dt1[p]){
					goto start;
				}
			}


		}
	
}
