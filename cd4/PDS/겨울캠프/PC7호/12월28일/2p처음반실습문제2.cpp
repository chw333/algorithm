#include<string.h>
#include<stdio.h>
#include<conio.h>
	FILE *fp;
	char dt[100];
	char cur[100],cur1[100];
	int	 fun[100];
	int  h[100];
void main(void)
{
	int ch1=0,ch2=0,k=0,i,j,p,s=0;
	
	fp = fopen("ff.in","r");
		fgets(dt,100,fp);
	
		p = strlen(dt);
	for(i=0;i<p;i++){
		if('0'<=dt[i] && dt[i]<='9')
		{
			cur[ch1] = dt[i];
			ch1++;
		}
		if(dt[i] == '(' || dt[i] == '+' || dt[i] == '-' || dt[i] == '*' || dt[i] == '/')
		{
			cur1[k] = dt[i];
			k++;
			if(dt[i] == '(')s++;
		}
		
		if(dt[i] == ')'&& s!=0){
			s--;
			for(j=k-1;;j--){
				if('(' == cur1[j]){cur1[j] = ' ';k = j;break;}
				else{	
					cur[ch1] = cur1[j];
					cur1[j] = ' ';
					ch1++;
				}
			}
		}
	}					
	p = strlen(cur);
	ch1 = 0;
//process();
}
/*
void process()
{
	int i,j;
	int g[2];

	for(i=0;i<p;i++){
			if('0'<= cur[i] && cur[i]<= '9')
		{
			fun[i] = cur[i]-'0';g[ch1] = fun[i];ch1++;

		}
		
		if(ch1 == 2)
		{
			for(j=0;j<p;j++){
				switch(cur[i])
				{
					case '+':{fun[i] = 1001;break;}
					case '-':{fun[i] = 1002;break;}
					case '*':{fun[i] = 1003;break;}
					case '/':{fun[i] = 1004;break;}
				}
			 ch1 = 0;
			}
		}
	} 
	for(i=0;i<p;i++){
			printf("%d\n",fun[i]);
	}

}*/
