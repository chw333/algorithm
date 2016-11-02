#include<stdio.h>

char stack[50],polish[50];
double v[50];
int pri[255];
int sp1,sp2;
int buf[50];
void main(void)
{
	int i;
	char *p="2+9*5-7+(9+9+9+3-8*2)/2";

	for(i=0;i<=255;i++)	pri[i] = 3;
	pri['+']=pri['-']=1;
	pri['*']=pri['/']=2;
	pri['(']=0;

	stack[0] =0;pri[0] =-1;
	sp1=sp2= 0;
	while(*p!='\0'){
		if(*p=='(')
			stack[++sp1]=*p;
		else if(*p==')'){
			while(stack[sp1]!='(')
				polish[++sp2] = stack[sp1--];
			sp1--;
		}
		else{
			while(pri[*p]<=pri[stack[sp1]])
				polish[++sp2] = stack[sp1--];
			stack[++sp1]= *p;
		}
		p++;
	}
	
	
	for(i=sp1;i>0;i--)polish[++sp2] = stack[i];
	for(i=1;i<=sp2;i++){
		if('0'<=polish[i] && polish[i]<='9')
		{
			buf[i] = polish[i]-'0';
		}
		else
		{
			if(polish[i] =='+')buf[i] = 3001;
			if(polish[i] =='-')buf[i] = 3002;
			if(polish[i] =='*')buf[i] = 3003;
			if(polish[i] =='/')buf[i] = 3004;
		}				
	}
//	for(i=1;i<=sp2;i++)putchar(polish[i]);
	for(i=1;i<=sp2;i++){
		int l;
		if(buf[i] >=3001)
		{
			 l = i-1;
vigo1:	
				if(buf[l] != 10000 && buf[l] < 3001)
				{
					int k;
					k = l-1;
vigo2:
					if(buf[k] != 10000 && buf[k] < 3001)
					{
						if(buf[i] == 3001){buf[i] = buf[k]+buf[l];}
						if(buf[i] == 3002){buf[i] = buf[k]-buf[l];}
						if(buf[i] == 3003){buf[i] = buf[k]*buf[l];}
						if(buf[i] == 3004){buf[i] = buf[k]/buf[l];}
						buf[k] = buf[l] = 10000;
					}
					else{ k--;goto vigo2;}
				}
				else {l--;goto vigo1;}
		}
	}	

	
printf("%d",sp2);
	
	
	
}