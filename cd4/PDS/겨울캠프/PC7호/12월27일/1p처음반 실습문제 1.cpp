#include<stdio.h>
#include<conio.h>
main()
{
	FILE *fp;
	static int n,m,k,i,j,cnt,cnt1=1,ou[100],ch[100];

	fp = fopen("input1.txt","r");
		fscanf(fp,"%d %d %d",&n,&m,&k);
	fclose(fp);
	ou[0] = m;
	ch[m] = 1;
	for(i=m+1;;i++){
		if(ch[i] == 0){
			cnt++;
			if(cnt==k){
					cnt = 0;
					ch[i] = 1;
					ou[cnt1++] = i;
			}
		}
		if(i==n)
			i=0;
		if(cnt1== n)
			break;
	}
	for(i=0;i<n;i++){
		printf("%d",ou[i]);
	}
	printf("\n%d",ou[n-1]);

}
	
